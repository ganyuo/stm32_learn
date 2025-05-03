#include "stm32f4xx_hal.h"
#include "system_clock_init.h"
#include "gpio_init.h"
#include "usart_init.h"

uint8_t uart_buff[2];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    GPIO_PinState led_state;
    HAL_UART_Transmit_IT(&usart1, uart_buff, 2);
    if(uart_buff[1] == '0')
    {
        led_state = GPIO_PIN_RESET;
    }
    else
    {
        led_state = GPIO_PIN_SET;
    }
    if(uart_buff[0] == 'R')
    {
        HAL_GPIO_WritePin(GPIOD, LED_RED_PIN, led_state);
    }
    else if(uart_buff[0] == 'G')
    {
        HAL_GPIO_WritePin(GPIOD, LED_GREEN_PIN, led_state);
    }
    else if(uart_buff[0] == 'B')
    {
        HAL_GPIO_WritePin(GPIOD, LED_BLUE_PIN, led_state);
    }
    HAL_UART_Receive_IT(&usart1, uart_buff, 2);
}

int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    GPIO_Init();
    USART1_Init();

    HAL_UART_Receive_IT(&usart1, uart_buff, 2);
    /* Infinite loop */
    while (1)
    {
    }
}
