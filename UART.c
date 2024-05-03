#include <xc.h>
#include <pic18f4550.h>
#include<stdio.h>
#define _XTAL_FREQ 48000000
#define Fosc 48000000UL

void InitUART(unsigned int baudrate)
{
  TRISCbits.RC6 = 0;                        //TX pin set as output
  TRISCbits.RC7 = 1;                        //RX pin set as input

  SPBRG = (unsigned char)(((Fosc /64)/baudrate)-1);
  BAUDCON = 0b00000000;                     //Non-inverted data; 8-bit baudrate generator

  TXSTA = 0b00100000;                       //Asynchronous 8-bit; Transmit enabled; Low speed baudrate select
  RCSTA = 0b10010000;                       //Serial port enabled; 8-bit data; single receive enabled
}



void UART_SendChar(char data)
{
    while (!TXIF) // Wait for the TX buffer to be empty
        continue;

    TXREG = data; // Transmit the character
}

void main(void)
{
    /*
    TRISC6 = 0; // TX Pin set as output
    UART_Init(); // Initialize UART
    */
    
    InitUART(9600);
    while (1)
    {
        UART_SendChar('P'); // Send 'P'
        __delay_ms(1000);   // Delay for 1 second
        
        UART_SendChar('I'); // Send 'I'
        __delay_ms(1000);   // Delay for 1 second
        
        UART_SendChar('C'); // Send 'C'
        __delay_ms(1000);   // Delay for 1 second
        
        UART_SendChar('T'); // Send 'T'
        __delay_ms(1000);   // Delay for 1 second
        
        UART_SendChar(' '); // Send ' '
        __delay_ms(1000);   // Delay for 1 second
    }

    return;
}
