extern "C"
{
  #include "Array.h"
  #include "SpiCmdArray.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_SpiCmdArray.h"

TEST_GROUP(SpiCmd)
{
  void setup()
  {}

  void teardown()
  {}
};

TEST(SpiCmd, TEST_FAIL)
{
  FAIL("SpiCmd wiring check");
}
