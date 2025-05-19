/**
 ************************************
 * @file     : ws2812.c
 * @author   : ganyuo
 * @date     : 2025-05-19
 ************************************
 * @brief :
 *     ws2812彩色LED驱动
 */

#include "ws2812.h"

#define CODE_0     30
#define CODE_1     60
#define CODE_RESET 0

void ws2812_update()
{
    static uint16_t data[] =
    {
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,
        CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1,
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,

        CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1,
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,

        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0, CODE_0,
        CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1,

        CODE_0, CODE_0, CODE_0, CODE_1, CODE_1, CODE_1, CODE_1, CODE_0,
        CODE_0, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1, CODE_1,
        CODE_0, CODE_0, CODE_0, CODE_0, CODE_1, CODE_1, CODE_1, CODE_1,
        CODE_RESET
    };

    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)data, sizeof(data)/sizeof(uint16_t));
}