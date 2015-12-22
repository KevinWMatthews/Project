extern "C"
{
  #include "Array.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Array.h"

#define ARRAY_SIZE 10

TEST_GROUP(Array)
{
  Array array;
  void setup()
  {
    array = Array_Create(ARRAY_INT8_T, 10);
  }

  void teardown()
  {
  }
};

TEST(Array, TEST_CREATE)
{
}

//TODO how to detect a memory leak??
TEST(Array, TEST_DESTROY)
{
  Array_Destroy(array);
}

TEST(Array, TEST_ELEMENTS_INITIALIZED_TO_EMPTY)
{
  int8_t value = 66;
  int8_t result = 66;
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    value = 66;
    result = 66;
    result = Array_Get(array, i, (void *)&value);
    LONGS_EQUAL(0, value);
    LONGS_EQUAL(ARRAY_SUCCESS, result);
  }
}

TEST(Array, TEST_GET_FAILS_IF_INDEX_IS_OUT_OF_RANGE)
{
  int8_t value = 66;
  int8_t result;

  result = Array_Get(array, -1, (void *)&value);
  LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(0, value);
  result = Array_Get(array, ARRAY_SIZE, (void *)&value);
  LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(0, value);
}

//Verify that the null terminator is intact
//I'm not sure that this is properly tested
// TEST(Array, TEST_VERIFY_BUFFER_INTEGRITY)
// {
//   CHECK_TRUE(Array_VerifyBufferIntegrity(array));
// }

TEST(Array, TEST_SET_FAILS_IF_INDEX_IS_OUT_OF_RANGE)
{
  int8_t value = 66;
  int8_t result;

  result = Array_Set(array, -1, (void *)&value);
  LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
  result = Array_Set(array, ARRAY_SIZE, (void *)&value);
  LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
}

TEST(Array, TEST_SET_FIRST_ARRAY_ELEMENT)
{
  int8_t set_value = 42;
  int8_t get_value = 0;
  int8_t result;

  result = Array_Set(array, 0, (void *)&set_value);
  Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(set_value, get_value);
}
