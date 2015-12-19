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
  void setup()
  {
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

TEST(SpiApi, TEST_FAIL)
{
  FAIL("Testing SpiApi!");
}
