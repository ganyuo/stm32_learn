#include "usart_init.h"
#include "error_handler.h"

UART_HandleTypeDef usart1;

/**
 * @brief 启动串口1
 * @param None
 * @retval None
 */
void USART1_Init(void)
{
    /* 初始化GPIO
        PA9     ------> USART1_TX
        PA10    ------> USART1_RX
    */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 配置串口 */
    usart1.Instance = USART1;
    usart1.Init.BaudRate = 115200;
    usart1.Init.WordLength = UART_WORDLENGTH_8B;
    usart1.Init.StopBits = UART_STOPBITS_1;
    usart1.Init.Parity = UART_PARITY_NONE;
    usart1.Init.Mode = UART_MODE_TX_RX;
    usart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    usart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&usart1) != HAL_OK)
    {
        Error_Handler();
    }

    // /* 启动串口中断 */
    // HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/**
 * @brief 关闭串口1
 * @retval None
 */
void USART1_DeInit(UART_HandleTypeDef *huart)
{
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    /* USART1 interrupt DeInit */
    // HAL_NVIC_DisableIRQ(USART1_IRQn);
}

/**
 * @brief 串口1中断处理函数
 * @retval None
 */
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&usart1);
}
