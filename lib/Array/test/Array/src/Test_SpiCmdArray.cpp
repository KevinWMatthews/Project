extern "C"
{
  #include "Array.h"
  #include "SpiCmdArray.h"
  #include "SpiCommand.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_SpiCmdArray.h"

#define ARRAY_SIZE 10

TEST_GROUP(SpiCmd)
{
  Array array;
  SpiCommandStruct spi_cmd;
  s08 result;

  void setup()
  {
    array = SpiCmdArray_Create(ARRAY_SIZE);
    result = 66;

    spi_cmd.command_type = 1;
    spi_cmd.data = 7;
  }

  void teardown()
  {
    Array_Destroy(array);
  }
};

TEST(SpiCmd, TEST_CREATE_AND_DESTROY)
{
}

TEST(SpiCmd, TEST_GET_SPI_COMMAND)
{
  result = Array_Get(array, 0, (void *)&spi_cmd);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(0, spi_cmd.command_type);
  LONGS_EQUAL(0, spi_cmd.data);
}
