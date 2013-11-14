#include <msp430.h> 

#define led BIT0
#define button BIT3

void setWatchDog(void);
void setLed(void);
void setButton(void);
void setInterruption(void);
void setTimer(void);

unsigned int switchOn = 0;

int main(void) {
    setWatchDog();
	setLed();
    setButton();
    setInterruption();
    setTimer();

    _BIS_SR(CPUOFF + GIE);

	return 0;
}

void setWatchDog(void){
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
}
void setLed(void){
    P1DIR |= led;   //Set P1.0 as output
    P1OUT &= ~led;  //Switch led off
}
void setButton(void){
    P1DIR &= ~button;   //Set P1.3 as input
	P1REN |= button;    //Enable P1.3 for input
	P1OUT |= button;    //Set P1.3 pullup
}
void setInterruption(void){
	P1IE = button;  //Enable interruption for P1.3
	P1IFG = 0x0;    //Clear interruption flag
}
void setTimer(void){
    CCTL0 = CCIE;                       //Enable interruption for timer
    TA0CTL = TASSEL_2 + MC_1 + ID_3;    //Set up/down + 
    CCR0 = 62500;                       //Define counter
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerA(void){
	if (switchOn)
		P1OUT ^= led;   //Change state of led
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	if (!(P1IFG & button))
		return;

	if (switchOn){
		switchOn = 0;
		P1OUT &= ~led;
	}
	else
		switchOn = 1;

	P1IFG = 0x0;
	__delay_cycles(600000);
}
