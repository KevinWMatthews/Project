#include "Spi.h"



int8_t Spi_Send(RegisterPointer slave, int8_t data)
{
  if (SpiHw_IsSlaveBusy(slave) == TRUE)
  {
    return SPI_FAIL_SLAVE_BUSY;
  }

  return SPI_SUCCESS;
}

int8_t Spi_Get(RegisterPointer slave, SpiSlaveCommand command, int8_t *data)
{
  return SPI_SUCCESS;
}
