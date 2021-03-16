#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
  cli();
  SREG |= (1 << 7);
  TIMSK1 |= (1 << OCIE1B);/*máscara de interrupção - comparação ou overflow? comparação*/
  /*Os dois bits acima foram setados para habilitar a interrupção por comparação*/
  TCCR1B |= (1 << CS12) | (1 << CS10)| (1 << WGM12);/*prescale de  1024*/
  OCR1B = 46922;
  TCNT1 = 0;/*Timer/Counter*/
  TIFR1 |= (1 << OCF1B); /*bit  1 setado para a interrupção ser executada*/
  DDRB |= (1 << DDB5);
  PORTB &= ~(1 << PB5);
  sei();
  while(1);/*o ponto e vírgula no while é como se não tivesse nada dentro dele*/
  return 0;/*pra caso não seja mais executado o while ele vai retornar um valor*/
}

ISR(TIMER1_COMPB_vect)
{
  PORTB ^= (1 << PB5);
  TCNT1 = 0;
}

/*16MHz --- prescale 1024 = 15625 Hz
T = 1/15625 = 64us
65535 x 64 us = 4,19s 

65535 ----- 4,19s
x --------- 3s
  x =  46922
*/
