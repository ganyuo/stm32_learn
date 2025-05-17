#include "ga_rtc.h"
#include "main.h"
#include <time.h>

#define RTC_INIT_FLAG 0x2333

/**
  * @brief  Enters the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if ((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);


    return HAL_OK;
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef *hrtc)
{
    uint32_t tickstart = 0U;

    /* Disable the write protection for RTC registers */
    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);

    tickstart = HAL_GetTick();
    /* Wait till RTC is in INIT state and if Time out is reached exit */
    while ((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
    {
        if ((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Read the time counter available in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval Time counter
  */
static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef *hrtc)
{
    uint16_t high1 = 0U, high2 = 0U, low = 0U;
    uint32_t timecounter = 0U;

    high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
    low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
    high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

    if (high1 != high2)
    {
        /* In this case the counter roll over during reading of CNTL and CNTH registers,
           read again CNTL register then return the counter value */
        timecounter = (((uint32_t) high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
    }
    else
    {
        /* No counter roll over during reading of CNTL and CNTH registers, counter
           value is equal to first value of CNTL and CNTH */
        timecounter = (((uint32_t) high1 << 16U) | low);
    }

    return timecounter;
}

/**
  * @brief  Write the time counter in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  TimeCounter: Counter to write in RTC_CNT registers
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef *hrtc, uint32_t TimeCounter)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Set Initialization mode */
    if (RTC_EnterInitMode(hrtc) != HAL_OK)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set RTC COUNTER MSB word */
        WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16U));
        /* Set RTC COUNTER LSB word */
        WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));

        /* Wait for synchro */
        if (RTC_ExitInitMode(hrtc) != HAL_OK)
        {
            status = HAL_ERROR;
        }
    }

    return status;
}

HAL_StatusTypeDef GA_RTC_SetTime(struct tm *time_)
{
    uint32_t unix_time = mktime(time_);
    return RTC_WriteTimeCounter(&hrtc, unix_time);
}

struct tm* GA_RTC_GetTime()
{
    time_t unix_time = RTC_ReadTimeCounter(&hrtc);
    return gmtime(&unix_time);
}

void GA_RTC_Init(void)
{
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;

    uint32_t init_flag = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
    if(init_flag == RTC_INIT_FLAG)
    {
        return ;
    }
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }
    RTC_DateTypeDef rtc_date_set =
    {
        .Year = 2025 - 1970,
        .Month = RTC_MONTH_MAY,
        .Date = 17,
        .WeekDay = RTC_WEEKDAY_SATURDAY
    };
    RTC_TimeTypeDef rtc_time_set =
    {
        .Hours = 23,
        .Minutes = 10,
        .Seconds = 20
    };
    HAL_RTC_SetDate(&hrtc, &rtc_date_set, RTC_FORMAT_BCD);
    HAL_RTC_SetTime(&hrtc, &rtc_time_set, RTC_FORMAT_BCD);
}
