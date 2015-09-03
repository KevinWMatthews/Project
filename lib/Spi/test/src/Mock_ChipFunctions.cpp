extern "C"
{
  #include "ChipFunctions.h"
}

#include "CppUTestExt/MockSupport.h"

void ChipFunctions_SetPinAsOutput(RegisterPointer dataDirectionRegister, uint8_t bitNumber)
{
  mock().actualCall("ChipFunctions_SetPinAsOutput")
        .withParameter("dataDirectionRegister", (uint8_t *)dataDirectionRegister)
        .withParameter("bitNumber", bitNumber);
}

void ChipFunctions_SetPinAsInput(RegisterPointer dataDirectionRegister, uint8_t bitNumber)
{}

void ChipFunctions_EnablePullUpResistor(RegisterPointer portRegister, uint8_t bitNumber)
{}

void ChipFunctions_DisablePullUpResistor(RegisterPointer portRegister, uint8_t bitNumber)
{}
