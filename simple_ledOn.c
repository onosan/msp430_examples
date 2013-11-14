#include <msp430.h> 

#define led BIT0

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	//Stop watchdog timer
	
    P1DIR = led;    //Set Port 1.0 as output (LED)
    P1OUT |= led;   //switch led on

    return 0;
}
