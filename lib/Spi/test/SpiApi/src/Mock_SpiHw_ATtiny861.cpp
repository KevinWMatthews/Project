extern "C"
{
  #include "SpiHw.h"
}

#include "CppUTestExt/MockSupport.h"

BOOL SpiHw_IsSlaveBusy(RegisterPointer slave)
{
  mock().actualCall("SpiHw_IsSlaveBusy")
        .withParameter("slave", slave);
  return (BOOL)(mock().intReturnValue());
}
