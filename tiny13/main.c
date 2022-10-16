/*******************************************************************************
Operate a 74HC595 via 1 wire
*******************************************************************************/
 
/*
  pb0   to one-wire 595 circuit. 
  pb1   
  pb2    
  pb4
  pb3
  pb5


                            +-----U-----+    
               RESET    PB5 | o         | VCC
               ADC3     PB3 |           | PB2 ADC1 
               ADC2     PB4 |   Tiny13  | PB1 OC0B
                        GND |           | PB0 OC0A
                            +-----------+    


*/


// manual port D bits 2 to 7


#include <avr/io.h>
#include "avrcommon.h"



  // Bit positions, PORTD 
  #define SCLK             0

  #define SCLKlow()              ClearBit(SCLK, PORTB)
  #define SCLKhigh()             SetBit(SCLK, PORTB)

  
  #define SendZero()            SCLKlow(); Delay(7); SCLKhigh(); NOP();
  #define SendOne()             SCLKlow(); NOP();     SCLKhigh(); NOP();


  
  void presend8 (unsigned int bits) ;
  void send8 (unsigned int bits);
  void Delay(unsigned int delay) ;
  void Delay2(unsigned int delay) ;


int main (void) {
  unsigned char i;

  // set up directions 
  DDRB = (OUTPUT << PB0 | INPUT << PB1 |INPUT << PB2 |INPUT << PB3 |INPUT << PB4 );             
  
      
  while(1){

    for( i = 0x01; i != 0; i<<=1) {
      send8(i);              
      Delay(11000); // this is a loop delay, but also ensures that the output is latched.
    }
    for( i = 0x80; i != 0; i>>=1) {
      send8(i);              
      Delay(11000);
    }    
    
         
  }

}



// send a 8bit word, msb first
void send8 (unsigned int bits) {
  uint8_t temp;  
  for( temp = (0x01); temp != 0; temp <<= 1) {    
    if ( (bits & temp) != 0 ) {    SendOne();
    } else {                       SendZero();
    }    
  } 
  Delay(1000); // delay to clock in latch signal
}

void presend8 (unsigned int bits) {
  uint8_t temp;  
  for( temp = (0x01); temp != 0; temp <<= 1) {    
    if ( (bits & temp) != 0 ) {    SendOne();
    } else {                       SendZero();
    }    
  }   
}


// these are my awful nop delays, written long before arduino.

void Delay(unsigned int delay) {
  unsigned int x;
  for (x = delay; x != 0; x--) {
    asm volatile ("nop"::); 
  }
}

void Delay2(unsigned int delay) {
  unsigned int x;
  for (x = delay; x != 0; x--) {
    Delay(65000);
  }
}


































