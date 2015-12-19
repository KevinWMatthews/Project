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
  uint8_t dummyRegister;
  int8_t data;
  int8_t result;

  void setup()
  {
    slave         = &dummyRegister;
    dummyRegister = 0;
    data          = 42;
    result        = 66; //Something that won't yield a false positive
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(SpiApi, TEST_SEND_FAILS_IF_MASTER_NOT_READY)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(FALSE);

  result = SpiApi_Send(slave, data);
  LONGS_EQUAL(SPIAPI_MASTER_NOT_READY, result);
}

TEST(SpiApi, TEST_SEND_FAILS_IF_SLAVE_NOT_READY)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_IsSlaveReady")
        .withParameter("slave", slave)
        .andReturnValue(FALSE);
  result = SpiApi_Send(slave, data);
  LONGS_EQUAL(SPIAPI_SLAVE_NOT_READY, result);
}

TEST(SpiApi, TEST_SEND_FAILS_IF_DATA_PREPARATION_FAILS)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_IsSlaveReady")
        .withParameter("slave", slave)
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_PrepareDataForSend")
        .withParameter("data", data)
        .andReturnValue(FALSE);

  result = SpiApi_Send(slave, data);
  LONGS_EQUAL(SPIAPI_PREPARE_DATA_FAIL, result);
}

TEST(SpiApi, TEST_SEND_SEND_SUCCESS)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_IsSlaveReady")
        .withParameter("slave", slave)
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_PrepareDataForSend")
        .withParameter("data", data)
        .andReturnValue(TRUE);
  mock().expectOneCall("SpiHw_StartTransmission");
  result = SpiApi_Send(slave, data);
  LONGS_EQUAL(SPIAPI_SUCCESS, result);
}

TEST(SpiApi, TEST_GET_FAILS_IF_MASTER_NOT_READY)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(FALSE);
  result = SpiApi_Get(slave, &data);
  LONGS_EQUAL(SPIAPI_MASTER_NOT_READY, result);
  LONGS_EQUAL(0, data);
}

TEST(SpiApi, TEST_GET_FAILS_IF_SEND_FAILS)
{
  mock().expectOneCall("SpiHw_IsMasterReady")
        .andReturnValue(TRUE);
  //How do I test SpiApi_Send?
}
