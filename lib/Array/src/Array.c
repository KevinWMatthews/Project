#include "Array.h"
#include <stdlib.h>
#include <assert.h>

void Array_Destroy(Array self)
{
  RETURN_IF_NULL(self);
  assert(self->vtable->Destroy != NULL);
  self->vtable->Destroy(self);
}

s08 Array_Get(Array self, s08 index, void * return_value)
{
  RETURN_VALUE_IF_NULL(self, ARRAY_NULL_POINTER);
  RETURN_VALUE_IF_NULL(return_value, ARRAY_NULL_POINTER);
  assert(self->vtable->Get != NULL);

  if (index < 0 || index >= self->size)
  {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }
  return self->vtable->Get(self, index, return_value);
}

s08 Array_Set(Array self, s08 index, void * value)
{
  assert(self->vtable->Set != NULL);
  if (index < 0 || index >= self->size)
  {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }
  return self->vtable->Set(self, index, value);
}

// static BOOL is_index_out_of_range(Array self, s08 index);

// Array Array_Create(Array_DataType data_type, s08 size)
// {
//   Array self = calloc(1, sizeof(ArrayStruct));
//   void * array = calloc(1, sizeof(s08));
//   //NULL check on array here? Probably the best spot; nip it in the bud.
//   self->size = size;
//   self->array = array;
//   return self;
// }

// BOOL Array_VerifyBufferIntegrity(Array self)
// {
//   return self->array[capacity] == 0;
// }

// s08 Array_Get(Array self, s08 index, void * return_value)
// {
//   s08 * pointer = (s08 *)return_value;
//   //NULL check on self!
//   //NULL check on return_value!

//   if (is_index_out_of_range(self, index) == TRUE)
//   {
//     *pointer = 0;
//     return ARRAY_ELEMENT_OUT_OF_BOUNDS;
//   }
//   *pointer = ((s08 *)self->array)[index];
//   return ARRAY_SUCCESS;
// }

// s08 Array_Set(Array self, s08 index, void * value)
// {
//   s08 *pointer = (s08 *)value;
//   if (is_index_out_of_range(self, index) == TRUE)
//   {
//     return ARRAY_ELEMENT_OUT_OF_BOUNDS;
//   }
//   //NULL check on value!
//   //NULL check on self->array!
//   ((s08 *)self->array)[index] = *pointer;
//   return ARRAY_SUCCESS;
// }

// static BOOL is_index_out_of_range(Array self, s08 index)
// {
//   return index < 0 || index >= self->size;
// }
