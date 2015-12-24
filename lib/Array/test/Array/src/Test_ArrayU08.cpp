extern "C"
{
  #include "Array.h"
  #include "ArrayU08.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_ArrayU08.h"

#define ARRAY_SIZE 10

TEST_GROUP(ArrayU08)
{
  Array array;
  void setup()
  {
    array = ArrayU08_Create(ARRAY_SIZE);
  }

  void teardown()
  {
      Array_Destroy(array);
  }
};

TEST(ArrayU08, TEST_CREATE_AND_DESTROY)
{
}

TEST(ArrayU08, TEST_ELEMENTS_INITIALIZED_TO_EMPTY)
{
  s08 value = 66;
  s08 result = 66;
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    value = 66;
    result = 66;
    result = Array_Get(array, i, (void *)&value);
    LONGS_EQUAL(0, value);
    LONGS_EQUAL(ARRAY_SUCCESS, result);
  }
}

// TEST(ArrayU08, TEST_GET_FAILS_IF_INDEX_IS_OUT_OF_RANGE)
// {
//   s08 value = 66;
//   s08 result;

//   result = Array_Get(array, -1, (void *)&value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
//   LONGS_EQUAL(0, value);
//   result = Array_Get(array, ARRAY_SIZE, (void *)&value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
//   LONGS_EQUAL(0, value);
// }

// //Verify that the null terminator is intact
// //I'm not sure that this is properly tested
// // TEST(ArrayU08, TEST_VERIFY_BUFFER_INTEGRITY)
// // {
// //   CHECK_TRUE(Array_VerifyBufferIntegrity(array));
// // }

// TEST(ArrayU08, TEST_SET_FAILS_IF_INDEX_IS_OUT_OF_RANGE)
// {
//   s08 value = 66;
//   s08 result;

//   result = Array_Set(array, -1, (void *)&value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
//   result = Array_Set(array, ARRAY_SIZE, (void *)&value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
// }

TEST(ArrayU08, TEST_SET_FIRST_ARRAY_ELEMENT)
{
  s08 set_value = 42;
  s08 get_value = 0;
  s08 result;

  result = Array_Set(array, 0, (void *)&set_value);
  Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(set_value, get_value);
}
