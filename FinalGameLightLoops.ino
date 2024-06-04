#include <Adafruit_CircuitPlayground.h>

//declaring variables
volatile bool switchFlag;
volatile bool buttFlag;

//attach variables to read pins
bool buttState = digitalRead(5);
bool switchState = digitalRead(7);

//Variables for incrementing levels
int levelOne = 300;
int levelUp = 50;
int speed = levelOne;

//Midi libraries and storing songs
float midi[127];
int A_four = 440; 

int loserSong[5][2] = {
  {61, 200},
  {60, 200},
  {59, 200},
  {58, 200},
  {57, 800},
};

int pointSong[2][2] = {
  {73, 50},
  {78, 200},
};

//start all libraries/monitors, attach interrupts to switch and button
void setup() {

Serial.begin(9600);
CircuitPlayground.begin();
generateMIDI();
attachInterrupt(digitalPinToInterrupt(7), switchISR, CHANGE);
attachInterrupt(digitalPinToInterrupt(5), buttISR, RISING);

}

//MIDI library calculations
void generateMIDI(){
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}

//switch interrupt 
void switchISR(){
//sets switch to true
  switchFlag = 1;
}

//button interrupt
void buttISR(){
//sets button to true
  buttFlag = 1;
}

//indicates a point
void point(){
//set all 10 neopixels to green
  for(int i=0; i<10; i++){
    CircuitPlayground.setPixelColor(i,0,200,10);
  }
//play point tone
  for(int i = 0; i < sizeof(pointSong) / sizeof(pointSong[0]); i++){
    CircuitPlayground.playTone(midi[pointSong[i][0]], pointSong[i][1]);
    Serial.println(midi[pointSong[i][0]]);
    delay(1);
  }
//wait a bit before advancing
  delay(25);
}

//indicates loss
void loser(){
//set all 10 neopixels red
  for(int i=0; i<10; i++){
    CircuitPlayground.setPixelColor(i,200,0,20);
  }
//play the loser song
  for(int i = 0; i < sizeof(loserSong) / sizeof(loserSong[0]); i++){
  CircuitPlayground.playTone(midi[loserSong[i][0]], loserSong[i][1]);
  Serial.println(midi[loserSong[i][0]]);
  delay(1);
  }
//wait a bit before re-starting
  delay(75);
}

//Chet's rainbow function: Indicates that you beat the game
void Winner(int currentSpeed, int stripLen) {
  // Make an offset based on the current millisecond count scaled by the current speed.
  uint32_t offset = millis() / currentSpeed;
  // Loop through each pixel and set it to an incremental color wheel value.
  for(int i=0; i<10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
}

//The game:
void loop() {
//switchFlag interrupt
  if(switchFlag){
    delay(5);
    switchState = digitalRead(7);
    switchFlag = 0;
  }
//When swich is on, run the game
  if(switchState){
//most of the game funciton is enclosed in this for loop. It cycles the neopixels around the CPX board.
    for(int i=0; i < 10; i++){  
//set neopixel to purple
      CircuitPlayground.setPixelColor(i,200,0,250);
//serial monitor prints these values for testing purposes. Not applicable to game function.
      Serial.print("button:");
      Serial.println(buttFlag);
      Serial.print("i:");
      Serial.println(i);
      Serial.print("speed");
      Serial.println(speed);
//if the light is on neopixel 8
      if(i==8){          
//if the button is pressed, indicate a point and level up: decrease speed variable (lights cycle faster). Reset button to not pressed.
        if(buttFlag){
          point();
          buttFlag = 0;
          speed -= levelUp;

          if(speed<=20){
//if "speed" becomes too low, all levels have been completed. Indicate player win
              for(int j=0; j<500; j++){
                if(j){
                  Winner(5, 10);
                }
              }
//reset "speed" to level one, this restarts the levels after winning.
            delay(250);
            speed = levelOne;
          }
        }
      }
//if the button is pressed when the light is not on neopixel 8, indicate player lost. reset "speed" to level one, this restarts the levels after losing. Reset button to not pressed.
      else if(buttFlag){   
        loser();
        buttFlag = 0;
        speed = levelOne;
      }
//delay by "speed" value before advancing to the next light on the board
    delay(speed);         
    CircuitPlayground.clearPixels();
    }
  }
//when the switch is off, turn off the game.
  else{
      CircuitPlayground.clearPixels();
  }
}
