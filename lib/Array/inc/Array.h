#ifndef Array_H
#define Array_H

#include "DataTypes.h"

typedef struct ArrayStruct * Array;

void Array_Destroy(Array self);

// typedef enum Array_DataType
// {
//   ARRAY_INT8_T
// } Array_DataType;
// Array Array_Create(Array_DataType data_type, int8_t size);
// BOOL Array_VerifyBufferIntegrity(Array self);


enum
{
  ARRAY_INDEX_OUT_OF_BOUNDS = -1,
  ARRAY_SUCCESS             = 0
};
s08 Array_Get(Array self, s08 index, void * return_value);
s08 Array_Set(Array self, s08 index, void * value);

#include "ArrayPrivate.h"

#endif
