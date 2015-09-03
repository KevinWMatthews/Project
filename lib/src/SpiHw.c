#include "SpiHw.h"
#include <avr/io.h>
#include "BitManip.h"
#include "DataTypes.h"
#include "ChipFunctions.h"

//This flag isn't strictly necessary for single-threaded SPI?
//If we're going multi-threaded, does it need to be more complex?
//Are writes atomic? Should this be a macro?
//This flag is set by when data is placed in the output register and
//is clear when the overflow interrupt is serviced.
static BOOL isTransmittingFlag = FALSE;

//Only one slave can be selected at a time.
//Store this slave so it can easily be released from within an interrupt.
static RegisterPointer activeSlavePort;
static uint8_t         activeSlaveBit;


//************************//
//*** Helper Functions ***//
//************************//
int8_t selectSlave(RegisterPointer port, uint8_t bitNumber)
{
  RETURN_VALUE_IF_NULL(port, SPIHW_NULL_POINTER);
  CLEAR_BIT_NUMBER(*port, bitNumber);
  return SPIHW_SUCCESS;
}

int8_t releaseSlave(RegisterPointer port, uint8_t bitNumber)
{
  RETURN_VALUE_IF_NULL(port, SPIHW_NULL_POINTER);
  SET_BIT_NUMBER(*port, bitNumber);
  return SPIHW_SUCCESS;
}

void clearActiveSlave(void)
{
  activeSlavePort    = NULL;
  activeSlaveBit     = 0xff;
}



//************************//
//*** Public Functions ***//
//************************//
void SpiHw_ResetDevice(void)
{
  isTransmittingFlag = FALSE;
  clearActiveSlave();
}

void SpiHw_ClearCounterOverflowInterruptFlag(void)
{
  SET_BIT_NUMBER(USISR, USIOIF);
}

void SpiHw_SetCounterOverflowInterrupts(BOOL enableInterrupts)
{
  SHIFT_AND_SET_BITMASK_TO(USICR, enableInterrupts, (1<<USIOIE));
}

void SpiHw_SetWireMode(Usi_WireMode wireMode)
{
  SHIFT_AND_SET_BITMASK_TO(USICR, wireMode, BITMASK_USI_WIRE_MODE);
}

void SpiHw_SetClockSource(Usi_ClockSource clockSource)
{
  SHIFT_AND_SET_BITMASK_TO(USICR, clockSource, BITMASK_USI_CLOCK_SOURCE);
}

void masterPinConfiguration(Spi_PinPosition pinPosition)
{
  if (pinPosition == SPI_PORTA_PINS)
  {
    ChipFunctions_SetPinAsInput(&DDRA, USI_MISO_BIT_A);
    ChipFunctions_SetPinAsOutput(&DDRA, USI_MOSI_BIT_A);
    ChipFunctions_SetPinAsOutput(&DDRA, USI_USCK_BIT_A);
    ChipFunctions_EnablePullUpResistor(&PORTA, USI_MISO_BIT_A);
  }
  else if (pinPosition == SPI_PORTB_PINS)
  {
    ChipFunctions_SetPinAsInput(&DDRB, USI_MISO_BIT_B);
    ChipFunctions_SetPinAsOutput(&DDRB, USI_MOSI_BIT_B);
    ChipFunctions_SetPinAsOutput(&DDRB, USI_USCK_BIT_B);
    ChipFunctions_EnablePullUpResistor(&PORTB, USI_MISO_BIT_B);
  }
}

void slavePinConfiguration(Spi_PinPosition pinPosition)
{
  if (pinPosition == SPI_PORTA_PINS)
  {
    ChipFunctions_SetPinAsInput(&DDRA, USI_MISO_BIT_A);
    ChipFunctions_SetPinAsOutput(&DDRA, USI_MOSI_BIT_A);
    ChipFunctions_SetPinAsInput(&DDRA, USI_USCK_BIT_A);
    ChipFunctions_EnablePullUpResistor(&PORTA, USI_MISO_BIT_A);
    ChipFunctions_EnablePullUpResistor(&PORTA, USI_USCK_BIT_A);

  }
  else if (pinPosition == SPI_PORTB_PINS)
  {
    ChipFunctions_SetPinAsInput(&DDRB, USI_MISO_BIT_B);
    ChipFunctions_SetPinAsOutput(&DDRB, USI_MOSI_BIT_B);
    ChipFunctions_SetPinAsInput(&DDRB, USI_USCK_BIT_B);
    ChipFunctions_EnablePullUpResistor(&PORTB, USI_MISO_BIT_B);
    ChipFunctions_EnablePullUpResistor(&PORTB, USI_USCK_BIT_B);
  }
}

void SpiHw_ConfigureUsiPins(Spi_DeviceType masterOrSlave, Spi_PinPosition pinPosition)
{
  SHIFT_AND_SET_BITMASK_TO(USIPP, pinPosition, (1<<USIPOS));

  if (masterOrSlave == SPI_MASTER)
  {
    masterPinConfiguration(pinPosition);
  }
  else if (masterOrSlave == SPI_SLAVE)
  {
    slavePinConfiguration(pinPosition);
  }
}

void SpiHw_PrepareOutputData(uint8_t data)
{
  SpiHw_SetIsTransmittingFlag(TRUE);
  USIDR = data;
}

uint8_t SpiHw_SaveInputData(void)
{
  return USIDR;
}

void SpiHw_ToggleUsiClock(void)
{
  SET_BIT_NUMBER(USICR, USITC);
}

void SpiHw_SetIsTransmittingFlag(BOOL isTransmitting)
{
  isTransmittingFlag = isTransmitting;
}

BOOL SpiHw_GetIsTransmittingFlag(void)
{
  return isTransmittingFlag;
}

uint8_t SpiHw_GetUsiCounter(void)
{
  return USISR & BITMASK_USI_COUNTER;
}

void SpiHw_ClearUsiCounter(void)
{
  SHIFT_AND_SET_BITMASK_TO(USISR, 0x0, BITMASK_USI_COUNTER);
}

int8_t SpiHw_SelectSlave(RegisterPointer port, uint8_t bitNumber)
{
  int8_t returnValue;

  returnValue = selectSlave(port, bitNumber);
  if (returnValue != SPIHW_SUCCESS)
  {
    clearActiveSlave();
    return returnValue;
  }
  activeSlavePort = port;
  activeSlaveBit  = bitNumber;
  return SPIHW_SUCCESS;
}

int8_t SpiHw_ReleaseSlave(RegisterPointer port, uint8_t bitNumber)
{
  int8_t returnValue;

  returnValue = releaseSlave(port, bitNumber);
  if (returnValue != SPIHW_SUCCESS)
  {
    return returnValue;
  }
  clearActiveSlave();
  return SPIHW_SUCCESS;
}

void SpiHw_ReleaseActiveSlave(void)
{
  releaseSlave(activeSlavePort, activeSlaveBit);
  clearActiveSlave();
}

BOOL SpiHw_IsAnySlaveSelected(void)
{
  return activeSlavePort != NULL;
}

BOOL SpiHw_IsSlaveSelected(RegisterPointer portRegister, uint8_t bitNumber)
{
  return (activeSlavePort == portRegister && activeSlaveBit == bitNumber);
}
