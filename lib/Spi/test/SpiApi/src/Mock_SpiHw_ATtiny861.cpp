extern "C"
{
  #include "SpiHw.h"
}

#include "CppUTestExt/MockSupport.h"

BOOL SpiHw_IsDeviceReady(RegisterPointer device)
{
  mock().actualCall("SpiHw_IsDeviceReady")
        .withParameter("device", device);
  return (BOOL)(mock().intReturnValue());
}

BOOL SpiHw_PrepareForSend(int8_t data)
{
  mock().actualCall("SpiHw_PrepareForSend")
        .withParameter("data", data);
  return (BOOL)(mock().intReturnValue());
}
