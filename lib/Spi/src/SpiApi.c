#include "SpiApi.h"
#include "Spi.h"

typedef struct
{
  RegisterPointer slave;
  BOOL sendData;
  BOOL getData;
  int8_t dataToSend;
} SpiCommandStruct;

typedef SpiCommandStruct * SpiCommand;

SpiCommandStruct commandQueue[10];

int8_t SpiApi_Send(RegisterPointer slave, int8_t data)
{
  SpiCommand new_command = &commandQueue[0];
  new_command->slave      = slave;
  new_command->sendData   = TRUE;
  new_command->getData    = FALSE;
  new_command->dataToSend = data;
  return SPIAPI_CMD_IN_QUEUE;
}

void SpiApi_Service(void)
{
  SpiCommand current_command = &commandQueue[0];

  if (current_command->sendData == TRUE)
  {
    Spi_Transmit(current_command->slave, current_command->dataToSend);
    current_command->slave      = NULL;
    current_command->sendData   = FALSE;
    current_command->getData    = FALSE;
    current_command->dataToSend = 0;
  }
}
