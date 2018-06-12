// ********Documentation Section **********
// Author : Nipun Pruthi
// May 22nd, 18
// This program is developed jff
// -------------------------------------------------------------------------

// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Using simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control
#define PF4 			(*((volatile unsigned long *)0x40025040))
#define PF2 			(*((volatile unsigned long *)0x40025010))

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(void); // 100ms delay

int main(void){ unsigned long volatile delay;
  	TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
  //    initialization goes here
	
	SYSCTL_RCGC2_R |= 0x020;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_AFSEL_R = 0x0;
	GPIO_PORTF_DEN_R = 0x14;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_DIR_R = 0x04;
	GPIO_PORTF_PUR_R = 0x10;
	GPIO_PORTF_DATA_R = 0x04;
	
	EnableInterrupts();           // enable interrupts for the grader

	while(1){

		Delay100ms();
		if( PF4 == 0x10)
			PF2 = 0x04;
		else
			PF2 = PF2 ^ 0x04;

	}
  
	/* while (1){
	  Delay100ms();
	  while( PF4 == 0 ){
	    PF2 = ~PF2;
	    Delay100ms();
	  }
	  PF2 = 0x04;
	}
	*/
}

void Delay100ms(void){
	unsigned long i;
	i = 1333333;
	while ( i > 0 ) {
	i = i - 1;
	}
}
