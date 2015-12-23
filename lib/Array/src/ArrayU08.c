#include "ArrayU08.h"
#include "Array.h"
#include <stdlib.h>



//Structures
typedef struct ArrayU08Struct
{
  ArrayStruct base;
  u08 *array;
} ArrayU08Struct;



//Prototypes
static void ArrayU08_Destroy(Array super);

ArrayInterfaceStruct interface = {
  .Destroy = ArrayU08_Destroy
};



//Functions
Array ArrayU08_Create(int8_t size)
{
  ArrayU08 self = calloc(1, sizeof(ArrayU08Struct));
  RETURN_VALUE_IF_NULL(self, NULL);
  self->base.vtable = &interface;
  self->array = calloc(size, sizeof(u08));
  RETURN_VALUE_IF_NULL(self, NULL);
  return (Array)self;
}

static void ArrayU08_Destroy(Array super)
{
  ArrayU08 self = (ArrayU08)super;

  //null checks

  free(self->array);
  free(self);
}
