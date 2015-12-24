#ifndef SpiCmdArray_H
#define SpiCmdArray_H

#include "Array.h"

//Only valid for shallow struct copies. If SpiCommand contains a pointer,
//we need to rewrite Get and Set.

Array SpiCmdArray_Create(s08 size);

#endif
