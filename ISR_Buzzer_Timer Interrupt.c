/*
 * File:   newmain.c
 * Author: acer
 *
 * Created on 3 May, 2024, 5:18 PM
 */


#include <xc.h>

 #include<pic18f4550.h>

#define Buzzer LATAbits.LATA5
unsigned int count =0;
void __interrupt() Timer1_ISR()
{
    if(TMR1IF==1)
    {
        TMR1L=0x20;
        TMR1H=0xD1;
        count ++;
        if (count>=1000)//measure upto 1000 ms ie 1 second
        {
            Buzzer =~Buzzer; // Toggle buzzer pin
            count = 0; //reset count 
          
        } 
        TMR1IF = 0; //timers1 overflow flag to 0
           
    }    

}
void main()
{
    //TRISB=0; // set as output port
    TRISAbits.TRISA5 =0; // set buzzer pin RRA5 as output
    GIE=1; //Enable global interrupt
    PEIE=1; //Enable peripheral interrupt
    TMR1IE=1; // enable timer1 overflow interrupt
    TMR1IF=0;
     
    //enable 16 bit TMR1 register no pre - scale , internal timer off
    T1CON=0x80;  // prescale value
    TMR1L=0x20;
    TMR1H=0xD1;   
    TMR1ON=1;     // turn on timer1
    while (1);
    


}