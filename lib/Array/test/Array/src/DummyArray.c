#include "DummyArray.h"
#include <stdlib.h>



//*****************************//
//*** Function declarations ***//
//*****************************//
static void DummyDestroy(Array self);
static s08 DummyGet(Array self, s08 index, void * return_value);
static s08 DummySet(Array self, s08 index, void * value);



//***************************************//
//*** File-scope variable definitions ***//
//***************************************//
static ArrayInterfaceStruct interface = {
  //Comment out individual function assignments to verify assertions
  .Destroy = DummyDestroy,
  .Get = DummyGet,
  .Set = DummySet
};



//****************************//
//*** Function definitions ***//
//****************************//
Array DummyArray_Create(s08 size)
{
  Array self = calloc(1, sizeof(ArrayStruct));
  self->vtable = &interface;
  self->size   = size;
  return self;
}

static void DummyDestroy(Array self)
{
  free(self);
}

static s08 DummyGet(Array self, s08 index, void * return_value)
{
  return ERRONEOUS_FUNCTION_CALL;
}

static s08 DummySet(Array self, s08 index, void * value)
{
  return ERRONEOUS_FUNCTION_CALL;
}
