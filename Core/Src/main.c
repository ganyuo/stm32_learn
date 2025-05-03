#include "stm32f4xx_hal.h"
#include "system_clock_init.h"
#include "gpio_init.h"
#include "usart_init.h"

/**
 * @brief  The application entry point.
 * @retval int
 */
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

    uint8_t uart_buff[2];
    GPIO_PinState led_state;

    /* Infinite loop */
    while (1)
    {
        HAL_UART_Receive(&usart1, uart_buff, 2, HAL_MAX_DELAY);
        HAL_UART_Transmit(&usart1, uart_buff, 2, 100);

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
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, led_state);
        }
        else if(uart_buff[0] == 'G')
        {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, led_state);
        }
        else if(uart_buff[0] == 'B')
        {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, led_state);
        }
    }
}
