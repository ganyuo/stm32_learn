
#ifndef __OLED_H__
#define __OLED_H__

#include "i2c.h"

#define OLED_ADDRESS 0x7A

void OLED_SendCmd(uint8_t cmd);
void OLED_NewFrame();
void OLED_ShowFrame();
void OLED_Init();
void OLED_SetPixel(uint8_t x, uint8_t y);

#endif /* __OLED_H__ */