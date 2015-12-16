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
  SpiSlaveSelect slave;
  void setup()
  {
    slave = NULL;
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(Spi, TEST_SEND_DATA_SUCCESS)
{
  int8_t result, data;

  data = 42;

  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_SUCCESS, result);
}
