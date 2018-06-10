// ***** 0. Documentation Section
// This program calculates the area of square shape rooms
// Author : Nipun Pruthi
// Date : 10th May, 18

// 1. Pre-processor directive section
#include <stdio.h>
#include "uart.h"


// 2. Global Declaration Section
// Global Variable
unsigned long error;

// Function Prototypes
unsigned long Calc_Area (unsigned long s); // Calculates Area, expects an unsigned long
					   // and return an unsigned long
void Initialise(void); // Global variable initialisation


// 3. Subroutines Section
// Main: Mandatory routine for the C program to be executable
int main(void){
  unsigned long side;
  unsigned long area;
  
  UART_Init(); 		// call subroutine to init uart lib
  Initialise();		// initialise the global variable
  printf("This program calculates the area of square shaped rooms\n");

  while(side != 0){
    printf("Enter side (0 to exit)\n");
		scanf("%ld", &side);
    area = Calc_Area(side);
    if( area != 0 )
    printf("Area of the room with side of %ld m is %ld sq m\n", side, area);
    else if(side > 25)
      printf("Side too long\n");
    else
      printf("GoodBye, Error occured = %ld times\n",error);

}}

// Initialise Global variable
// Input : None
// Ouput : None
// Notes : ...
void Initialise(void){
  error = 0;
}

// Calculates Area
// Input : side of room in meter (unsigned long)
// Ouput : area of the room (unsigned long)
// Notes : ...
unsigned long Calc_Area( unsigned long s){
  unsigned long result;
  if( s < 25)
    result = s * s;
  else{
    result = 0;
    error++ ;
  }
  return(result);
}
