This program employs a switch statement in the control loop to manage 6 programs. At this point, only 1 LED board 
(2x2 RGB LEDs, or 6 bits of LED data) is being controlled. 

Program 1: picks a random color out of the 8-color array, updates only when the analog audio sensor is above a certain threshold

Program 2: LEDs are updated to blue (this was a test case - I was having trouble with blue)

Program 3: Test program - cycles rapidly through color array to test function of all colors

Program 4: Generates a strobing pattern of random color. An array is made consisting of alternating color and black. 
This is rapidly pushed to the LEDs. 

Program 5: Fades from a random color to black. 

Program 6: Blends between all 8 colors. 
