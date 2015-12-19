#ifndef SpiApi_H
#define SpiApi_H

#include "DataTypes.h"

enum
{
  SPIAPI_MASTER_NOT_READY = -2,
  SPIAPI_SLAVE_NOT_READY  = -1,
  SPIAPI_SUCCESS          = 0
};
int8_t SpiApi_Send(RegisterPointer slave, int8_t data);

#endif
