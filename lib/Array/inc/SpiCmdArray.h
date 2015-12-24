#ifndef SpiCmdArray_H
#define SpiCmdArray_H

#include "Array.h"

//SpiCmdArray may produce undefined behavior if the SpiCommand struct contains a pointer
//because Get and set use shallow struct copies.
//If SpiCommand is revised to contain a pointer, verify the behavior of SpiCmdArray Get() and Set().

Array SpiCmdArray_Create(s08 size);

//See Array.h for the Array interface.

#endif
