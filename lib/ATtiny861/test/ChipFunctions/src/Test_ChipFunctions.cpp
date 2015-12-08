extern "C"
{
  #include "ChipFunctions.h"
  #include <avr/interrupt.h>
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_ChipFunctions.h"

TEST_GROUP(ChipFunctions)
{
  void setup()
  {
    SREG  = 0;
    CLKPR = 0b0011;
    DDRA  = 0;
    PORTA = 0;
  }

  void teardown()
  {
  }
};

TEST(ChipFunctions, AllRegistersSetToFactoryDefaultsAfterSetup)
{
  BYTES_EQUAL(0, SREG);
  BYTES_EQUAL(0b0011, CLKPR);
  BYTES_EQUAL(0, DDRA);
  BYTES_EQUAL(0, PORTA);
}

// TEST(ChipFunctions, HardwareSetup)
// {
//   uint8_t expectedCLKPR = 0;
//   SET_BITMASK_TO(expectedCLKPR, CF_CPU_PRESCALE_FACTOR_1, BITMASK_CF_PRESCALE_FACTOR);
//   ChipFunctions_HwSetup();
//   BYTES_EQUAL(expectedCLKPR, CLKPR);
// }

TEST(ChipFunctions, SetGlobalInterruptBit)
{
  ChipFunctions_EnableGlobalInterrupts();
  BYTES_EQUAL(0x80, SREG);
}

TEST(ChipFunctions, ClearGlobalInterruptBit)
{
  SREG = 0xff;
  ChipFunctions_DisableGlobalInterrupts();
  BYTES_EQUAL(0xff & ~0x80, SREG);
}

// TEST(ChipFunctions, SetAllCpuPrescaleFactorBits)
// {
//   //0x0f isn't a valid prescaler value, so test all bits in two steps
//   ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_256);
//   BYTES_EQUAL(0x08, CLKPR);
//   ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_128);
//   BYTES_EQUAL(0x07, CLKPR);
// }

// TEST(ChipFunctions, ClearAllCpuPrescaleFactorBits)
// {
//   CLKPR = 0xff;
//   ChipFunctions_SetCpuPrescaler(CF_CPU_PRESCALE_FACTOR_1);
//   BYTES_EQUAL(0xf0, CLKPR);
// }

TEST(ChipFunctions, SetPinAsOutput)
{
  uint8_t expectedDdr = 0x00;
  SET_BIT_NUMBER(expectedDdr, DDA7);
  ChipFunctions_SetPinAsOutput(&DDRA, DDA7);
  BYTES_EQUAL(expectedDdr, DDRA);
}

TEST(ChipFunctions, SetPinAsOutputCanHandleNullPointer)
{
  ChipFunctions_SetPinAsOutput(NULL, DDA7);
}

//How can I get this to fail?
IGNORE_TEST(ChipFunctions, SetPinAsOutputCanHandleOutOfBoundsBit)
{
  DDRA = 0x00;
  ChipFunctions_SetPinAsOutput(&DDRA, 8);
  //Test for memory leak!
}

TEST(ChipFunctions, SetPinAsInput)
{
  uint8_t expectedDdr = 0xff;
  DDRA = 0xff;
  CLEAR_BIT_NUMBER(expectedDdr, DDA0);
  ChipFunctions_SetPinAsInput(&DDRA, DDA0);
  BYTES_EQUAL(expectedDdr, DDRA);
}

TEST(ChipFunctions, SetPinAsInputCanHandleNullPointer)
{
  ChipFunctions_SetPinAsInput(NULL, DDA0);
}

//How can I get this to fail?
IGNORE_TEST(ChipFunctions, SetPinAsInputCanHandleOutOfBoundsBit)
{
  DDRA = 0xff;
  ChipFunctions_SetPinAsInput(&DDRA, 8);
  //Test for memory leak!
}

TEST(ChipFunctions, EnablePullUpResistor)
{
  uint8_t expectedPort = 0x00;
  SET_BIT_NUMBER(expectedPort, PORTA3);
  ChipFunctions_EnablePullUpResistor(&PORTA, PORTA3);
  BYTES_EQUAL(expectedPort, PORTA);
}

TEST(ChipFunctions, EnablePullUpResistorCanHandleNullPointer)
{
  ChipFunctions_EnablePullUpResistor(NULL, PORTA4);
}

//How can I get this to fail?
IGNORE_TEST(ChipFunctions, EnablePullUpResistorCanHandleOutOfBoundsBit)
{
  PORTA = 0x00;
  ChipFunctions_EnablePullUpResistor(&PORTA, 8);
  //Test for memory leak!
}

TEST(ChipFunctions, DisablePullUpResistor)
{
  uint8_t expectedPort = 0xff;
  PORTA = 0xff;
  CLEAR_BIT_NUMBER(expectedPort, PORTA3);
  ChipFunctions_DisablePullUpResistor(&PORTA, PORTA3);
  BYTES_EQUAL(expectedPort, PORTA);
}

TEST(ChipFunctions, DisablePullUpResistorCanHandleNullPointer)
{
  ChipFunctions_DisablePullUpResistor(NULL, PORTA4);
}

//How can I get this to fail?
IGNORE_TEST(ChipFunctions, DisablePullUpResistorCanHandleOutOfBoundsBit)
{
  PORTA = 0xff;
  ChipFunctions_DisablePullUpResistor(&PORTA, 8);
  //Test for memory leak!
}
