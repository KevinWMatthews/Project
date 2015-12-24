#include "SpiCmdArray.h"
#include "SpiCommand.h"
#include <stdlib.h>



//******************************//
//*** Data type declarations ***//
//******************************//
typedef struct SpiCmdArrayStruct * SpiCmdArray;
typedef struct SpiCmdArrayStruct
{
  ArrayStruct base;
  SpiCommand array;
} SpiCmdArrayStruct;



//*****************************//
//*** Function declarations ***//
//*****************************//
static void SpiCmdArray_Destroy(Array super);
static s08 SpiCmdArray_Get(Array super, s08 index, void * return_value);
static s08 SpiCmdArray_Set(Array super, s08 index, void * value);



//***************************************//
//*** File-scope variable definitions ***//
//***************************************//
static ArrayInterfaceStruct interface = {
  .Destroy = SpiCmdArray_Destroy,
  .Get     = SpiCmdArray_Get,
  .Set     = SpiCmdArray_Set
};



//****************************//
//*** Function definitions ***//
//****************************//
Array SpiCmdArray_Create(s08 size)
{
  SpiCmdArray self = calloc(1, sizeof(SpiCmdArrayStruct));
  RETURN_VALUE_IF_NULL(self, NULL);

  self->array = calloc(size, sizeof(SpiCommandStruct));
  RETURN_VALUE_IF_NULL(self->array, NULL);

  self->base.vtable = &interface;
  self->base.size   = size;

  return (Array)self;
}

static void SpiCmdArray_Destroy(Array super)
{
  SpiCmdArray self = (SpiCmdArray)super;
  if (self->array != NULL)
  {
    free(self->array);
  }
  free(self);
}

static s08 SpiCmdArray_Get(Array super, s08 index, void * return_value)
{
  SpiCmdArray self = (SpiCmdArray)super;
  SpiCommand data = (SpiCommand)return_value;

  *data = self->array[index];
  return ARRAY_SUCCESS;
}

static s08 SpiCmdArray_Set(Array super, s08 index, void * value)
{
  SpiCmdArray self = (SpiCmdArray)super;
  SpiCommand data = (SpiCommand)value;

  self->array[index] = *data;
  return ARRAY_SUCCESS;
}
