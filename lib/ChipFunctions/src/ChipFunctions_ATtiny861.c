#include "ChipFunctions.h"
#include "BitManip.h"
#include <avr/interrupt.h>
// #include <avr/io.h>

void ChipFunctions_EnableGlobalInterrupts(void)
{
  //This call is specific to AVR chips
  //Can also manually set bit 7 (I) of SREG
  sei();
}

void ChipFunctions_DisableGlobalInterrupts(void)
{
  //This call is specific to AVR chips
  //Can also manually clear bit 7 (I) of SREG
  cli();
}

void ChipFunctions_SetPinAsOutput(RegisterPointer dataDirectionRegister, uint8_t bitNumber)
{
  RETURN_IF_NULL(dataDirectionRegister);
  if (bitNumber >= sizeof(bitNumber) * 8)
  {
    return;
  }
  SET_BIT_NUMBER(*dataDirectionRegister, bitNumber);
}

void ChipFunctions_SetPinAsInput(RegisterPointer dataDirectionRegister, uint8_t bitNumber)
{
  RETURN_IF_NULL(dataDirectionRegister);
  if (bitNumber >= sizeof(bitNumber) * 8)
  {
    return;
  }
  CLEAR_BIT_NUMBER(*dataDirectionRegister, bitNumber);
}

void ChipFunctions_EnablePullUpResistor(RegisterPointer portRegister, uint8_t bitNumber)
{
  RETURN_IF_NULL(portRegister);
  if (bitNumber >= sizeof(bitNumber) * 8)
  {
    return;
  }
  SET_BIT_NUMBER(*portRegister, bitNumber);
}

void ChipFunctions_DisablePullUpResistor(RegisterPointer portRegister, uint8_t bitNumber)
{
  RETURN_IF_NULL(portRegister);
  if (bitNumber >= sizeof(bitNumber) * 8)
  {
    return;
  }
  CLEAR_BIT_NUMBER(*portRegister, bitNumber);
}
