extern "C"
{
  #include "Spi.h"
}

#include "CppUTestExt/MockSupport.h"

int8_t Spi_Transmit(RegisterPointer slave, int8_t data)
{
  mock().actualCall("Spi_Transmit")
        .withParameter("slave", slave)
        .withParameter("data", data);
  return mock().intReturnValue();
}
