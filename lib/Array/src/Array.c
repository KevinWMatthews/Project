#include "Array.h"
#include <stdlib.h>
#include <assert.h>

static BOOL is_index_out_of_range(Array self, s08 index);

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

  if (is_index_out_of_range(self, index))
  {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }
  return self->vtable->Get(self, index, return_value);
}

s08 Array_Set(Array self, s08 index, void * value)
{
  RETURN_VALUE_IF_NULL(self, ARRAY_NULL_POINTER);
  RETURN_VALUE_IF_NULL(value, ARRAY_NULL_POINTER);
  assert(self->vtable->Set != NULL);

  if (is_index_out_of_range(self, index))
  {
    return ARRAY_INDEX_OUT_OF_BOUNDS;
  }
  return self->vtable->Set(self, index, value);
}

static BOOL is_index_out_of_range(Array self, s08 index)
{
  return index < 0 || index >= self->size;
}
