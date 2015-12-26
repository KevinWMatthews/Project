extern "C"
{
  #include "CircularBuffer.h"
  #include "U08Array.h" //TODO replace with dummy or spy
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_CircularBuffer.h"

TEST_GROUP(CircularBuffer)
{
  CircularBuffer buffer;

  void setup()
  {
    buffer = CircularBuffer_Create(CIRCULARBUFFER_U08, 10);
  }

  void teardown()
  {
    CircularBuffer_Destroy(&buffer);
    POINTERS_EQUAL(NULL, buffer);
  }
};

TEST(CircularBuffer, CreateAndDestroy)
{
  STRCMP_EQUAL("U08", CircularBuffer_Type(buffer));
}

TEST(CircularBuffer, DestroyWontSegfaultWithNullPointer)
{
  CircularBuffer null_pointer = NULL;
  CircularBuffer_Destroy(NULL);
  CircularBuffer_Destroy(&null_pointer);
}

TEST(CircularBuffer, FunctionsWontSegfaultWithNullPointer)
{
  u08 data = 0;
  STRCMP_EQUAL("NULL", CircularBuffer_Type(NULL));
  LONGS_EQUAL(0, CircularBuffer_Capacity(NULL));
  CircularBuffer_IsEmpty(NULL);
  CircularBuffer_IsFull(NULL);
  LONGS_EQUAL(CIRCULARBUFFER_NULL_POINTER, CircularBuffer_Put(NULL, &data));
  LONGS_EQUAL(CIRCULARBUFFER_NULL_POINTER, CircularBuffer_Put(buffer, NULL));
  LONGS_EQUAL(CIRCULARBUFFER_NULL_POINTER, CircularBuffer_Get(NULL, &data));
  LONGS_EQUAL(CIRCULARBUFFER_NULL_POINTER, CircularBuffer_Get(buffer, NULL));
}

TEST(CircularBuffer, EmptyAfterCreation)
{
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation)
{
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, GetPutOneValue)
{
  u08 input = 123;
  u08 output = 0;
  s08 return_value = 1;

  return_value = CircularBuffer_Put(buffer, &input);
  LONGS_EQUAL(CIRCLARBUFFER_SUCCESS, return_value);

  return_value = CircularBuffer_Get(buffer, &output);
  LONGS_EQUAL(CIRCLARBUFFER_SUCCESS, return_value);
  LONGS_EQUAL(123, output);
}

TEST(CircularBuffer, NotEmptyThenEmpty)
{
  u08 input = 123;
  u08 output = 0;

  CircularBuffer_Put(buffer, &input);
  CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
  CircularBuffer_Get(buffer, &output);
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, PutAndGetAFew)
{
  u08 input = 1;
  u08 output = 0;

  CircularBuffer_Put(buffer, &input);
  input++;
  CircularBuffer_Put(buffer, &input);
  input++;
  CircularBuffer_Put(buffer, &input);

  CircularBuffer_Get(buffer, &output);
  LONGS_EQUAL(1, output);
  CircularBuffer_Get(buffer, &output);
  LONGS_EQUAL(2, output);
  CircularBuffer_Get(buffer, &output);
  LONGS_EQUAL(3, output);
}

TEST(CircularBuffer, Capacity)
{
  CircularBuffer b = CircularBuffer_Create(CIRCULARBUFFER_U08, 2);
  LONGS_EQUAL(2, CircularBuffer_Capacity(b));
  CircularBuffer_Destroy(&b);
}

TEST(CircularBuffer, IsFull)
{
  for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    u08 data = i + 10;
    CircularBuffer_Put(buffer, &data);
  }

  CHECK_TRUE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, EmptyToFullToEmpty)
{
  u08 data;
  for (u08 i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    data = i + 10;
    CircularBuffer_Put(buffer, &data);
  }
  CHECK_TRUE(CircularBuffer_IsFull(buffer));

  for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
  {
    CircularBuffer_Get(buffer, &data);
    LONGS_EQUAL(j + 10, data);
  }

  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, WrapAround)
{
  int capacity = CircularBuffer_Capacity(buffer);
  u08 data = 0;

  //Fill buffer
  for (u08 i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    data = i + 10;
    CircularBuffer_Put(buffer, &data);
  }
  CHECK_TRUE(CircularBuffer_IsFull(buffer));

  //Get first element
  CircularBuffer_Get(buffer, &data);
  LONGS_EQUAL(10, data);
  CHECK_FALSE(CircularBuffer_IsFull(buffer));

  //Refill the first buffer element with a unique value
  data = 200;
  CircularBuffer_Put(buffer, &data);
  CHECK_TRUE(CircularBuffer_IsFull(buffer));

  //Get the remaining elements
  for (int i = 1; i < capacity; i++)
  {
    CircularBuffer_Get(buffer, &data);
    LONGS_EQUAL(i+10, data);
  }

  //Get our unique first element
  CircularBuffer_Get(buffer, &data);
  LONGS_EQUAL(200, data);
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

// TEST(CircularBuffer, PutToFullReturnsFalse)
// {
//   putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
//   CHECK_FALSE(CircularBuffer_Put(buffer, 9999));
// }

// TEST(CircularBuffer, PutToFullDoesNotDamageContents)
// {
//   putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

//   CircularBuffer_Put(buffer, 9999);

//   for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
//   {
//     LONGS_EQUAL(i+900, CircularBuffer_Get(buffer));
//   }

//   CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
// }

// TEST(CircularBuffer, GetFromEmptyReturns0)
// {
//   LONGS_EQUAL(0, CircularBuffer_Get(buffer));
// }
