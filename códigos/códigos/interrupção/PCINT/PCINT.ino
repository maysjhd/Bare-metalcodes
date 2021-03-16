#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
  cli();//desabilita todas as interrupções
  SREG |= (1 << 7); //bit I setado no registrador SREG (ele é o bit de ativação de interrupção global -> deve ser definido para as interrupções serem ativadas)
  PCICR |= (1 << PCIE0);//PCIE0 - bit 0 no registrador PCICR em nível 1 para habilitar a interrupção de mudança de pino  
  PCMSK0 |= (1 << PCINT2);//PB2 = PCINT2 definido para habilitar a interrupção de mudança de pino de E/S

  DDRB &= ~(1 << DDB2);//pino 10 (PB2) setado como entrada
  PORTB |= (1 << PORTB2);//pull-up
  DDRB |= (1 << DDB5);//acender o LED; pino de saída
  sei();//habilita todas as interrupções

  while(1)
  {
    PORTB ^= (1 << PORTB5); //pino 10 - PB2 muda de low para high
    _delay_ms(1500);
  }
  
}

ISR(PCINT0_vect)
{
   PORTB ^= (1 << PORTB5);
}
