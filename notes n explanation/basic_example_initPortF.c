// ******* 0. Documentation Section
// This program explain and implement function to initialize the PORTF
// Author : Nipun Pruthi
// Date : 19th May, 18

// ******** Steps
// 1. Activate the clock of the Port.
// 2. Unlock the port; unlocking is needed only for pins PC0-3, PD7 and PF0.
// 3. Disable analog function of the pin
// 4. Clear bits in PCTL to select regular digital function.
// 5. Set its direction register.
// 6. Clear bit in alternate direction register.
// 7. Enable Digital Register.

// We need to add a short delay between activating the clock and accessing the port registers.

// 1. Pre-processor directive section
#include 'tm4c123ge6pm.h'
// constant declarations to access port registers using symbolic names instead of address
#define GPIO_PORTF_DATA_R 	(*((volatile unsigned long *) 0x400253FC )) // this will change all 8-bit
#define SYSCTL_RCGC2_R 		(*((volatile unsigned long *) 0x400FE108)) // always this
#define GPIO_PORTF_DIR_R 	(*((volatile unsigned long *) 0x40025400)) // use table
#define GPIO_PORTF_DEN_R 	(*((volatile unsigned long *) 0x4002551C)) // use table
#define GPIO_PORTF_AFSEL_R 	(*((volatile unsigned long *) 0x40025420)) // use table
#define GPIO_PORTF_PUR_R 	(*((volatile unsigned long *) 0x40025510)) // use table
#define GPIO_PORTF_AMSEL_R 	(*((volatile unsigned long *) 0x40025528))
#define GPIO_PORTF_PCTL_R 	(*((volatile unsigned long *) 0x4002552C))
#define GPIO_PORTF_LOCK_R 	(*((volatile unsigned long *) 0x40025520))
#define GPIO_PORTF_CR_R 	(*((volatile unsigned long *) 0x40025524))

// 2. Global Declaration Section
// Global variable
unsigned long in; // input from PF4
unsigned long out; // output to PF2 (blue LED)

// Function Protypes
void PortF_Init(void);

// 3. Subroutines Section
// MAIN : Mandatory for a C program to be executable
int main(void){
    PortF_Init(); // initialize PF0 and PF4 and make them inputs and make PF1-3 out
    
    while(1){
        in = GPIO_PORTF_DATA_R & 0x010; // read PF4 into sw1
        in = in >> 2;                   // shift into position PF2
        out = GPIO_PORTF_DATA_R;
        out = out & 0xfb;
        out = out | in;
        GPIO_PORTF_DATA_R = out;        // output
    }
}
// Subroutine to initialize port F pins for I/O
// PF4 is input switch1 and PF2 is output LED blue
// Input : None
// Output : None
// Notes : ..........
void PortF_Init(void){
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x020;            // 1) activate clk for port F
    delay = SYSCTL_RCGC2_R;             // allow time for clk to start
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     // 2) unlock GPIO port F
    GPIO_PORTF_CR_R = 0x1F;             // allow changes to PF0-4
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTF_AMSEL_R = 0x00;          // 3) disable analog on PF, Analog_Mode_SELect
    GPIO_PORTF_PCTL_R = 0x00;           // 4) PCTL GPIO on PF0-4, Port_ConTroL_Register to select regular digital function
    GPIO_PORTF_DIR_R = 0x0E;            // 5) PF0 and PF4 in, PF1-3 output
    GPIO_PORTF_AFSEL_R = 0x00;          // 6) disable alt function on PF0-7
    GPIO_PORTF_PUR_R = 0x11;            // enable pullup register on PF0 and PF4
    GPIO_PORTF_DEN_R = 0x1F;            // 7) enable digital io on PF0-4
}
/
