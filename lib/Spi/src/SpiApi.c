#include "SpiApi.h"
#include "SpiHw.h"

int8_t SpiApi_Send(RegisterPointer slave, int8_t data)
{
  if (!SpiHw_IsDeviceReady(slave))
  {
    return SPIAPI_SLAVE_NOT_READY;
  }
  if (!SpiHw_PrepareForSend(data))
  {
    return SPIAPI_MASTER_NOT_READY;
  }
  SpiHw_StartTransmission();
  return SPIAPI_SUCCESS;
}
