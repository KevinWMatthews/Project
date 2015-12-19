#ifndef SpiHw_H
#define SpiHw_H

#include "DataTypes.h"

BOOL SpiHw_IsSlaveBusy(RegisterPointer slave);
int8_t SpiHw_GetUsiCounter(void);
void SpiHw_LoadOutputRegister(int8_t data);
void SpiHw_EnableClockInterrupt(BOOL isEnabled);

#endif
