#include "FakeSpiApi.h"

int8_t FakeSpiApi_Send_Fails(RegisterPointer slave, int8_t data)
{
  return FALSE;
}
