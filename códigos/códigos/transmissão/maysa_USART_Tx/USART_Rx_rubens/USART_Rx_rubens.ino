#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>

volatile char buf;

int main()
{
  cli();
  SREG |= (1 << 7);
  
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  DDRB |= (1 << DDB5);
  
  sei();
  while(1);
  return 0;  
}


ISR(USART_RX_vect)
{
  while (!(UCSR0A & (1<<RXC0)));
  buf = UDR0;

  if(buf == 't')
  {
    PORTB |= (1 << PORTB5);
  }
  else
  {
    PORTB &= ~(1 << PORTB5);
  }
  while (!(UCSR0A & (1<<UDRIE0)));
  UDR0 = buf;
}
