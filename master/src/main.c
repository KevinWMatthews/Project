#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "Spi.h"
#include "ChipFunctions.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "SpiHw.h"
#include "Timer0_ATtiny861.h"

#include <util/delay.h>

int main(void)
{
  SpiSlaveSelectPin slave;
  uint8_t outputData;

  _delay_ms(2000);

  Spi_HwSetupMaster();
  slave = Spi_SlaveSetup(&DDRA, &PORTA, PORTA3);

  //Enable status LEDS
  DDRA |= (1<<DDA4) | (1<<DDA5);

  //Loop will send Spi Data when this input is grounded
  DDRA &= ~(1<<DDA7);
  PORTA |= (1<<PORTA7); //Enable internal pull-up resistor
  ChipFunctions_EnableGlobalInterrupts();

  //Transmit a single number
  outputData = 0xaa;
  if (Spi_SendData(slave, outputData) != SPI_SUCCESS)
  {
    PORTA |= (1<<PORTA5);
  }
  else
  {
    PORTA |= (1<<PORTA4);
  }

  //Transmit an increasing value every 10 seconds
  outputData = 0x00;
  while (1)
  {
    // PORTA &= ~((1<<PORTA4) | (1<<PORTA5));
    // _delay_ms(1000);
    // if (!(PINA & (1<<PINA7)))
    // {
    //   if (Spi_SendData(slave, outputData) != SPI_SUCCESS)
    //   {
    //     PORTA |= (1<<PORTA5);
    //   }
    //   else
    //   {
    //     PORTA |= (1<<PORTA4);
    //   }
    //   outputData++;
    // }
    // _delay_ms(9000);
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
