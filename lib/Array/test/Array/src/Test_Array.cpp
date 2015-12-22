extern "C"
{
  #include "Array.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Array.h"

TEST_GROUP(Array)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Array, TEST_WIRING_CHECK)
{
  FAIL("Array test wiring check\n");
}
