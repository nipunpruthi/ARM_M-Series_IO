// 0. Documentation Section
// C7, SOS
// Author : Nipun Pruthi
// Date : 22nd May, 18

// Input from PF4(SW1) and PF0(SW2), Output from PF1(Red LED)
// Precessing SW1 starts SOS (Red LED flashed SOS)
//  S : Toggle light 3 times with .5 second gap b/n ON and OFF
//  O : Toggle light 3 times with 2 seconds gap b/n ON and OFF
//  S : Toggle light 3 times with .5 second gap b/n ON and OFF
// Precessing SW2 stops SOS

// Pseudo-Code
// (1) Init Ports
// (2) If sw1 not pressed, repeat step 2
// (3) If sw1 is pressed, Flash sos, delay 5 sec
// (4) If sw2 not pressed, go to step 3
// (5) if sw2 pressed, go to step 2

// 1. Pre-processor Directives Section
// Constant declarations to access ports registers using symbolic names
// instead of addressess
#define GPIO_PORTF_DATA_R   (*((volatile unsigned long *) 0x400253FC))
#define SYSCTL_RCGC2_R      (*((volatile unsigned long *) 0x400FE108))
#define GPIO_PORTF_DIR_R    (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_DEN_R    (*((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_AFSEL_R  (*((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_PUR_R    (*((volatile unsigned long *) 0x40025510))
#define GPIO_PORTF_AMSEL_R  (*((volatile unsigned long *) 0x40025528))
#define GPIO_PORTF_PCTL_R   (*((volatile unsigned long *) 0x4002552C))
#define GPIO_PORTF_LOCK_R   (*((volatile unsigned long *) 0x40025520))
#define GPIO_PORTF_CR_R     (*((volatile unsigned long *) 0x40025524))
#define PF4                 (*((volatile unsigned long *) 0x40025040))
#define PF0                 (*((volatile unsigned long *) 0x40025004))
#define PF1                 (*((volatile unsigned long *) 0x40025008))

// 2. Declarations Section
//    Global Variable
unsigned long SW1; // input from PF4
unsigned long SW2; // input from PF0
//Function Prototypes
void PortF_Init(void);
void Flash_SOS(void);
void delay(unsigned long half_secs);

// 3. Subroutine Section
//    Main: Mandatory for a C program to be executable
int main(void){
    PortF_Init();
    while (1){
        do{
            SW1 = PF4 & 0x10;
        }while(SW1 == 0x10);

        do {
            Flash_SOS();
            SW2 = PF0 & 0x01;

        }while(SW2 == 0x01);
    }
}

// Subroutine to initialize port F
// Input : None
// Output : None
// Notes : ..........
void PortF_Init(){
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x020;            // 1) activate clk for port F
    delay = SYSCTL_RCGC2_R;             // allow time for clk to start
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     // 2) unlock GPIO port F
    GPIO_PORTF_CR_R |= 0x13;             // allow changes to PF0-4
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTF_AMSEL_R &= ~0x13;          // 3) disable analog on PF, Analog_Mode_SELect
    GPIO_PORTF_PCTL_R &= ~0x13;           // 4) PCTL GPIO on PF0-4, Port_ConTroL_Register to select regular digital function
    GPIO_PORTF_DIR_R |= 0x02;            // 5.1) PF0 and PF4 in
    GPIO_PORTF_DIR_R &= ~0x11// 5.2) PF1 output
    GPIO_PORTF_AFSEL_R &= ~0x13;          // 6) disable alt function on PF0-7
    GPIO_PORTF_PUR_R |= 0x11;            // enable pullup register on PF0 and PF4
    GPIO_PORTF_DEN_R |= 0x13;            // 7) enable digital io on PF0-4
}

// Subroutine for SOS
// Input : None
// Output : None
// Notes : ...............
void Flash_SOS(void){
    // S
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);
    // O
    PF1 |= 0x2;     delay(4);
    PF1 &= ~0x2;    delay(4);
    PF1 |= 0x2;     delay(4);
    PF1 &= ~0x2;    delay(4);
    PF1 |= 0x2;     delay(4);
    PF1 &= ~0x2;    delay(4);
    // S
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);
    PF1 |= 0x2;     delay(1);
    PF1 &= ~0x2;    delay(1);

    delay(10);  
}

void delay(unsigned long half_secs){
    unsigned long i;
    while (half_secs > 0){
        i = 1333333*5;
        while ( i > 0){
            i--;
        }
        half_secs--;
    }
}