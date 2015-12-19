#ifndef SpiHw_H
#define SpiHw_H

#include "DataTypes.h"

BOOL SpiHw_IsDeviceReady(RegisterPointer device);
BOOL SpiHw_PrepareForSend(int8_t data);

#endif
