#ifndef Spi_H
#define Spi_H

#include "DataTypes.h"

enum
{
  SPI_FAIL_USI_COUNTER_NONZERO = -3,
  SPI_FAIL_SLAVE_BUSY          = -2,
  SPI_FAIL_NULL_SLAVE          = -1,
  SPI_SUCCESS                  = 0
};
int8_t Spi_Send(RegisterPointer slave, int8_t data);

#endif
