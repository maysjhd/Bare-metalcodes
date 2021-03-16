#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*
 * Timer de 16 bits: 0 a 2^16(65536)
 *    -Overflow
 *    -Comparador
 *    -PMW
 *    TCCR1B(CS12, CS11 e CS10)->Prescale
 */
int main(){
  cli();
  TCCR1B |= (1 << CS11);//Pescale de 8
  TCNT1 = 0;
  SREG |= (1 << 7);
  TIMSK1 |= (1 << TOIE1);//Habilitando interrupção por overflow
  DDRB |= (1 << DDB5);
  PORTB &= ~(1 << PB5);
  sei();
  
  while(1);
  return 0;
}
ISR(TIMER1_OVF_vect){
  PORTB ^= (1 << PB5);
  TCNT1 =0;}
