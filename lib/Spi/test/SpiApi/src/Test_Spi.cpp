extern "C"
{
  #include "Spi.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Spi.h"

TEST_GROUP(Spi)
{
  RegisterPointer slave;
  SpiSlaveCommand command;

  void setup()
  {
    slave = NULL;
    command = NULL;
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(Spi, TEST_FAIL_IF_SLAVE_IS_ALREADY_SELECTED)
{
  int8_t result, data;

  data = 42;

  mock().expectOneCall("SpiHw_IsSlaveBusy")
      .withParameter("slave", slave)
      .andReturnValue(TRUE);

  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_FAIL_SLAVE_BUSY, result);
}

IGNORE_TEST(Spi, TEST_SEND_DATA_SUCCESS)
{
  int8_t result, data;

  data = 42;

  //TODO set up mock here
  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_SUCCESS, result);
}
