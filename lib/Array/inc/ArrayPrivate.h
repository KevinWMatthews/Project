#ifndef ArrayPrivate_H
#define ArrayPrivate_H

typedef struct ArrayInterfaceStruct * ArrayInterface;

typedef struct ArrayStruct
{
  ArrayInterface vtable;
  s08 size;
} ArrayStruct;

typedef struct ArrayInterfaceStruct
{
  void (*Destroy)(Array self);
  s08 (*Get)(Array self, s08 index, void * return_value);
  s08 (*Set)(Array self, s08 index, void * value);
} ArrayInterfaceStruct;

#endif
