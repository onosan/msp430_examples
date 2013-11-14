#include <msp430.h> 

#define led BIT0
#define button BIT3

void setWatchDog(void);
void setLed(void);
void setButton(void);
void setInterruption(void);

int main(void) {
    setWatchDog();
	setLed();
	setButton();
    setInterruption();

    _BIS_SR(CPUOFF + GIE);

	return 0;
}

void setWatchDog(void){
	WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
}
void setLed(void){
	P1DIR |= led;   //Set P1.0 as output
	P1OUT &= ~led;  //Switch led off
}
void setButton(void){
	P1DIR &= ~button;   //Set P1.3 as input
	P1REN |= button;    //Enable P1.3 for input
	P1OUT |= button;    //Set P1.3 as pullup
}
void setInterruption(void){
	P1IE = button;      //Enable interruption for P1.3
	P1IFG = 0x0;        //Clean interruption flag
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	P1OUT ^= led;       //Change state of Led
	P1IFG = 0x0;        //Clean interruption flag

	__delay_cycles(600000);
}
