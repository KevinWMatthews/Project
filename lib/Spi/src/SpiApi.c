#include "SpiApi.h"
#include "SpiHw.h"

int8_t SpiApi_Send(RegisterPointer slave, int8_t data)
{
  SpiHw_IsDeviceReady(slave);
  return SPIAPI_SLAVE_NOT_READY;
}
