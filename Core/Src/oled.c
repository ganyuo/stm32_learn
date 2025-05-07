#include "oled.h"
#include <string.h>

uint8_t OLED_GRAM[8][128];

void OLED_SendCmd(uint8_t cmd)
{
    uint8_t send_buff[2];
    send_buff[0] = 0x00;
    send_buff[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, send_buff, 2, HAL_MAX_DELAY);
}

void OLED_NewFrame()
{
    memset(OLED_GRAM, 0, sizeof(OLED_GRAM));

}

void OLED_ShowFrame()
{
    uint8_t send_buff[129];
    send_buff[0] = 0x40;
    for(int8_t i = 0; i < 8; i++)
    {
        memcpy(send_buff + 1, OLED_GRAM[i], sizeof(OLED_GRAM[i]));
        OLED_SendCmd(0xB0 + i);
        OLED_SendCmd(0x00);
        OLED_SendCmd(0x10);
        HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, send_buff, sizeof(send_buff), HAL_MAX_DELAY);
    }
}

void OLED_Init()
{
    OLED_SendCmd(0xAE); /*关闭显示 display off*/

    OLED_SendCmd(0x20);
    OLED_SendCmd(0x10);

    OLED_SendCmd(0xB0);

    OLED_SendCmd(0xC8);

    OLED_SendCmd(0x00);
    OLED_SendCmd(0x10);

    OLED_SendCmd(0x40);

    OLED_SendCmd(0x81);

    OLED_SendCmd(0xDF);
    OLED_SendCmd(0xA1);

    OLED_SendCmd(0xA6);
    OLED_SendCmd(0xA8);

    OLED_SendCmd(0x3F);

    OLED_SendCmd(0xA4);

    OLED_SendCmd(0xD3);
    OLED_SendCmd(0x00);

    OLED_SendCmd(0xD5);
    OLED_SendCmd(0xF0);

    OLED_SendCmd(0xD9);
    OLED_SendCmd(0x22);

    OLED_SendCmd(0xDA);
    OLED_SendCmd(0x12);

    OLED_SendCmd(0xDB);
    OLED_SendCmd(0x20);

    OLED_SendCmd(0x8D);
    OLED_SendCmd(0x14);

    OLED_NewFrame();
    OLED_ShowFrame();

    OLED_SendCmd(0xAF); /*开启显示 display ON*/
}


void OLED_SetPixel(uint8_t x, uint8_t y)
{
    if(x >= 128 || y >= 64)
    {
        return ;
    }
    OLED_GRAM[y / 8][x] |= (0x01 << (y % 8));
}
