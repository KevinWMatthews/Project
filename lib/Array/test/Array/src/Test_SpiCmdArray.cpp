extern "C"
{
  #include "Array.h"
  #include "SpiCmdArray.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_SpiCmdArray.h"

#define ARRAY_SIZE 10

TEST_GROUP(SpiCmd)
{
  Array array;

  void setup()
  {}

  void teardown()
  {}
};

TEST(SpiCmd, TEST_CREATE)
{
  array = SpiCmdArray_Create(ARRAY_SIZE);
}

TEST(SpiCmd, TEST_DESTROY)
{
  Array_Destroy(array);
}
