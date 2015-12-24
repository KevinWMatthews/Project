extern "C"
{
  #include "Array.h"
  #include "DummyArray.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_Array.h"

#define ARRAY_SIZE 10
#define GET_INITIAL 66  //Used to detect accidental modifications ot the get_value pointer
#define SET_INITIAL 42
#define RESULT_INITIAL 77


TEST_GROUP(Array)
{
  Array array;
  s08 get_value;
  s08 set_value;
  s08 result;

  void setup()
  {
    array = DummyArray_Create(ARRAY_SIZE);
    get_value = GET_INITIAL;
    set_value = SET_INITIAL;
    result    = RESULT_INITIAL;
  }

  void teardown()
  {
    Array_Destroy(array);
  }
};

TEST(Array, TEST_CREATE_AND_DESTROY)
{
}

TEST(Array, TEST_DESTROY_WONT_SEGFAULT_WITH_NULL)
{
  Array_Destroy(NULL);
}

TEST(Array, TEST_GET_WONT_SEGFAULT_WITH_NULL)
{
  result = Array_Get(NULL, 1, (void*)&get_value);
  LONGS_EQUAL(ARRAY_NULL_POINTER, result);

  result = RESULT_INITIAL;
  result = Array_Get(array, 1, NULL);
  LONGS_EQUAL(ARRAY_NULL_POINTER, result);
}

TEST(Array, TEST_GET_FAILS_IF_INDEX_IS_TOO_SMALL)
{
  result = Array_Get(array, -1, (void *)&get_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(GET_INITIAL, get_value);
}

TEST(Array, TEST_GET_FAILS_IF_INDEX_IS_TOO_LARGE)
{
  result = Array_Get(array, ARRAY_SIZE, (void *)&get_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(GET_INITIAL, get_value);
}

TEST(Array, TEST_SET_WONT_SEGFAULT_WITH_NULL)
{
  result = Array_Set(NULL, 1, (void*)&set_value);
  LONGS_EQUAL(ARRAY_NULL_POINTER, result);

  result = RESULT_INITIAL;
  result = Array_Set(array, 1, NULL);
  LONGS_EQUAL(ARRAY_NULL_POINTER, result);
}

TEST(Array, TEST_SET_FAILS_IF_INDEX_IS_TOO_SMALL)
{
  result = Array_Set(array, -1, (void *)&set_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(SET_INITIAL, set_value);
}

TEST(Array, TEST_SET_FAILS_IF_INDEX_IS_TOO_LARGE)
{
  result = Array_Set(array, ARRAY_SIZE, (void *)&set_value);
  LONGS_EQUAL(ARRAY_INDEX_OUT_OF_BOUNDS, result);
  LONGS_EQUAL(SET_INITIAL, set_value);
}
