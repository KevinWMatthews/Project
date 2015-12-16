extern "C"
{
  #include "SpiHw.h"
  #include <avr/io.h>
  #include "BitManip.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_SpiHw.h"

TEST_GROUP(SpiHw)
{
  uint8_t expectedBitmask;

  void setup()
  {
    expectedBitmask = 0;
    USICR = 0;
    USISR = 0;
    USIDR = 0;
    USIPP = 0;
    DDRA  = 0;
    PORTA = 0;
    PORTB = 0;
    SpiHw_ResetDevice();
//    SpiHw_SetIsTransmittingFlag(FALSE);
  }

  void teardown()
  {
  }

  void checkNoSlaveIsSelected(void)
  {
    LONGS_EQUAL(TRUE, SpiHw_IsSlaveSelected(NULL, 0xff));
    LONGS_EQUAL(FALSE, SpiHw_IsAnySlaveSelected());
  }

  void checkSlaveIsSelected(RegisterPointer port, uint8_t bitNumber)
  {
    LONGS_EQUAL(TRUE, SpiHw_IsSlaveSelected(port, bitNumber));
    LONGS_EQUAL(TRUE, SpiHw_IsAnySlaveSelected());
  }
};

TEST(SpiHw, RegistersClearedAfterSetup)
{
  BYTES_EQUAL(0, USICR);
  BYTES_EQUAL(0, USISR);
  BYTES_EQUAL(0, USIDR);
  BYTES_EQUAL(0, USIPP);
  BYTES_EQUAL(0, DDRA);
  BYTES_EQUAL(0, PORTA);
  BYTES_EQUAL(0, PORTB);
  CHECK(!SpiHw_IsAnySlaveSelected());
  CHECK(!SpiHw_GetIsTransmittingFlag());
}

TEST(SpiHw, ClearCounterOverflowInterruptFlag)
{
  SET_BIT_NUMBER(expectedBitmask, USIOIF);

  SpiHw_ClearCounterOverflowInterruptFlag();
  BYTES_EQUAL(expectedBitmask, USISR);
}

TEST(SpiHw, EnableCounterOverflowInterrupts)
{
  SET_BIT_NUMBER(expectedBitmask, USIOIE);

  SpiHw_SetCounterOverflowInterrupts(TRUE);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, DisableCounterOverflowInterrupts)
{
  USICR = 0xff;
  expectedBitmask = 0xff;
  CLEAR_BIT_NUMBER(expectedBitmask, USIOIE);

  SpiHw_SetCounterOverflowInterrupts(FALSE);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, SetAllWiringModeBits)
{
  SET_BIT_NUMBER(expectedBitmask, USIWM1);
  SET_BIT_NUMBER(expectedBitmask, USIWM0);

  SpiHw_SetWireMode(USI_TWO_WIRE_2);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, ClearAllWiringModeBits)
{
  USICR = 0xff;
  expectedBitmask = 0xff;
  CLEAR_BIT_NUMBER(expectedBitmask, USIWM1);
  CLEAR_BIT_NUMBER(expectedBitmask, USIWM0);

  SpiHw_SetWireMode(USI_PARTIAL_DISABLE);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, SetAllClockSourceBits)
{
  SET_BIT_NUMBER(expectedBitmask, USICS1);
  SET_BIT_NUMBER(expectedBitmask, USICS0);
  SET_BIT_NUMBER(expectedBitmask, USICLK);

  SpiHw_SetClockSource(USI_EXTERNAL_NEGATIVE_EDGE_SOFTWARE_STROBE);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, ClearAllClockSourceBits)
{
  USICR = 0xff;
  expectedBitmask = 0xff;
  CLEAR_BIT_NUMBER(expectedBitmask, USICS1);
  CLEAR_BIT_NUMBER(expectedBitmask, USICS0);
  CLEAR_BIT_NUMBER(expectedBitmask, USICLK);

  SpiHw_SetClockSource(USI_NONE);
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, PrepareOutputDataSetsIsTransmittingFlag)
{
  uint8_t sampleData = 0xa5;
  SpiHw_PrepareOutputData(sampleData);
  BYTES_EQUAL(sampleData, USIDR);
  CHECK(SpiHw_GetIsTransmittingFlag());
}

TEST(SpiHw, SetMasterPinPositionToPortA)
{
  uint8_t expectedDDR   = 0x00;
  uint8_t expectedUSIPP = 0x00;
  uint8_t expectedPORT  = 0x00;
  USIPP = 0x00;
  DDRA  = 0x01;

  SET_BIT_NUMBER(expectedUSIPP, USIPOS);
  CLEAR_BIT_NUMBER(expectedDDR, USI_MISO_BIT_A);  //Input:   MISO
  SET_BIT_NUMBER(expectedDDR, USI_MOSI_BIT_A);    //Output:  MOSI
  SET_BIT_NUMBER(expectedDDR, USI_USCK_BIT_A);    //Output:  SCK
  SET_BIT_NUMBER(expectedPORT, USI_MISO_BIT_A);   //Pull-up: MISO

  SpiHw_ConfigureUsiPins(SPI_MASTER, SPI_PORTA_PINS);
  BYTES_EQUAL(expectedUSIPP, USIPP);
  BYTES_EQUAL(expectedDDR, DDRA);
  BYTES_EQUAL(expectedPORT, PORTA);
}

TEST(SpiHw, SetMasterPinPositionToPortB)
{
  uint8_t expectedDDRB  = 0x00;
  uint8_t expectedUSIPP = 0xff;
  uint8_t expectedPORT  = 0x00;
  USIPP = 0xff;
  DDRB  = 0x01;

  CLEAR_BIT_NUMBER(expectedUSIPP, USIPOS);
  CLEAR_BIT_NUMBER(expectedDDRB, USI_MISO_BIT_B); //Input:   MISO
  SET_BIT_NUMBER(expectedDDRB, USI_MOSI_BIT_B);   //Output:  MOSI
  SET_BIT_NUMBER(expectedDDRB, USI_USCK_BIT_B);   //Output:  USCK
  SET_BIT_NUMBER(expectedPORT, USI_MISO_BIT_B);   //Pull-up: MISO

  SpiHw_ConfigureUsiPins(SPI_MASTER, SPI_PORTB_PINS);
  BYTES_EQUAL(expectedUSIPP, USIPP);
  BYTES_EQUAL(expectedDDRB, DDRB);
  BYTES_EQUAL(expectedPORT, PORTB);
}

TEST(SpiHw, SetSlavePinPositionToPortA)
{
  uint8_t expectedDDR   = 0x00;
  uint8_t expectedUSIPP = 0xff;
  uint8_t expectedPORT  = 0x00;
  USIPP = 0xff;
  DDRA  = 0x06;

  SET_BIT_NUMBER(expectedUSIPP, USIPOS);
  CLEAR_BIT_NUMBER(expectedDDR, USI_MISO_BIT_A);  //Input:  MISO
  SET_BIT_NUMBER(expectedDDR, USI_MOSI_BIT_A);    //Output: MOSI
  CLEAR_BIT_NUMBER(expectedDDR, USI_USCK_BIT_A);  //Input:  USCK
  SET_BIT_NUMBER(expectedPORT, USI_MISO_BIT_A);   //Pull-up: MISO
  SET_BIT_NUMBER(expectedPORT, USI_USCK_BIT_A);   //Pull-up: USCK

  SpiHw_ConfigureUsiPins(SPI_SLAVE, SPI_PORTA_PINS);
  BYTES_EQUAL(expectedUSIPP, USIPP);
  BYTES_EQUAL(expectedDDR, DDRA);
  BYTES_EQUAL(expectedPORT, PORTA);
}

TEST(SpiHw, SetSlavePinPositionToPortB)
{
  uint8_t expectedDDR   = 0x00;
  uint8_t expectedUSIPP = 0xff;
  uint8_t expectedPORT  = 0x00;
  USIPP = 0xff;
  DDRB  = 0x06;

  CLEAR_BIT_NUMBER(expectedUSIPP, USIPOS);
  CLEAR_BIT_NUMBER(expectedDDR, USI_MISO_BIT_B);  //Input:  MISO
  SET_BIT_NUMBER(expectedDDR, USI_MOSI_BIT_B);    //Output: MOSI
  CLEAR_BIT_NUMBER(expectedDDR, USI_USCK_BIT_B);  //Input:  USCK
  SET_BIT_NUMBER(expectedPORT, USI_MISO_BIT_B);   //Pull-up: MISO
  SET_BIT_NUMBER(expectedPORT, USI_USCK_BIT_B);   //Pull-up: USCK

  SpiHw_ConfigureUsiPins(SPI_SLAVE, SPI_PORTB_PINS);
  BYTES_EQUAL(expectedUSIPP, USIPP);
  BYTES_EQUAL(expectedDDR, DDRB);
  BYTES_EQUAL(expectedPORT, PORTB);
}

TEST(SpiHw, SaveInputData)
{
  USIDR = 0x53;
  BYTES_EQUAL(USIDR, SpiHw_SaveInputData());
}

TEST(SpiHw, ToggleUsiClock)
{
  SET_BIT_NUMBER(expectedBitmask, USITC);
  SpiHw_ToggleUsiClock();
  BYTES_EQUAL(expectedBitmask, USICR);
}

TEST(SpiHw, SetisTransmittingFlag)
{
  SpiHw_SetIsTransmittingFlag(TRUE);
  CHECK(SpiHw_GetIsTransmittingFlag());
  SpiHw_SetIsTransmittingFlag(FALSE);
  CHECK(!SpiHw_GetIsTransmittingFlag());
}

TEST(SpiHw, GetUsiCounter)
{
  LONGS_EQUAL(0, SpiHw_GetUsiCounter());

  //Set all bits that arenot in the counter to ensure that they have no effect
  SET_BITMASK_TO(USISR, 0xff, ~(BITMASK_USI_COUNTER));
  //Set bits within the counter
  SET_BITMASK_TO(USISR, 0x0a, BITMASK_USI_COUNTER);
  BYTES_EQUAL(0x0a, SpiHw_GetUsiCounter());
}

TEST(SpiHw, ResetUsiCounter)
{
  //Set all bits that are not in the counter to ensure that they are unaffected
  SET_BITMASK_TO(USISR, 0xff, ~(BITMASK_USI_COUNTER));
  SET_BITMASK_TO(USISR, 0x0a, BITMASK_USI_COUNTER);
  SpiHw_ClearUsiCounter();
  BYTES_EQUAL(0x00, SpiHw_GetUsiCounter());
  BYTES_EQUAL( USISR & ~(BITMASK_USI_COUNTER), 0xf0);
}

TEST(SpiHw, SelectSlavePullsPinLowAndStoresActiveSlave)
{
  RegisterPointer port = &PORTA;
  uint8_t bitNumber    = PORTA7;
  *port = 0xff;

  LONGS_EQUAL(SPIHW_SUCCESS, SpiHw_SelectSlave(port, bitNumber));
  checkSlaveIsSelected(port, bitNumber);
  BYTES_EQUAL(~(1<<bitNumber), *port);
}

TEST(SpiHw, SelectSlaveFailsAndClearsActiveSlaveIfRegisterIsNull)
{
  RegisterPointer port = &PORTA;
  uint8_t bitNumber    = PORTA0;
  *port = 0xff;

  LONGS_EQUAL(SPIHW_NULL_POINTER, SpiHw_SelectSlave(NULL, bitNumber));
  checkNoSlaveIsSelected();
  BYTES_EQUAL(0xff, *port);
}

TEST(SpiHw, ReleaseSlavePullsPinHighAndClearsActiveSlave)
{
  RegisterPointer port = &PORTA;
  uint8_t bitNumber    = PORTA7;
  *port = 0x00;
  SpiHw_SelectSlave(port, bitNumber);

  LONGS_EQUAL(SPIHW_SUCCESS, SpiHw_ReleaseSlave(port, bitNumber));
  checkNoSlaveIsSelected();
  BYTES_EQUAL(1<<bitNumber, *port);
}

TEST(SpiHw, ReleaseSlaveFailsIfRegisterIsNull)
{
  RegisterPointer port = &PORTA;
  uint8_t bitNumber    = PORTA3;
  *port = 0x00;
  SpiHw_SelectSlave(port, bitNumber);

  SpiHw_ReleaseSlave(NULL, bitNumber);

  checkSlaveIsSelected(port, bitNumber);
  BYTES_EQUAL(0x00, *port);
}

TEST(SpiHw, ReleaseActiveSlave)
{
  RegisterPointer port = &PORTA;
  uint8_t bitNumber    = PORTA6;
  *port = 0x00;
  SpiHw_SelectSlave(port, bitNumber);

  SpiHw_ReleaseActiveSlave();

  checkNoSlaveIsSelected();
  BYTES_EQUAL(1<<bitNumber, *port);
}

TEST(SpiHw, ReleaseActiveSlaveWhenNoSlaveIsActive)
{
  RegisterPointer port = &PORTA;
  *port = 0x00;

  SpiHw_ReleaseActiveSlave();

  checkNoSlaveIsSelected();
  BYTES_EQUAL(0x00, *port);
}

TEST(SpiHw, NoSlaveSelectedByDefault)
{
  checkNoSlaveIsSelected();
}
