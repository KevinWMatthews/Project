extern "C"
{
  #include "Array.h"
  #include "ArrayU08.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_ArrayU08.h"

#define ARRAY_SIZE 10
#define GET_INITIAL 66  //Used to detect accidental modifications ot the get_value pointer
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

TEST(ArrayU08, TEST_ELEMENT_INITIALIZED_TO_EMPTY)
{
  get_value = GET_INITIAL;
  result    = RESULT_INITIAL;
  result = Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(0, get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
}

TEST(ArrayU08, TEST_SET_FIRST_ARRAY_ELEMENT)
{
  result = Array_Set(array, 0, (void *)&set_value);
  Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(set_value, get_value);
}

TEST(ArrayU08, TEST_SET_FIRST_ARRAY_ELEMENT_AGAIN)  //I'm tired.
{
  set_value = 7;
  result = Array_Set(array, 0, (void *)&set_value);
  Array_Get(array, 0, (void *)&get_value);
  LONGS_EQUAL(ARRAY_SUCCESS, result);
  LONGS_EQUAL(set_value, get_value);
}
