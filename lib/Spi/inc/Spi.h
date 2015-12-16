#ifndef Spi_H
#define Spi_H

#include "DataTypes.h"
#include "SpiHw.h"

typedef struct SpiSlaveSelectStruct * SpiSlaveSelect;

enum
{
  SPI_SUCCESS = 0
};
int8_t Spi_Send(SpiSlaveSelect slave, int8_t data);

#endif
