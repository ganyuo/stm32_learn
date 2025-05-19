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

uint8_t led_coler[LED_COUNT][3];

void ws2812_set(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if(index >= LED_COUNT)
    {
        return ;
    }
    led_coler[index][0] = red;
    led_coler[index][1] = green;
    led_coler[index][2] = blue;
}

void ws2812_setall(uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        ws2812_set(i, red, green, blue);
    }
}

void ws2812_update()
{
    static uint16_t data[3 * 8 * LED_COUNT  + 1];

    for (int i = 0; i < LED_COUNT; i++)
    {
        uint8_t red   = led_coler[i][0];
        uint8_t green = led_coler[i][1];
        uint8_t blue  = led_coler[i][2];

        for(int j = 0; j < 8; j++)
        {
            data[24 * i + j]      = (green & (0x80 >> j)) ? CODE_1 : CODE_0;
            data[24 * i + j + 8]  = (red   & (0x80 >> j)) ? CODE_1 : CODE_0;
            data[24 * i + j + 16] = (blue  & (0x80 >> j)) ? CODE_1 : CODE_0;
        }
    }
    data[LED_COUNT * 24] = CODE_RESET;

    HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SetCounter(&htim4, 0);
    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)data, sizeof(data)/sizeof(uint16_t));
}