#include "SpiApi.h"
#include "SpiHw.h"

int8_t SpiApi_Send(RegisterPointer slave, int8_t data)
{
  if (!SpiHw_IsMasterReady())
  {
    return SPIAPI_MASTER_NOT_READY;
  }
  if (!SpiHw_IsSlaveReady(slave))
  {
    return SPIAPI_SLAVE_NOT_READY;
  }
  if (!SpiHw_PrepareDataForSend(data))
  {
    return SPIAPI_PREPARE_DATA_FAIL;
  }
  SpiHw_StartTransmission();
  return SPIAPI_SUCCESS;
}
