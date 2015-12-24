#ifndef ArrayPrivate_H
#define ArrayPrivate_H

typedef struct ArrayInterfaceStruct * ArrayInterface;

// The base/common elements of an Array struct
typedef struct ArrayStruct
{
  ArrayInterface vtable;
  s08 size;
} ArrayStruct;

//All Arrays subclasses must implement this interface
typedef struct ArrayInterfaceStruct
{
  void (*Destroy)(Array self);
  s08 (*Get)(Array self, s08 index, void * return_value);
  s08 (*Set)(Array self, s08 index, void * value);
} ArrayInterfaceStruct;

#endif
