#ifndef Spi_H
#define Spi_H

#include "DataTypes.h"
#include "SpiHw.h"

typedef struct SpiSlaveCommandStruct * SpiSlaveCommand;

enum
{
  SPI_FAIL_SLAVE_BUSY = -1,
  SPI_SUCCESS         = 0
};
int8_t Spi_Send(RegisterPointer slave, int8_t data);
int8_t Spi_Get(RegisterPointer slave, SpiSlaveCommand command, int8_t *data);

#endif
