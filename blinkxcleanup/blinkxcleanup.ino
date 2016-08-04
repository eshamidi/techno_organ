//Color Organ 2.0 -- designed for house + techno. 

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
//  Serial.begin(9600);
//  Serial.println("Serial Communication Established");

}
int SensorPin = A1; //audio in 

int SensorVal = 0; 
//determines which mode 


void blinkit(int pgm, byte color1, byte color2){


  switch(pgm){

//Program 1: basic blinky lighty thing; lights flash randomly to beat 
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
    SensorVal = analogRead(SensorPin);
    shiftOut(dataPin, clockPin, MSBFIRST, colorarr[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
}
break;


case 2: //boring blue light; placeholder for something cooler 
{ 
  for(int i = 0; i<2; i++){
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:

    shiftOut(dataPin, clockPin, MSBFIRST, b);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH); 
}
break;
}

case 3: //subdivisions. quarter notes/eighth notes/we'll see.
{
  for(int i = 0; i<8; i++){
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:

    shiftOut(dataPin, clockPin, MSBFIRST, colorarr[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(500);
    
  
}
break;
}

case 4: /// simple strobe flash
{
  
  byte strbarr1[32];
  int sdice = random(1,8);

  for(int z = 0; z < 32; z++){
  if(z%2 != 0){
    if(color1==color2){
      strbarr1[z] = k; //black in random case 
    }
    else{
  strbarr1[z] = color1; 
    }
  }
  else{
    if(color1==color2){
      strbarr1[z] = colorarr[sdice]; //random color strobe 
    }
    else{
    strbarr1[z] = color2 ; //selected color
    }
  }
  }


  for(int i = 0; i<32; i++){
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:

    shiftOut(dataPin, clockPin, MSBFIRST, strbarr1[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(20);
  }

    


break;
}

case 5: //pulse width modulation jawn 
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

               //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);

    


    
 break; 
  
}

case 6: //mellow PWM color blending
{
  byte pwmarr1[32][32]; //nxn array. n steps of resolution for n steps of PWM 

  for(int fade = 1; fade < 8; fade++){
    
  
   color1 = colorarr[fade];
  if(fade == 7){
    color2 = colorarr[1];
  }
  else{
    color2 = colorarr[fade+1];
  }
  
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
    int duty = random(1,30);
    for(int DC = 0; DC < duty; DC++){ //duty cycle - repeat same duty cycle 5x 
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

               //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);

    
    
  }
    
 break; 
  
}   



default: 
break;
}








  
}






void loop() {

  //for(int x = 3; x < 6; x++){
  //  for(int z = 0; z<4; z++){
  //blinkit(5,b,g);
  //delay(200);
  //blinkit(5,g,b);
  delay(1000);
  blinkit(6,g+g*8,k+k*8);


}
