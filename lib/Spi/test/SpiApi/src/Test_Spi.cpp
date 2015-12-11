extern "C"
{
  #include "Spi.h"
  #include "SpiHw.h"
  #include "Timer0_ATtiny861.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Spi.h"

TEST_GROUP(Spi)
{
  RegisterPointer ddr;
  RegisterPointer port;
  uint8_t         bit;
  SpiSlaveSelectPin slave;

  void setup()
  {
    slave = NULL; //Until we have destroy()
    ddr   = &DDRA;
    port  = &PORTA;
    bit   = PINA1;
    DDRA  = 0;
    PORTA = 0;
    mock().strictOrder();
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }

  void expectSlaveSetup(RegisterPointer ddr, RegisterPointer port, uint8_t bitNumber)
  {
    mock().expectOneCall("SpiHw_ReleaseSlave")
          .withParameter("port", (uint8_t *)port)
          .withParameter("bit", bit);
    mock().expectOneCall("ChipFunctions_SetPinAsOutput")
          .withParameter("dataDirectionRegister", (uint8_t *)ddr)
          .withParameter("bitNumber", bitNumber);
  }
};



//HwSetup
TEST(Spi, HwSetupMasterOnPortA)
{
  //Set up SpiHw
  mock().expectOneCall("SpiHw_SetWireMode")
        .withParameter("wireMode", USI_THREE_WIRE);
  mock().expectOneCall("SpiHw_SetClockSource")
        .withParameter("clockSource", USI_EXTERNAL_POSITIVE_EDGE_SOFTWARE_STROBE);
  mock().expectOneCall("SpiHw_ConfigureUsiPins")
        .withParameter("masterOrSlave", SPI_MASTER)
        .withParameter("pinPosition", SPI_PORTA_PINS);
  mock().expectOneCall("SpiHw_SetCounterOverflowInterrupts")
        .withParameter("enableInterrupts", TRUE);
  mock().expectOneCall("SpiHw_SetIsTransmittingFlag")
        .withParameter("isTransmitting", FALSE);
  //Set up Timer0
  mock().expectOneCall("Timer0_SetTimerBitWidth")
        .withParameter("timerBitWidth", T0_EIGHT_BIT);
  mock().expectOneCall("Timer0_ClearTimerOnMatch")
        .withParameter("clearOnMatchFlag", TRUE);
  mock().expectOneCall("Timer0_SetPrescaleFactor")
        .withParameter("prescaleFactor", T0_PRESCALE_FACTOR_64);
  mock().expectOneCall("Timer0_SetTimerCompareValue0A")
        .withParameter("timerCompareValue", 125);
  mock().expectOneCall("Timer0_SetTimerCompareInterrupt0A")
        .withParameter("enableInterrupt", FALSE);

  Spi_SetupHwMaster();
  CHECK(Spi_GetIsMaster());
}

TEST(Spi, HwSetupSlave)
{
  //Set up SpiHw
  mock().expectOneCall("SpiHw_SetWireMode")
        .withParameter("wireMode", USI_THREE_WIRE);
  mock().expectOneCall("SpiHw_SetClockSource")
        .withParameter("clockSource", USI_EXTERNAL_POSITIVE_EDGE_SOFTWARE_STROBE);
  mock().expectOneCall("SpiHw_ConfigureUsiPins")
        .withParameter("masterOrSlave", SPI_SLAVE)
        .withParameter("pinPosition", SPI_PORTA_PINS);
  mock().expectOneCall("SpiHw_SetCounterOverflowInterrupts")
        .withParameter("enableInterrupts", TRUE);
  mock().expectOneCall("SpiHw_SetIsTransmittingFlag")
        .withParameter("isTransmitting", FALSE);

  //Timer is not needed
  Spi_SetupHwSlave();
  CHECK(!Spi_GetIsMaster());
}


//Interrupts
TEST(Spi, UsiCounterOverflowInterruptForMaster)
{
  uint8_t mockUsidr = 42;

  Spi_SetIsMaster(TRUE);

  mock().expectOneCall("Timer0_SetTimerCompareInterrupt0A")
        .withParameter("enableInterrupt", FALSE);
  // mock().expectOneCall("SpiHw_ReleaseActiveSlave");
  mock().expectOneCall("SpiHw_ClearCounterOverflowInterruptFlag");
  mock().expectOneCall("SpiHw_SetIsTransmittingFlag")
        .withParameter("isTransmitting", FALSE);
  mock().expectOneCall("SpiHw_SaveInputData")
        .andReturnValue(mockUsidr);

  Spi_UsiOverflowInterrupt();

  LONGS_EQUAL(mockUsidr, Spi_GetInputData());
}

TEST(Spi, UsiCounterOverflowInterruptForSlave)
{
  uint8_t mockUsidr = 42;

  Spi_SetIsMaster(FALSE);

  mock().expectOneCall("SpiHw_ClearCounterOverflowInterruptFlag");
  mock().expectOneCall("SpiHw_SetIsTransmittingFlag")
        .withParameter("isTransmitting", FALSE);
  mock().expectOneCall("SpiHw_SaveInputData")
        .andReturnValue(mockUsidr);

  Spi_UsiOverflowInterrupt();

  LONGS_EQUAL(mockUsidr, Spi_GetInputData());
}

TEST(Spi, ClockInterruptStrobesClock)
{
  mock().expectOneCall("SpiHw_ToggleUsiClock");
  Spi_ClockInterrupt();
}


//Slave select
TEST(Spi, SlaveSetupSelectPinFailsIfDdrIsNull)
{
  slave = Spi_SlaveSetup(NULL, port, bit);
  POINTERS_EQUAL(NULL, slave);
}

TEST(Spi, SlaveSetupSelectPinFailsIfPortIsNull)
{
  slave = Spi_SlaveSetup(ddr, NULL, bit);
  POINTERS_EQUAL(NULL, slave);
}

TEST(Spi, SlaveSetupSelectFailsIfPinBitGreaterTooLarge)
{
  slave = Spi_SlaveSetup(ddr, port, 8);
  POINTERS_EQUAL(NULL, slave);
}

TEST(Spi, SlaveSetupSelectPinSetsDdrAndPortBits)
{
  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);
  CHECK(slave != NULL);
  LONGS_EQUAL(bit, Spi_GetSlaveBit(slave));
  POINTERS_EQUAL(port, Spi_GetSlavePortPointer(slave));
}

