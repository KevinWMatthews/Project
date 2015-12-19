extern "C"
{
  #include "SpiApi.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_SpiApi.h"

TEST_GROUP(SpiApi)
{
  RegisterPointer slave;
  int8_t data, result;

  void setup()
  {
    slave  = NULL;
    data   = 42;
    result = 66;
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(SpiApi, TEST_SERVICE_SPI_DOES_NOTHING_IF_NO_COMMANDS_IN_QUEUE)
{
  SpiApi_Service();
}

TEST(SpiApi, TEST_SINGLE_SEND_CALLS_SINGLE_TRANSMIT_COMMAND)
{
  mock().expectOneCall("Spi_Transmit")
        .withParameter("slave", slave)
        .withParameter("data", data);
  result = SpiApi_Send(slave, data);

  SpiApi_Service();
  LONGS_EQUAL(SPIAPI_CMD_IN_QUEUE, result)
  SpiApi_Service(); //Won't cause a second transmit
}

IGNORE_TEST(SpiApi, TEST_TWO_SENDS_CALL_TWO_TRANSMIT_COMMAND)
{
  mock().expectOneCall("Spi_Transmit")
        .withParameter("slave", slave)
        .withParameter("data", data);
  mock().expectOneCall("Spi_Transmit")
        .withParameter("slave", slave)
        .withParameter("data", data+1);

  SpiApi_Send(slave, data);
  result = SpiApi_Send(slave, data+1);
  LONGS_EQUAL(SPIAPI_CMD_IN_QUEUE, result)
  SpiApi_Service();
  SpiApi_Service();
  SpiApi_Service(); //Won't cause a third transmit
}
