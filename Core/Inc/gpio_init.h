
#ifndef __GPIO_INIT_H__
#define __GPIO_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define LED_GREEN_PIN   GPIO_PIN_12
#define LED_ORANGE_PIN  GPIO_PIN_13
#define LED_RED_PIN     GPIO_PIN_14
#define LED_BLUE_PIN    GPIO_PIN_15

void GPIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_INIT_H__ */