//Accessors
TEST(Spi, GetSlaveBitFailsIfSlaveIsNull)
{
  LONGS_EQUAL(0, Spi_GetSlaveBit(NULL));
}

TEST(Spi, GetPortRegisterPointerFailsIfSlaveIsNull)
{
  POINTERS_EQUAL(NULL, Spi_GetSlavePortPointer(NULL));
}

//Release
IGNORE_TEST(Spi, ReleaseSlave)
{
  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_ReleaseSlave")
        .withParameter("port", (uint8_t *)port)
        .withParameter("bit", bit);

  Spi_ReleaseSlave(slave);
}

IGNORE_TEST(Spi, ReleaseFailsWithNullSlave)
{
  Spi_ReleaseSlave(NULL);
}



//Select
IGNORE_TEST(Spi, SelectSlave)
{
  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_SelectSlave")
        .withParameter("port", (uint8_t *)port)
        .withParameter("bit", bit);

  Spi_SelectSlave(slave);
}

TEST(Spi, SelectFailsWithNullSlave)
{
  Spi_SelectSlave(NULL);
}



//SendData
TEST(Spi, SpiSendFailsIfSlaveIsNull)
{
  LONGS_EQUAL(SPI_NULL_POINTER, Spi_SendData(NULL, 66));
}

TEST(Spi, SpiMasterSendFailsIfTransmissionInProgressFlagIsSet)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(TRUE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(TRUE);

  LONGS_EQUAL(SPI_WRITE_IN_PROGRESS, Spi_SendData(slave, outputData));
}

IGNORE_TEST(Spi, SpiSlaveSendFailsIfTransmissionInProgressFlagIsSet)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(FALSE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(TRUE);

  LONGS_EQUAL(SPI_WRITE_IN_PROGRESS, Spi_SendData(slave, outputData));
}

IGNORE_TEST(Spi, SpiMasterSendFailsIfAnotherSlaveIsSelected)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(TRUE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_IsAnySlaveSelected")
        .andReturnValue(TRUE);

  LONGS_EQUAL(SPI_SLAVE_SELECTED, Spi_SendData(slave, outputData));
}

IGNORE_TEST(Spi, SpiSlaveSendFailsIfItIsNotSelected)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(FALSE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_IsSlaveSelected")
        .withParameter("slave", slave)
        .andReturnValue(TRUE);

  LONGS_EQUAL(SPI_SLAVE_SELECTED, Spi_SendData(slave, outputData));
}

TEST(Spi, SpiMasterSendFailsIfUsiCounterIsNotZero)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(TRUE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  // mock().expectOneCall("SpiHw_IsAnySlaveSelected")
  //       .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_GetUsiCounter")
        .andReturnValue(0x01);

  LONGS_EQUAL(SPI_USI_COUNTER_NONZERO, Spi_SendData(slave, outputData));
}

IGNORE_TEST(Spi, SpiSlaveSendFailsIfUsiCounterIsNotZero)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(FALSE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_IsSlaveSelected")
        .withParameter("slave", slave)
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_GetUsiCounter")
        .andReturnValue(0x01);

  LONGS_EQUAL(SPI_USI_COUNTER_NONZERO, Spi_SendData(slave, outputData));
}

TEST(Spi, SpiMasterSendPutsDataInBufferAndEnablesTimer0Interrupts)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(TRUE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  // mock().expectOneCall("SpiHw_IsAnySlaveSelected")
  //       .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_GetUsiCounter")
        .andReturnValue(0x00);
  mock().expectOneCall("SpiHw_PrepareOutputData")
        .withParameter("data", outputData);
  // mock().expectOneCall("SpiHw_SelectSlave")
  //       .withParameter("port", (uint8_t *)port)
  //       .withParameter("bit", bit);
  mock().expectOneCall("Timer0_SetTimerCompareInterrupt0A")
        .withParameter("enableInterrupt", TRUE);

  LONGS_EQUAL(SPI_SUCCESS, Spi_SendData(slave, outputData));
}

IGNORE_TEST(Spi, SpiSlaveSendPutsDataInBuffer)
{
  uint8_t outputData = 0x42;

  Spi_SetIsMaster(FALSE);

  expectSlaveSetup(ddr, port, bit);
  slave = Spi_SlaveSetup(ddr, port, bit);

  mock().expectOneCall("SpiHw_GetIsTransmittingFlag")
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_IsSlaveSelected")
        .withParameter("slave", slave)
        .andReturnValue(FALSE);
  mock().expectOneCall("SpiHw_GetUsiCounter")
        .andReturnValue(0x00);
  mock().expectOneCall("SpiHw_PrepareOutputData")
        .withParameter("data", outputData);

  LONGS_EQUAL(SPI_SUCCESS, Spi_SendData(slave, outputData));
}
