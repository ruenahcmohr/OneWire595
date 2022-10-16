/*
 *  1 wire 74hc595 output, and 74hc165 input demo
 * 
 *  This just copies the 8 bits from the input to the outputs.
 *  
 *  the 74hc595 is controlled by GPIO 0 and the return data from the shift register 
 *  comes back on GPIO2
 *  
 *  If expanding this to an array of 595 and 165, I recommend buffering the signals with a 74HC14
 *  
 *  @ruenahcmohr oct 2022
 * 
 */



  #define OUT_PIN 0
  #define IN_PIN 2


  #define SCLKlow()              digitalWrite(OUT_PIN, LOW);
  #define SCLKhigh()             digitalWrite(OUT_PIN, HIGH);

  // a bit is read for each bit written
  

  #define RxDSample()           RxD<<=1; RxD |= digitalRead(IN_PIN)

  #define SendZero()            RxDSample(); SCLKlow(); delayMicroseconds(36-2); SCLKhigh(); delayMicroseconds(10-2) 
  #define SendOne()             RxDSample(); SCLKlow(); delayMicroseconds(5-2); SCLKhigh(); delayMicroseconds(10-2)  // 2us overhead 


uint8_t RxD;


void setup() {
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, INPUT);
}

void loop() {

   send8(RxD);      // during the write RxD is automatically updated.        
   delayMicroseconds(1000);   
   
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
