#ifndef SpiApi_H
#define SpiApi_H

#include "DataTypes.h"

enum
{
  SPIAPI_CMD_IN_QUEUE = 0
};
int8_t SpiApi_Send(RegisterPointer slave, int8_t data);
void SpiApi_Service(void);

#endif
