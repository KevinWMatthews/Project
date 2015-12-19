#ifndef SpiApi_H
#define SpiApi_H

#include "DataTypes.h"

enum
{
  SPIAPI_SLAVE_NOT_READY = -1
};
int8_t SpiApi_Send(RegisterPointer slave, int8_t data);

#endif
