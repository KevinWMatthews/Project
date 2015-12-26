#include "CircularBuffer.h"
// #include "Array.h"
#include "U08Array.h"
#include <stdlib.h>

// enum {BUFFER_GUARD = -999};



//******************************//
//*** Data type declarations ***//
//******************************//
typedef struct CircularBufferStruct
{
  s08 count;    // Current number of entries
  s08 index;
  s08 outdex;
  s08 capacity;
  const char * data_type;
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
CircularBuffer CircularBuffer_Create(CircularBuffer_DataType array_type, s08 capacity)
{
  CircularBuffer self = calloc(1, sizeof(CircularBufferStruct));
  RETURN_VALUE_IF_NULL(self, NULL);

  //TODO this needs to be dynamic :/
  //TODO move the +1 within the Array.
  switch (array_type)
  {
  case (CIRCULARBUFFER_U08):
    self->array = U08Array_Create(capacity+1);
    self->data_type = "U08";
    break;
  default:
    return NULL;
  }
  RETURN_VALUE_IF_NULL(self->array, NULL);

  self->capacity = capacity;
  return self;
}

//Carefule, we're passed a pointer to a pointer.
void CircularBuffer_Destroy(CircularBuffer * pointer_to_self)
{
  CircularBuffer self;

  RETURN_IF_NULL(pointer_to_self);
  self = *pointer_to_self; //I'm not sure that this helps...

  RETURN_IF_NULL(self);
  Array_Destroy(self->array); //Destroy the Array within the CircularBuffer
  free(self);                 //Free the memory that self is pointing to

  *pointer_to_self = (CircularBuffer)NULL; //Set self to NULL
}

const char* CircularBuffer_Type(CircularBuffer self)
{
  RETURN_VALUE_IF_NULL(self, "NULL");
  return self->data_type;
}

// BOOL CircularBuffer_VerifyIntegrity(CircularBuffer self)
// {
//   RETURN_VALUE_IF_NULL(self, FALSE);
//   return self->values[self->capacity] == BUFFER_GUARD;
// }

s08 CircularBuffer_Capacity(CircularBuffer self)
{
  RETURN_VALUE_IF_NULL(self, 0);
  return self->capacity;
}

BOOL CircularBuffer_IsEmpty(CircularBuffer self)
{
  RETURN_VALUE_IF_NULL(self, TRUE);
  return self->count == 0;
}

BOOL CircularBuffer_IsFull(CircularBuffer self)
{
  // RETURN_VALUE_IF_NULL(self, FALSE);
  return FALSE;//self->count == self->capacity;
}

s08 CircularBuffer_Put(CircularBuffer self, void * data)
{
  RETURN_VALUE_IF_NULL(self, CIRCULARBUFFER_NULL_POINTER);
  RETURN_VALUE_IF_NULL(data, CIRCULARBUFFER_NULL_POINTER);
  Array_Set(self->array, self->index, data);  //TODO Pass up return code from here?
  self->count++;
  self->index++;
  return CIRCLARBUFFER_SUCCESS;
}

s08 CircularBuffer_Get(CircularBuffer self, void * data)
{
  RETURN_VALUE_IF_NULL(self, CIRCULARBUFFER_NULL_POINTER);
  RETURN_VALUE_IF_NULL(data, CIRCULARBUFFER_NULL_POINTER);
  Array_Get(self->array, self->outdex, data);
  self->count--;
  self->outdex++;
  return CIRCLARBUFFER_SUCCESS;
}


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
