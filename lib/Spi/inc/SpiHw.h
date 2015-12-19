#ifndef SpiHw_H
#define SpiHw_H

#include "DataTypes.h"

BOOL SpiHw_IsMasterReady(void);
BOOL SpiHw_IsSlaveReady(RegisterPointer slave);
BOOL SpiHw_PrepareDataForSend(int8_t data);
void SpiHw_StartTransmission(void);

#endif
