#include "Array.h"
#include <stdlib.h>
#include <assert.h>

void Array_Destroy(Array self)
{
  assert(self != NULL);
  RETURN_IF_NULL(self);
  self->vtable->Destroy(self);
}

// static BOOL is_index_out_of_range(Array self, int8_t index);

// Array Array_Create(Array_DataType data_type, int8_t size)
// {
//   Array self = calloc(1, sizeof(ArrayStruct));
//   void * array = calloc(1, sizeof(int8_t));
//   //NULL check on array here? Probably the best spot; nip it in the bud.
//   self->size = size;
//   self->array = array;
//   return self;
// }

// BOOL Array_VerifyBufferIntegrity(Array self)
// {
//   return self->array[capacity] == 0;
// }

// int8_t Array_Get(Array self, int8_t index, void * return_value)
// {
//   int8_t * pointer = (int8_t *)return_value;
//   //NULL check on self!
//   //NULL check on return_value!

//   if (is_index_out_of_range(self, index) == TRUE)
//   {
//     *pointer = 0;
//     return ARRAY_ELEMENT_OUT_OF_BOUNDS;
//   }
//   *pointer = ((int8_t *)self->array)[index];
//   return ARRAY_SUCCESS;
// }

// int8_t Array_Set(Array self, int8_t index, void * value)
// {
//   int8_t *pointer = (int8_t *)value;
//   if (is_index_out_of_range(self, index) == TRUE)
//   {
//     return ARRAY_ELEMENT_OUT_OF_BOUNDS;
//   }
//   //NULL check on value!
//   //NULL check on self->array!
//   ((int8_t *)self->array)[index] = *pointer;
//   return ARRAY_SUCCESS;
// }

// static BOOL is_index_out_of_range(Array self, int8_t index)
// {
//   return index < 0 || index >= self->size;
// }
