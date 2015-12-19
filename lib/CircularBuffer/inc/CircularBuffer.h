#ifndef D_CircularBuffer_H_
#define D_CircularBuffer_H_

#include <stdint.h>
#include "DataTypes.h"

typedef struct CircularBufferStruct* CircularBuffer;

CircularBuffer CircularBuffer_Create(uint8_t capacity);
void CircularBuffer_Destroy(CircularBuffer* self);
BOOL CircularBuffer_VerifyIntegrity(CircularBuffer self);
int8_t CircularBuffer_Capacity(CircularBuffer self);
BOOL CircularBuffer_IsEmpty(CircularBuffer self);
BOOL CircularBuffer_IsFull(CircularBuffer self);
BOOL CircularBuffer_Put(CircularBuffer self, int16_t value);
int16_t CircularBuffer_Get(CircularBuffer self);
float CircularBuffer_Average(CircularBuffer self);

#endif