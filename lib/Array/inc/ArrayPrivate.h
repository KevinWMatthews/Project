#ifndef ArrayPrivate_H
#define ArrayPrivate_H

typedef struct ArrayInterfaceStruct * ArrayInterface;

typedef struct ArrayStruct
{
  ArrayInterface vtable;
} ArrayStruct;

typedef struct ArrayInterfaceStruct
{
  void (*Destroy)(Array self);
  int8_t (*Get)(Array self, int8_t index, void * return_value);
  int8_t (*Set)(Array self, int8_t index, void * value);
} ArrayInterfaceStruct;

#endif
