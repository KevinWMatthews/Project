#include "SpiApi.h"
#include "SpiHw.h"

int8_t SpiApi_Send_Impl(RegisterPointer slave, int8_t data)
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
  return SPIAPI_SEND_SUCCESS;
}

int8_t (*SpiApi_Send)(RegisterPointer, int8_t) = SpiApi_Send_Impl;

int8_t SpiApi_Get(RegisterPointer slave, int8_t *data)
{
  if (!SpiHw_IsMasterReady())
  {
    *data = 0;
    return SPIAPI_MASTER_NOT_READY;
  }
  *data = 0;
  return SPIAPI_SEND_FAILED;
}
