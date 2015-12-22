#ifndef Array_H
#define Array_H

#include "DataTypes.h"

typedef struct ArrayStruct * Array;

typedef enum Array_DataType
{
  ARRAY_INT8_T
} Array_DataType;
Array Array_Create(Array_DataType data_type, int8_t size);
void Array_Destroy(Array self);
BOOL Array_VerifyBufferIntegrity(Array self);


enum
{
  ARRAY_ELEMENT_OUT_OF_BOUNDS = -1,
  ARRAY_SUCCESS               = 0
};
int8_t Array_Get(Array self, int8_t index, void * return_value);
int8_t Array_Set(Array self, int8_t index, void * value);

#endif
