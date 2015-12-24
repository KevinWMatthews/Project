#include "CircularBuffer.h"
#include "Array.h"
#include <stdlib.h>

// enum {BUFFER_GUARD = -999};



//******************************//
//*** Data type declarations ***//
//******************************//
typedef struct CircularBufferStruct
{
  uint8_t count;    // Current number of entries
  uint8_t index;
  uint8_t outdex;
  uint8_t capacity;
  Array array;      // Pointer to the actual buffer
} CircularBufferStruct;



//*****************************//
//*** Function declarations ***//
//*****************************//



//***************************************//
//*** File-scope variable definitions ***//
//***************************************//



//****************************//
//*** Function definitions ***//
//****************************//
CircularBuffer CircularBuffer_Create(s08 capacity)
{
  // CircularBuffer self = calloc(1, sizeof(CircularBufferStruct));
  // self->values = calloc(capacity + 1, sizeof(int16_t));
  // self->values[capacity] = BUFFER_GUARD;
  // self->capacity = capacity;
  // return self;
  return NULL;
}

// void CircularBuffer_Destroy(CircularBuffer* self)
// {
//   RETURN_IF_NULL(self);
//   RETURN_IF_NULL(*self);
//   RETURN_IF_NULL((*self)->values);

//   free((*self)->values);
//   free(*self);
//   *self = NULL;
// }

// BOOL CircularBuffer_VerifyIntegrity(CircularBuffer self)
// {
//   RETURN_VALUE_IF_NULL(self, FALSE);
//   return self->values[self->capacity] == BUFFER_GUARD;
// }

// int8_t CircularBuffer_Capacity(CircularBuffer self)
// {
//   RETURN_VALUE_IF_NULL(self, 0);
//   return self->capacity;
// }

// BOOL CircularBuffer_IsEmpty(CircularBuffer self)
// {
//   RETURN_VALUE_IF_NULL(self, TRUE);
//   return self->count == 0;
// }

// BOOL CircularBuffer_IsFull(CircularBuffer self)
// {
//   RETURN_VALUE_IF_NULL(self, FALSE);
//   return self->count == self->capacity;
// }

// BOOL CircularBuffer_Put(CircularBuffer self, int16_t value)
// {
//   RETURN_VALUE_IF_NULL(self, FALSE);
//   if (self->count >= self->capacity)
//   {
//     return FALSE;
//   }

//   self->values[self->index++] = value;
//   self->count++;
//   if (self->index >= self->capacity)
//   {
//     self->index = 0;
//   }
//   return TRUE;
// }

// int16_t CircularBuffer_Get(CircularBuffer self)
// {
//   int16_t value;

//   RETURN_VALUE_IF_NULL(self, 0);
//   if (self->count <= 0)
//   {
//     return 0;
//   }

//   value = self->values[self->outdex++];
//   self->count--;
//   if (self->outdex >= self->capacity)
//   {
//     self->outdex = 0;
//   }
//   return value;
// }
