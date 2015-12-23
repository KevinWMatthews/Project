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
} ArrayInterfaceStruct;

#endif
