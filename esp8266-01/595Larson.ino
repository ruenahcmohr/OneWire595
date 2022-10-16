/*
thankyou @YLRabbit for the code starter!

This is one wire 595 operation by @ruenahcmohr

*/

#define OUT_PIN 0


  #define SCLKlow()              digitalWrite(OUT_PIN, LOW);
  #define SCLKhigh()             digitalWrite(OUT_PIN, HIGH);

  
  #define SendZero()            SCLKlow(); delayMicroseconds(36-2); SCLKhigh(); delayMicroseconds(10-2) 
  #define SendOne()             SCLKlow(); delayMicroseconds(5-2); SCLKhigh(); delayMicroseconds(10-2)  // 2us overhead 


void setup() {
  pinMode(OUT_PIN, OUTPUT);
}

void loop() {

  uint8_t i;

  for( i = 0x02; i != 0; i<<=1) {
      send8(i);              
      delayMicroseconds(49000);   
    }
    for( i = 0x40; i != 0; i>>=1) {
      send8(i);                   
      delayMicroseconds(49000);
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
  delayMicroseconds(32-2); // delay to clock in latch signal
}

void presend8 (unsigned int bits) {
  uint8_t temp;  
  for( temp = (0x01); temp != 0; temp <<= 1) {    
    if ( (bits & temp) != 0 ) {    SendOne();
    } else {                       SendZero();
    }    
  }   
}
