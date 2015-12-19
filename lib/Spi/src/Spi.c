#include "Spi.h"
#include "SpiHw.h"



int8_t Spi_Send(RegisterPointer slave, int8_t data)
{
  RETURN_VALUE_IF_NULL(slave, SPI_FAIL_NULL_SLAVE);
  if (SpiHw_IsSlaveBusy(slave) == TRUE)
  {
    return SPI_FAIL_SLAVE_BUSY;
  }
  if (SpiHw_GetUsiCounter() != 0)
  {
    return SPI_FAIL_USI_COUNTER_NONZERO;
  }
  SpiHw_LoadOutputRegister(data);
  SpiHw_EnableClockInterrupt(TRUE);
  return SPI_SUCCESS;
}
