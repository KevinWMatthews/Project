#ifndef SpiCommand_H
#define SpiCommand_H

typedef struct SpiCommandStruct * SpiCommand;

//This will eventually be private?
typedef struct SpiCommandStruct
{
  u08 command_type; //This may become its own type.
  u08 data;
} SpiCommandStruct;

#endif
