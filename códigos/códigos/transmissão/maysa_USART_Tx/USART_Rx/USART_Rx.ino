/*RECEBER BYTES POR INTERRUPÇÃO*/
#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void UART_Tx();
void UART_Txchar(char data);
void UART_Rxchar();


int main
{
  /*O processo de inicialização normalmente consiste em definir o baud rate, definir o frame format e habilitar o Tx ou o Rx dependendo do uso.
  Para operação USART orientada por interrupção, o sinalizador de interrupção global deve ser limpo(e as interrupções desabilitadas globalmente) 
  ao fazer a inicialização.*/
  
  sei();
  
  UBRR0H = 0;
  UBRR0L = 104;
  UCSR0B |= (1 << RXEN0)| (1 << RXCIE0): ;/*Setar RXCIE0 permite a interrupção no sinalizador RXC0. 
  Interrupção completa de recebimento USART:
  - RXCIE0 for escrito em um;
  - SREG for gravado em um;
  - RXC0 em UCSR0A for definido.*/
  UCSR0A |= (1 << TXC0)|(1 << RXC0); /*Este bit de sinalizador é definido quando há dados não lidos no buffer de recebimento e limpo quando o buffer de
  recebimento está vazio; Se o receptor estiver desabilitado, o buffer de recepção será esvaziado e, conseqüentemente, o bit RXC0 se tornará zero.*/
  UCSR0C |= (1 << UCSRZ00) | (1 << UCSRZ01) | (1 << UCSRZ02); /*caracter de 9 bits*/

  cli();
}




ISR(USART_Rx_vect)
{
  PORTB ^= (1 << PORTB5);
}
