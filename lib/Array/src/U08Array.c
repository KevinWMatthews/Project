#include "U08Array.h"
#include <stdlib.h>



//******************************//
//*** Data type declarations ***//
//******************************//
typedef struct U08ArrayStruct
{
  ArrayStruct base;
  u08 *array;
} U08ArrayStruct;



//*****************************//
//*** Function declarations ***//
//*****************************//
static void U08Array_Destroy(Array super);
static s08 U08Array_Get(Array super, s08 index, void * return_value);
static s08 U08Array_Set(Array super, s08 index, void * value);



//***************************************//
//*** File-scope variable definitions ***//
//***************************************//
static ArrayInterfaceStruct interface = {
  .Destroy = U08Array_Destroy,
  .Get = U08Array_Get,
  .Set = U08Array_Set
};



//****************************//
//*** Function definitions ***//
//****************************//
Array U08Array_Create(s08 size)
{
  U08Array self = calloc(1, sizeof(U08ArrayStruct));
  RETURN_VALUE_IF_NULL(self, NULL);

  self->base.vtable = &interface;
  self->base.size   = size;

  self->array = calloc(size, sizeof(u08));
  RETURN_VALUE_IF_NULL(self->array, NULL);
  return (Array)self;
}

static void U08Array_Destroy(Array super)
{
  U08Array self = (U08Array)super;
  free(self->array);
  free(self);
}

static s08 U08Array_Get(Array super, s08 index, void * return_value)
{
  U08Array self = (U08Array)super;
  u08 * data = (u08 *)return_value;

  *data = self->array[index];
  return ARRAY_SUCCESS;
}

static s08 U08Array_Set(Array super, s08 index, void * value)
{
  U08Array self = (U08Array)super;
  u08 * data = (u08 *)value;

  self->array[index] = *data;
  return ARRAY_SUCCESS;
}
