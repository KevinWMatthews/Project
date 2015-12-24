extern "C"
{
  #include "Array.h"
  #include "ArrayU08.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_ArrayU08.h"

#define ARRAY_SIZE 10
#define GET_INITIAL 66
#define SET_INITIAL 42
#define RESULT_INITIAL 77

TEST_GROUP(ArrayU08)
{
  Array array;
  s08 get_value;
  s08 set_value;
  s08 result;

  void setup()
  {
    array = ArrayU08_Create(ARRAY_SIZE);
    get_value = GET_INITIAL;
    set_value = SET_INITIAL;
    result    = RESULT_INITIAL;
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
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    get_value = GET_INITIAL;
    result    = RESULT_INITIAL;
    result = Array_Get(array, i, (void *)&get_value);
    LONGS_EQUAL(0, get_value);
    LONGS_EQUAL(ARRAY_SUCCESS, result);
  }
}

TEST(ArrayU08, TEST_GET_FAILS_IF_INDEX_IS_TOO_SMALL)
{
  result = Array_Get(array, -1, (void *)&get_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(GET_INITIAL, get_value);
}

TEST(ArrayU08, TEST_GET_FAILS_IF_INDEX_IS_TOO_LARGE)
{
  result = Array_Get(array, ARRAY_SIZE, (void *)&get_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(GET_INITIAL, get_value);
}

// //Verify that the null terminator is intact
// //I'm not sure that this is properly tested
// // TEST(ArrayU08, TEST_VERIFY_BUFFER_INTEGRITY)
// // {
// //   CHECK_TRUE(Array_VerifyBufferIntegrity(array));
// // }

// TEST(ArrayU08, TEST_SET_FAILS_IF_INDEX_IS_OUT_OF_RANGE)
// {
//   s08 get_value = 66;
//   s08 result;

//   result = Array_Set(array, -1, (void *)&get_value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
//   result = Array_Set(array, ARRAY_SIZE, (void *)&get_value);
//   LONGS_EQUAL(ARRAY_ELEMENT_OUT_OF_BOUNDS, result);
// }

TEST(ArrayU08, TEST_SET_FIRST_ARRAY_ELEMENT)
{
  result = Array_Set(array, 0, (void *)&set_value);
  Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(set_value, get_value);
}
