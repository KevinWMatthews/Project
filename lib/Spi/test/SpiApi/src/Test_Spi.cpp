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
  int8_t result, data;
  RegisterPointer slave;
  uint8_t dummySlaveSelectRegister;

  void setup()
  {
    data   = 42;
    result = -120;
    slave  = &dummySlaveSelectRegister;
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(Spi, TEST_SEND_FAILS_IF_SLAVE_IS_NULL)
{
  result = Spi_Send(NULL, data);
  LONGS_EQUAL(SPI_FAIL_NULL_SLAVE, result);
}

TEST(Spi, TEST_SEND_FAILS_IF_SLAVE_IS_ALREADY_SELECTED)
{
  mock().expectOneCall("SpiHw_IsSlaveBusy")
        .withParameter("slave", slave)
        .andReturnValue(TRUE);

  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_FAIL_SLAVE_BUSY, result);
}

TEST(Spi, TEST_SEND_FAILS_IF_USI_COUNTER_IS_NONZERO)
{
  mock().expectOneCall("SpiHw_IsSlaveBusy")
        .withParameter("slave", slave)
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_GetUsiCounter")
        .andReturnValue(1);
  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_FAIL_USI_COUNTER_NONZERO, result);
}

IGNORE_TEST(Spi, TEST_SEND_DATA_SUCCESS)
{
  //TODO set up mock here
  result = Spi_Send(slave, data);
  LONGS_EQUAL(SPI_SUCCESS, result);
}
