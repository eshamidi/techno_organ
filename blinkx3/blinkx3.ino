//Color Organ 2.0 -- designed for house + techno. 

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//color declarations 
byte w = 0;  //white
byte k = 63; //black
byte r = 54; //red
byte g = 45; //green
byte y = 36; //yellow
byte x = 18; //pink
byte q = 9; //lite blue 
byte b = 27; //blue
byte colorarr[] = {k, w, r, b,x, g, y, q }; //array storing color values 
byte thresh = 100; //tunable threshold for audio activation

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
int pgm = 6; //determines which mode 
void loop() {


switch(pgm){

//Program 1: basic blinky lighty thing; lights flash randomly to beat 
case 1: 
{  
int i = random(0, 8);
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    SensorVal = analogRead(SensorPin);
    if(SensorVal > thresh){
    shiftOut(dataPin, clockPin, MSBFIRST, colorarr[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(300);
    }
    
}
break;


case 2: //boring blue light; placeholder for something cooler 
{ 
  for(int i = 0; i<2; i++){
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    SensorVal = analogRead(SensorPin);
    if(SensorVal > 100){
    shiftOut(dataPin, clockPin, MSBFIRST, b);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(100);
    }
    
}
break;
}
case 3: ///test program - no analog in, just cycles thru colors 
{
  for(int i = 0; i<8; i++){
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:

    shiftOut(dataPin, clockPin, MSBFIRST, colorarr[i]);  
    
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(400);
    
  
}
break;
}

case 4: /// simple strobe flash
{
  
  byte strbarr1[32];
  int sdice = random(1,8);
  //colorarr[0] = p;
  for(int z = 0; z < 32; z++){
  if(z%2 != 0){
  strbarr1[z] = k; //black
  }
  else{
    strbarr1[z] = colorarr[sdice] ; //color lights will strobe randomly
  }
  }

   //SensorVal = analogRead(SensorPin);
  //if(SensorVal > thresh){

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
  delay(300);
  //}
    


break;
}

case 5: //pulse width modulation jawn 
{
  byte pwmarr1[32][32]; //16x16 array. 16 steps of resolution for PWM 
  int sdice = random(1,8); //pick color
  int color = colorarr[sdice];
  int color2 = k;
  
  for(int px = 0; px < 32; px++){
   
      for(int z = 0; z < 32; z++){
        if(z <= px){
        pwmarr1[px][z] = color; //color to start 
        }
        else{
          pwmarr1[px][z] = color2; //color to be faded to
        }

  }

    
  }
 
 

 //  SensorVal = analogRead(SensorPin);
 // if(SensorVal > 100){

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

    
    delay(300);

    
 break; 
  
}

case 6: //mellow PWM color blending
{
  byte pwmarr1[32][32]; //nxn array. n steps of resolution for n steps of PWM 
  int color1, color2; 
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
 
 

 //  SensorVal = analogRead(SensorPin);
 // if(SensorVal > 100){
 
  for(int PW = 0; PW < 32; PW++){ //32 steps of pulse width resolution
    int duty = random(1,20);
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
