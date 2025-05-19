/**
 ************************************
 * @file     : ws2812.h
 * @author   : ganyuo
 * @date     : 2025-05-19
 ************************************
 * @brief :
 *     ws2812彩色LED驱动
 */

#ifndef __WS2812_H__
#define __WS2812_H__

#include <tim.h>

#define LED_COUNT 10

void ws2812_set(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

void ws2812_setall(uint8_t red, uint8_t green, uint8_t blue);

void ws2812_update();

#endif /* __WS2812_H__ */
