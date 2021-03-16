#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
  cli();//desabilitar TODAS as interrupções
  SREG |= (1 << I); //bitI no registrador sreg setado para habilitar o pino de interrupção externo
  EIMSK |= (1 << INT1);//bit INT1 setado no registrador EIMSK para habilitar o pino de interrupção externo
  EICRA |= (1 << ISC11);//ativei o meu ISC11 para ele ser ativado em borda de descida

  DDRD &= ~(1 << DDD3);// pino recebe nível lógico zero para acionar a interrupção; pino de entrada.
  PORTD |= (1 << PORTD3);//pull-up
  DDRB |= (1 << DDB5);//acender o LED; pino de saída
  sei();//habilitar TODAS as interrupções
 
  while(1)
  {
     PORTB ^= (1 << PORTB5);
    _delay_ms(1500);
  }
}



ISR(INT1_vect)
{
  PORTB ^= (1 << PORTB5);
}
