extern "C"
{
  #include "SpiHw.h"
}

#include "CppUTestExt/MockSupport.h"

BOOL SpiHw_IsMasterReady(void)
{
  mock().actualCall("SpiHw_IsMasterReady");
  return (BOOL)(mock().intReturnValue());
}

BOOL SpiHw_IsSlaveReady(RegisterPointer slave)
{
  mock().actualCall("SpiHw_IsSlaveReady")
        .withParameter("slave", slave);
  return (BOOL)(mock().intReturnValue());
}

BOOL SpiHw_PrepareDataForSend(int8_t data)
{
  mock().actualCall("SpiHw_PrepareDataForSend")
        .withParameter("data", data);
  return (BOOL)(mock().intReturnValue());
}

void SpiHw_StartTransmission(void)
{
  mock().actualCall("SpiHw_StartTransmission");
}
