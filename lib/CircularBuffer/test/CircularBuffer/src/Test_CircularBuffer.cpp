extern "C"
{
  #include "CircularBuffer.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_CircularBuffer.h"

TEST_GROUP(CircularBuffer_Init)
{
  CircularBuffer buffer;

  void setup()
  {
    buffer = CircularBuffer_Create(42);
  }

  void teardown()
  {
    CircularBuffer_Destroy(&buffer);
  }
};

TEST_GROUP(CircularBuffer)
{
  #define BUFFER_SIZE 10
  #define FLOAT_PRECISION 0.000001
  CircularBuffer buffer;

  void setup()
  {
    buffer = CircularBuffer_Create(BUFFER_SIZE);
  }

  void teardown()
  {
    CHECK_TRUE(CircularBuffer_VerifyIntegrity(buffer));
    CircularBuffer_Destroy(&buffer);
  }

  void putManyInTheBuffer(int seed, int howMany)
  {
    for (int i = 0; i < howMany; i++)
    {
      CircularBuffer_Put(buffer, i+seed);
    }
  }

  // Step is assumed to be 1 (n, n+1, n+2, ...)
  float calculateAverage(int first, int last)
  {
    return (first + last) / 2.0;
  }
};

//*** Test Create() and Destroy() ***//
TEST(CircularBuffer_Init, Create)
{
  //TODO learn how to detect a memory leak if free() isn't called!
}

TEST(CircularBuffer_Init, DestroyCanHandleNullPointer)
{
  CircularBuffer_Destroy(NULL);
}

TEST(CircularBuffer_Init, DestroyClearsPointer)
{
  CircularBuffer_Destroy(&buffer);
  POINTERS_EQUAL(NULL, buffer);
}

TEST(CircularBuffer_Init, CanDestroySameBufferTwice)
{
  CircularBuffer_Destroy(&buffer);
  CircularBuffer_Destroy(&buffer);
}

//*** Test CircularBuffer functionality ***//
TEST(CircularBuffer, AllFunctionsCanHandleNullPointer)
{
  LONGS_EQUAL(FALSE, CircularBuffer_VerifyIntegrity(NULL));
  LONGS_EQUAL(0, CircularBuffer_Capacity(NULL));
  LONGS_EQUAL(TRUE, CircularBuffer_IsEmpty(NULL));
  LONGS_EQUAL(FALSE, CircularBuffer_IsFull(NULL));
  LONGS_EQUAL(FALSE, CircularBuffer_Put(NULL, 666));
  LONGS_EQUAL(0, CircularBuffer_Get(NULL));
  DOUBLES_EQUAL(0, CircularBuffer_Average(NULL), FLOAT_PRECISION);
}

TEST(CircularBuffer, EmptyAfterCreation)
{
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation)
{
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmptyThenEmpty)
{
  CircularBuffer_Put(buffer, 4567);
  CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
  CircularBuffer_Get(buffer);
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetPutOneValue)
{
  CircularBuffer_Put(buffer, 4567);
  LONGS_EQUAL(4567, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, GetPutAFew)
{
  CircularBuffer_Put(buffer, 1);
  CircularBuffer_Put(buffer, 2);
  CircularBuffer_Put(buffer, 3);
  LONGS_EQUAL(1, CircularBuffer_Get(buffer));
  LONGS_EQUAL(2, CircularBuffer_Get(buffer));
  LONGS_EQUAL(3, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Capacity)
{
  CircularBuffer b = CircularBuffer_Create(2);
  LONGS_EQUAL(2, CircularBuffer_Capacity(b));
  CircularBuffer_Destroy(&b);
}

TEST(CircularBuffer, IsFull)
{
  for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    CircularBuffer_Put(buffer, i+100);
  }

  CHECK_TRUE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, EmptyToFullToEmpty)
{
  for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    CircularBuffer_Put(buffer, i+100);
  }
  CHECK_TRUE(CircularBuffer_IsFull(buffer));

  for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
  {
    LONGS_EQUAL(j+100, CircularBuffer_Get(buffer));
  }

  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, WrapAround)
{
  int capacity = CircularBuffer_Capacity(buffer);
  putManyInTheBuffer(100, capacity);

  CHECK_TRUE(CircularBuffer_IsFull(buffer));
  LONGS_EQUAL(100, CircularBuffer_Get(buffer));
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
  CircularBuffer_Put(buffer, 1000);
  CHECK_TRUE(CircularBuffer_IsFull(buffer));

  for (int i = 1; i < capacity; i++)
  {
    LONGS_EQUAL(i+100, CircularBuffer_Get(buffer));
  }

  LONGS_EQUAL(1000, CircularBuffer_Get(buffer));
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, PutToFullReturnsFalse)
{
  putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
  CHECK_FALSE(CircularBuffer_Put(buffer, 9999));
}

TEST(CircularBuffer, PutToFullDoesNotDamageContents)
{
  putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

  CircularBuffer_Put(buffer, 9999);

  for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
  {
    LONGS_EQUAL(i+900, CircularBuffer_Get(buffer));
  }

  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetFromEmptyReturns0)
{
  LONGS_EQUAL(0, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, AverageWithEmptyBuffer)
{
  LONGS_EQUAL(0, CircularBuffer_Average(buffer));
}

TEST(CircularBuffer, AverageWithOneEntryAtBeginning)
{
  CircularBuffer_Put(buffer, 42);
  LONGS_EQUAL(42, CircularBuffer_Average(buffer));
}

TEST(CircularBuffer, AverageWithOneEntryInMiddle)
{
  CircularBuffer_Put(buffer, 42);
  CircularBuffer_Put(buffer, 52);
  CircularBuffer_Get(buffer);
  LONGS_EQUAL(52, CircularBuffer_Average(buffer));
}

TEST(CircularBuffer, AverageWithSeveralEntries)
{
  CircularBuffer_Put(buffer, 48);
  CircularBuffer_Put(buffer, 52);
  LONGS_EQUAL(50, CircularBuffer_Average(buffer));
}

TEST(CircularBuffer, AverageWithFullBuffer)
{
  float ave;
  putManyInTheBuffer(100, BUFFER_SIZE);
  ave = calculateAverage(100, 100+BUFFER_SIZE-1);
  DOUBLES_EQUAL(ave, CircularBuffer_Average(buffer), FLOAT_PRECISION);
}

TEST(CircularBuffer, FloatingPointAverage)
{
  CircularBuffer_Put(buffer, 33);
  CircularBuffer_Put(buffer, 33);
  CircularBuffer_Put(buffer, 34);
  DOUBLES_EQUAL(33.333333, CircularBuffer_Average(buffer), FLOAT_PRECISION);
}

TEST(CircularBuffer, AverageWrapAround)
{
  float ave;
  putManyInTheBuffer(10, 10);     // Fill buffer with 10-19
  CircularBuffer_Get(buffer);
  CircularBuffer_Put(buffer, 20); // Buffer now holds 11-20
  ave = calculateAverage(11, 20);
  DOUBLES_EQUAL(ave, CircularBuffer_Average(buffer), FLOAT_PRECISION);
}
