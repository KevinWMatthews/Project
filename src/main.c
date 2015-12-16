#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "DataTypes.h"
#include "Spi.h"
#include "ChipFunctions.h"
#include "Timer0_ATtiny861.h"
#include "BitManip.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define SEND_SUCCESS_LED 6
#define GET_DATA_SUCCESS_LED 7

void turn_led_on(int pin)
{
  SET_BIT_NUMBER(PORTA, pin);
}

void turn_led_off(int pin)
{
  CLEAR_BIT_NUMBER(PORTA, pin);
}


int main(void)
{
  SpiSlaveSelectPin slave;
  uint8_t output_data = 0, input_data = 0;

  //Set up status LEDs
  SET_BIT_NUMBER(DDRA, SEND_SUCCESS_LED);
  SET_BIT_NUMBER(DDRA, GET_DATA_SUCCESS_LED);
  turn_led_off(SEND_SUCCESS_LED);
  turn_led_off(GET_DATA_SUCCESS_LED);

  Spi_SetupHwMaster();
  slave = Spi_SlaveSetup(&DDRA, &PORTA, PINA3);

  output_data = 0;

  ChipFunctions_EnableGlobalInterrupts();

  while (1)
  {
    _delay_ms(1000);
    if (Spi_SendData(slave, output_data) == SPI_SUCCESS)
    {
      turn_led_on(SEND_SUCCESS_LED);
      _delay_ms(5);
      input_data = Spi_GetInputData();
      if (input_data == output_data)
      {
        turn_led_on(GET_DATA_SUCCESS_LED);
      }
    }
    _delay_ms(2000);
    turn_led_off(SEND_SUCCESS_LED);
    turn_led_off(GET_DATA_SUCCESS_LED);
    output_data++;
  }
}

ISR(USI_OVF_vect)
{
  Spi_UsiOverflowInterrupt();
}

ISR(TIMER0_COMPA_vect)
{
  Spi_ClockInterrupt();
}
