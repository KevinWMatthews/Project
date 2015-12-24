extern "C"
{
  #include "CircularBuffer.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_CircularBuffer.h"

TEST_GROUP(CircularBuffer)
{
  CircularBuffer buffer;

  void setup()
  {
    buffer = CircularBuffer_Create(10);
  }

  void teardown()
  {
    CircularBuffer_Destroy(&buffer);
    POINTERS_EQUAL(NULL, buffer);
  }
};

TEST(CircularBuffer, CreateAndDestroy)
{
}

TEST(CircularBuffer, DestroyWontSegfaultWithNullPointer)
{
  CircularBuffer null_pointer = NULL;
  CircularBuffer_Destroy(NULL);
  CircularBuffer_Destroy(&null_pointer);
}

// TEST_GROUP(CircularBuffer)
// {
//   #define BUFFER_SIZE 10
//   #define FLOAT_PRECISION 0.000001
//   CircularBuffer buffer;

//   void setup()
//   {
//     buffer = CircularBuffer_Create(BUFFER_SIZE);
//   }

//   void teardown()
//   {
//     CHECK_TRUE(CircularBuffer_VerifyIntegrity(buffer));
//     CircularBuffer_Destroy(&buffer);
//   }

//   void putManyInTheBuffer(int seed, int howMany)
//   {
//     for (int i = 0; i < howMany; i++)
//     {
//       CircularBuffer_Put(buffer, i+seed);
//     }
//   }
// };

// //*** Test CircularBuffer functionality ***//
// TEST(CircularBuffer, AllFunctionsCanHandleNullPointer)
// {
//   LONGS_EQUAL(FALSE, CircularBuffer_VerifyIntegrity(NULL));
//   LONGS_EQUAL(0, CircularBuffer_Capacity(NULL));
//   LONGS_EQUAL(TRUE, CircularBuffer_IsEmpty(NULL));
//   LONGS_EQUAL(FALSE, CircularBuffer_IsFull(NULL));
//   LONGS_EQUAL(FALSE, CircularBuffer_Put(NULL, 666));
//   LONGS_EQUAL(0, CircularBuffer_Get(NULL));
// }

// TEST(CircularBuffer, EmptyAfterCreation)
// {
//   CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
// }

// TEST(CircularBuffer, NotFullAfterCreation)
// {
//   CHECK_FALSE(CircularBuffer_IsFull(buffer));
// }

// TEST(CircularBuffer, NotEmptyThenEmpty)
// {
//   CircularBuffer_Put(buffer, 4567);
//   CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
//   CircularBuffer_Get(buffer);
//   CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
// }

// TEST(CircularBuffer, GetPutOneValue)
// {
//   CircularBuffer_Put(buffer, 4567);
//   LONGS_EQUAL(4567, CircularBuffer_Get(buffer));
// }

// TEST(CircularBuffer, GetPutAFew)
// {
//   CircularBuffer_Put(buffer, 1);
//   CircularBuffer_Put(buffer, 2);
//   CircularBuffer_Put(buffer, 3);
//   LONGS_EQUAL(1, CircularBuffer_Get(buffer));
//   LONGS_EQUAL(2, CircularBuffer_Get(buffer));
//   LONGS_EQUAL(3, CircularBuffer_Get(buffer));
// }

// TEST(CircularBuffer, Capacity)
// {
//   CircularBuffer b = CircularBuffer_Create(2);
//   LONGS_EQUAL(2, CircularBuffer_Capacity(b));
//   CircularBuffer_Destroy(&b);
// }

// TEST(CircularBuffer, IsFull)
// {
//   for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
//   {
//     CircularBuffer_Put(buffer, i+100);
//   }

//   CHECK_TRUE(CircularBuffer_IsFull(buffer));
// }

// TEST(CircularBuffer, EmptyToFullToEmpty)
// {
//   for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
//   {
//     CircularBuffer_Put(buffer, i+100);
//   }
//   CHECK_TRUE(CircularBuffer_IsFull(buffer));

//   for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
//   {
//     LONGS_EQUAL(j+100, CircularBuffer_Get(buffer));
//   }

//   CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
//   CHECK_FALSE(CircularBuffer_IsFull(buffer));
// }

// TEST(CircularBuffer, WrapAround)
// {
//   int capacity = CircularBuffer_Capacity(buffer);
//   putManyInTheBuffer(100, capacity);

//   CHECK_TRUE(CircularBuffer_IsFull(buffer));
//   LONGS_EQUAL(100, CircularBuffer_Get(buffer));
//   CHECK_FALSE(CircularBuffer_IsFull(buffer));
//   CircularBuffer_Put(buffer, 1000);
//   CHECK_TRUE(CircularBuffer_IsFull(buffer));

//   for (int i = 1; i < capacity; i++)
//   {
//     LONGS_EQUAL(i+100, CircularBuffer_Get(buffer));
//   }

//   LONGS_EQUAL(1000, CircularBuffer_Get(buffer));
//   CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
// }

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
