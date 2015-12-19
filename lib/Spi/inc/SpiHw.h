#ifndef SpiHw_H
#define SpiHw_H

#include "DataTypes.h"

BOOL SpiHw_IsSlaveBusy(RegisterPointer slave);
int8_t SpiHw_GetUsiCounter(void);

#endif
