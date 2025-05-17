#ifndef __GA_RTC_H__
#define __GA_RTC_H__

#include "stm32f1xx_hal.h"
#include "rtc.h"
#include <time.h>

HAL_StatusTypeDef GA_RTC_SetTime(struct tm *time_);

struct tm* GA_RTC_GetTime();

#endif /* __GA_RTC_H__ */
