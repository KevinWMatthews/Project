#ifndef D_CircularBuffer_H_
#define D_CircularBuffer_H_

#include "DataTypes.h"

typedef struct CircularBufferStruct * CircularBuffer;

typedef enum
{
  CIRCULARBUFFER_U08
} CircularBuffer_DataType;
CircularBuffer CircularBuffer_Create(CircularBuffer_DataType array_type, s08 capacity);
void CircularBuffer_Destroy(CircularBuffer * self);

const char* CircularBuffer_Type(CircularBuffer self);
// BOOL CircularBuffer_VerifyIntegrity(CircularBuffer self);
s08 CircularBuffer_Capacity(CircularBuffer self);
BOOL CircularBuffer_IsEmpty(CircularBuffer self);
BOOL CircularBuffer_IsFull(CircularBuffer self);
enum
{
  CIRCULARBUFFER_FULL         = -2,
  CIRCULARBUFFER_NULL_POINTER = -1,
  CIRCLARBUFFER_SUCCESS       = 0
};
s08 CircularBuffer_Put(CircularBuffer self, void * data);
s08 CircularBuffer_Get(CircularBuffer self, void * data);

#endif
