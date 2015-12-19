#ifndef SpiApi_H
#define SpiApi_H

#include "DataTypes.h"

enum
{
  SPIAPI_PREPARE_DATA_FAIL = -3,
  SPIAPI_MASTER_NOT_READY  = -2,
  SPIAPI_SLAVE_NOT_READY   = -1,
  SPIAPI_SEND_SUCCESS      = 0
};
extern int8_t (*SpiApi_Send)(RegisterPointer slave, int8_t data);

enum
{
  SPIAPI_SEND_FAILED = -1
};
int8_t SpiApi_Get(RegisterPointer slave, int8_t *data);

#endif
