//Color Organ 3.0 -- designed for house + techno. 

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;


byte thresh = 100; //tunable threshold for audio activation

  //color declarations - single LED 
byte w = 0;  //white
byte k = B111 ; //black
byte r = B110; //red
byte g = B101; //green
byte y = B100; //yellow
byte x = B010; //pink
byte q = B001; //lite blue 
byte b = B011; //blue
byte colorarr[] = {k+ k * 8, w+ w*8, r+r*8, b+b*8,x+x*8, g+g*8, y+y*8, q+q*8 }; //array storing 2x color values 

int i = 0;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


}

void blinkit(int pgm, byte color1, byte color2){

 
 switch(pgm){
 case 1: 
{ 
    if(color1==color2){
    i = random(0, 7);
    }
    else{
      i++;
      if(i == 8){
        i = 0;
      }
    }
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    //SensorVal = analogRead(SensorPin);
    shiftOut(dataPin, clockPin, MSBFIRST, colorarr[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
}
break;
   
 case 5:
 {
  byte pwmarr1[32][32]; //16x16 array. 16 steps of resolution for PWM 

  int sdice = random(1,8); //pick color

  
  for(int px = 0; px < 32; px++){
   
      for(int z = 0; z < 32; z++){
        if(z <= px){
        pwmarr1[px][z] = color1; //color to start 
        }
        else{
          pwmarr1[px][z] = color2; //color to be faded to
        }

  }

    
  }
 
 



  for(int PW = 0; PW < 32; PW++){ //32 steps of pulse width resolution
    for(int DC = 0; DC < 3; DC++){ //duty cycle - repeat same duty cycle 5x 
      for (int Display = 0; Display < 32; Display++) { //each duty cycle setting 
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, pwmarr1[Display][PW]);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    
      }
      }
    
    }

    //initialize to black 
    
    digitalWrite(latchPin, LOW);
              // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, color2);  
    shiftOut(dataPin, clockPin, MSBFIRST, color2);  
               //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);

    


 }
break;    

 }

}

void loop() {

  delay(1000);
  //blinkit(5,k+k*8,g+g*8);
  blinkit(1,g+g*8,r+r*8);
  //blinkit(5,g+g*8,k+k*8);

}
