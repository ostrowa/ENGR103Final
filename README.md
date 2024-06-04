# ENGR103Final
Game for ENGR 103: light loops &amp; pressing a button
Game Description/Rules Draft
Turn the switch on to start the neopixels cycling around the Circuit Playground board. Press button B when the light next to it becomes lit up. The light cycle will speed up after each successful button press. If the player fails to press the button at the correct moment, they lose. Once the player successfully completes all levels, they win and the game begins again.
Inputs & Outputs Specifications
Inputs:
Switch 
Function: When the switch is on, the game will run. Turning the switch off turns the game off. 
Range: 0,1
Control: If the sound and light functions for the game are on or off.
	Left button
Function: If the button is pressed at the correct time (indicated by neopixels), the game will advance to the next level. If the button is pressed at the incorrect time, the game will indicate loss and will reset.
Range: 0,1
Control: Player must press at the correct time to advance the level. 
Outputs:
	NeoPixels
Function: Cycle around the CPX board to indicate when the player should press the button. If the player presses the button at the incorrect time, all pixels will light up red. If the player presses the button at the correct time, all pixels will light up green.
Range: 0-9
Control: Indicate to the player when to press the button to advance. Indicate to the player when they have lost.
	Speaker
Function: Play a fun sound when the player presses the button correctly. Play a sad tune when they lose. *No longer using speech functions.
Range: MIDI library, 0-126
Control: Indicate to the player when they successfully pressed the button, and when they have lost. *no longer indicates when to start
