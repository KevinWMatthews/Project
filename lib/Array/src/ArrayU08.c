#include "ArrayU08.h"
#include "Array.h"
#include <stdlib.h>



//Define data structures
typedef struct ArrayU08Struct
{
  ArrayStruct base;
  u08 *array;
} ArrayU08Struct;



//Prototypes
static void ArrayU08_Destroy(Array super);
static s08 ArrayU08_Get(Array super, s08 index, void * return_value);
static s08 ArrayU08_Set(Array super, s08 index, void * value);



//Initialize file-scope variables
static ArrayInterfaceStruct interface = {
  .Destroy = ArrayU08_Destroy,
  .Get = ArrayU08_Get,
  .Set = ArrayU08_Set
};



//Functions
Array ArrayU08_Create(s08 size)
{
  ArrayU08 self = calloc(1, sizeof(ArrayU08Struct));
  RETURN_VALUE_IF_NULL(self, NULL);

  self->base.vtable = &interface;
  self->base.size   = size;

  self->array = calloc(size, sizeof(u08));
  RETURN_VALUE_IF_NULL(self->array, NULL);
  return (Array)self;
}

static void ArrayU08_Destroy(Array super)
{
  ArrayU08 self = (ArrayU08)super;

  //null checks

  free(self->array);
  free(self);
}

static s08 ArrayU08_Get(Array super, s08 index, void * return_value)
{
  ArrayU08 self = (ArrayU08)super;
  u08 * data = (u08 *)return_value;
  //null checks

  *data = self->array[index];
  return ARRAY_SUCCESS;
}

static s08 ArrayU08_Set(Array super, s08 index, void * value)
{
  ArrayU08 self = (ArrayU08)super;
  u08 * data = (u08 *)value;
  self->array[index] = *data;
  return ARRAY_SUCCESS;
}
