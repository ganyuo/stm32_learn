
#ifndef __AHT20_H__
#define __AHT20_H__

#include "i2c.h"

#define AHT20_ADDRESS 0x70

void AHT20_Init();
void AHT20_Read(float *temperature, float *humidity);

#endif /* __AHT20_H__ */