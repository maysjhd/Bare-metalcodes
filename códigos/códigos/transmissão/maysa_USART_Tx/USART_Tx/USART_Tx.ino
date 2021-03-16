#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>

void UART_Tx();
void UART_Txchar(char data);

int main()
{
  UART_Tx();
   
  while(1)
  {
     UART_Txchar('M');
    _delay_ms(1000);/*de 1 em 1s*/
  }
  return 0;
}


void UART_Tx()/*função para Tx*/
{
  UBRR0L = 104; /*UBRRnL contains the eight least significant bits of the USART baud rate*/
  UCSR0B |= (1 << TXEN0);/*TXEN0 para habilitar o USART*/
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01)| (1 << UCSZ02);/*define o tamanho do caractere (aqui está para 1B)*/
}


void UART_Txchar(char data)
{ 
    /*UCSR0A |= (1 << UDRE0);/*| (1 << U2X0);/*UDRE0(sinalizador)para podermos setar o buffer de transmissão*/
    UDR0 = data;/*transmitir do Tx do meu uc pro meu computador*/
    UDR0 = '\n';
}
