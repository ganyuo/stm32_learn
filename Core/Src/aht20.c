#include "aht20.h"

#define AHT20_ADDRESS 0x70

uint8_t read_buff[6] = {0};

void AHT20_Init()
{
    uint8_t read_buff;
    HAL_Delay(40);
    HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, &read_buff, 1, HAL_MAX_DELAY);
    if((read_buff & 0x08) == 0x00)
    {
        uint8_t send_buff[3] = {0xBE, 0x08, 0x00};
        HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, send_buff, 3, HAL_MAX_DELAY);
    }
}

void AHT20_Read(float *temperature, float *humidity)
{
    uint8_t send_buff[3] = {0xAC, 0x33, 0x00};
    uint8_t read_buff[6];

    HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDRESS, send_buff, 3, HAL_MAX_DELAY);
    HAL_Delay(75);

    HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDRESS, read_buff, 6, HAL_MAX_DELAY);
    if((read_buff[0] & 0x80) == 0x00)
    {
        uint32_t data = 0;
        data = ((uint32_t)read_buff[3] >> 4) + ((uint32_t)read_buff[2] << 4) + ((uint32_t)read_buff[1] << 12);
        *humidity = data * 100.0f / (1 << 20);

        data = (((uint32_t)read_buff[3] & 0x0F) << 16) + ((uint32_t)read_buff[4] << 8) + (uint32_t)read_buff[5];
        *temperature = data * 200.0f / (1 << 20) - 50;
    }
}

void AHT20_Measure()
{
    static uint8_t send_buff[3] = {0xAC, 0x33, 0x00};
    HAL_I2C_Master_Transmit_IT(&hi2c1, AHT20_ADDRESS, send_buff, 3);
}

void AHT20_Get()
{
    HAL_I2C_Master_Receive_IT(&hi2c1, AHT20_ADDRESS, read_buff, 6);
}

void AHT20_Analysis(float *temperature, float *humidity)
{
    if((read_buff[0] & 0x80) == 0x00)
    {
        uint32_t data = 0;
        data = ((uint32_t)read_buff[3] >> 4) + ((uint32_t)read_buff[2] << 4) + ((uint32_t)read_buff[1] << 12);
        *humidity = data * 100.0f / (1 << 20);

        data = (((uint32_t)read_buff[3] & 0x0F) << 16) + ((uint32_t)read_buff[4] << 8) + (uint32_t)read_buff[5];
        *temperature = data * 200.0f / (1 << 20) - 50;
    }
}
