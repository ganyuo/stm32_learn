
#ifndef __USART_INIT_H__
#define __USART_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef usart1;

void USART1_Init(void);
void USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __USART_INIT_H__ */
