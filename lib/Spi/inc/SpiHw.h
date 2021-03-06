#ifndef SpiHw_H
#define SpiHw_H

#include "DataTypes.h"

enum
{
  SPIHW_NULL_POINTER = -1,
  SPIHW_SUCCESS      =  0
};
int8_t SpiHw_SelectSlave(RegisterPointer port, uint8_t bitNumber);
int8_t SpiHw_ReleaseSlave(RegisterPointer port, uint8_t bitNumber);
void SpiHw_ReleaseActiveSlave(void);  //Interrupt safe

void SpiHw_ClearCounterOverflowInterruptFlag(void);

//Copy data into output register
//Sets an internal transmission started flag
void SpiHw_PrepareOutputData(uint8_t data);

//Copy data from input register
uint8_t SpiHw_SaveInputData(void);

void SpiHw_ToggleUsiClock(void);

void SpiHw_SetIsTransmittingFlag(BOOL isTransmitting);
BOOL SpiHw_GetIsTransmittingFlag(void);

#define BITMASK_USI_COUNTER ((1<<USICNT3) | (1<<USICNT2) | (1<<USICNT1) | (1<<USICNT0))
uint8_t SpiHw_GetUsiCounter(void);
void SpiHw_ClearUsiCounter(void);

BOOL SpiHw_IsAnySlaveSelected(void);
BOOL SpiHw_IsSlaveSelected(RegisterPointer portRegister, uint8_t bitNumber);

void SpiHw_ResetDevice(void);

//*******************************//
//*** Configuration Functions ***//
//*******************************//
//These are inteded for use by the SpiHw module itself.
#define SPIHW_DATA_REGISTER_SIZE (sizeof(uint8_t) * 8)

typedef enum
{
  USI_PARTIAL_DISABLE = 0b00,
  USI_THREE_WIRE      = 0b01,
  USI_TWO_WIRE_1      = 0b10,
  USI_TWO_WIRE_2      = 0b11    //Don't know the difference. Look it up.
} Usi_WireMode;
#define BITMASK_USI_WIRE_MODE (1<<USIWM1) | (1<<USIWM0)
void SpiHw_SetWireMode(Usi_WireMode wireMode);

typedef enum
{
  USI_NONE                                   = 0b000,
  USI_EXTERNAL_POSITIVE_EDGE_SOFTWARE_STROBE = 0b101,   //Spi mode 0
  USI_EXTERNAL_NEGATIVE_EDGE_SOFTWARE_STROBE = 0b111    //Spi mode 1
} Usi_ClockSource;
#define BITMASK_USI_CLOCK_SOURCE (1<<USICS1) | (1<<USICS0) | (1<<USICLK)
void SpiHw_SetClockSource(Usi_ClockSource clockSource);

typedef enum
{
  SPI_PORTB_PINS = 0,
  SPI_PORTA_PINS = 1
} Spi_PinPosition;
typedef enum
{
  SPI_MASTER = 0,
  SPI_SLAVE  = 1
} Spi_DeviceType;
#define USI_MISO_BIT_A 0
#define USI_MOSI_BIT_A 1
#define USI_USCK_BIT_A 2
#define USI_MISO_BIT_B 0
#define USI_MOSI_BIT_B 1
#define USI_USCK_BIT_B 2
void SpiHw_ConfigureUsiPins(Spi_DeviceType masterOrSlave, Spi_PinPosition pinPosition);

//Enable or disable counter overflow interrupts on the USI
void SpiHw_SetCounterOverflowInterrupts(BOOL enableInterrupts);

#endif
