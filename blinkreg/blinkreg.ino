//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}

/* important numbers 
 *  low bit is on. 
 *    int LEDARR[8] = { 127, 9, 18, 27,36,45,54, 63 }; example array that steps thru all colors x2 
 *    9 = light blue (1)
 *    18 = purple (2)
 *    27 = blue (3) MSB
 *    36 = yellow (4)
 *    45 = green (5) middle
 *    54 = red (6) LSB
 *    63 = off (7)
 *    64 = white (8)
 *    
 */

  int LEDARR[8][8] = {
   
    { 63, 63, 63, 63, 63, 63, 63, 63 },
    { 18, 63, 63, 63, 63, 63, 63, 63 },
    { 18, 18, 63, 63, 63, 63, 63, 63 },
    { 18, 18, 18, 63, 63, 63, 63, 63 },
    { 18, 18, 18, 18, 63, 63, 63, 63 },
    { 18, 18, 18, 18, 18, 63, 63, 63 },
    { 18, 18, 18, 18, 18, 18, 18, 63 },
    { 18, 18, 18, 18, 18, 18, 18, 18 },
    
  };

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for(int PW = 0; PW < 7; PW++){
    for(int DC = 0; DC < 40; DC++){
      for (int Display = 0; Display < 7; Display++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, LEDARR[Display][PW]);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    
      }
      }
    delay(1);
    }
    delay(1000);
}

