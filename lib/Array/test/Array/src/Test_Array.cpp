extern "C"
{
  #include "Array.h"
  #include "DummyArray.h"
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

TEST(Array, TEST_FAIL)
{
  FAIL("Test Array wiring check");
}
