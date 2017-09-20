#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>
#include "musical_notes.h"
//// for only one RGB LED
//int redPin= 12;
//int greenPin = 11;
//int bluePin = 10;
//void setup() {
//  pinMode(redPin, OUTPUT);
//  pinMode(greenPin, OUTPUT);
//  pinMode(bluePin, OUTPUT);
//  Serial.begin(9600);
//}
//void loop() {
//  int state=random(0, 100);
//  float x=state/100.0;
//  Serial.println(x);
//    if (x<0.1){
//      digitalWrite(redPin,LOW);
//      digitalWrite(greenPin,LOW);
//      digitalWrite(bluePin,LOW);
//      Serial.println("OFF");
//    } else {
//      int r=random(0, 255);
//      int g=random(0, 255);
//      int b=random(0, 255);
//      Serial.print(r);
//      Serial.print(", ");
//      Serial.print(g);
//      Serial.print(", ");
//      Serial.println(b);
//      analogWrite(redPin,r);
//      analogWrite(greenPin,g);
//      analogWrite(bluePin,b);
//    }
//  delay(500);
//}


///////////////////////////////////////////////////////////////////////////

// For speaker
int speakerPin = 52; // speaker connected to digital pin 9

// all the following pins should be PWM
#define FIVE_MIN  5*60*1000

// LED pins of each block
int Block11_LED[3] = {1,2,3};
int Block12_LED[3] = {4,5,6};
int Block13_LED[3] = {7,8,9};
int Block21_LED[3] = {10,11,12};
int Block22_LED[3] = {13,14,15};
int Block23_LED[3] = {16,17,18};
int Block31_LED[3] = {19,20,21};
int Block32_LED[3] = {22,23,24};
int Block33_LED[3] = {25,26,27};

int NUM_LEDS = 9;

int* Block_LED[]={Block11_LED,Block12_LED,Block13_LED,Block21_LED,
    Block22_LED,Block23_LED,Block31_LED,Block32_LED,Block33_LED};

int buttons[] = {28,29,30,31,32,33,34,35,36};

//default timeout is 5 mins, different game modes will overwrite it
int timeout = FIVE_MIN;
unsigned long currentTime;
unsigned long iniTime;

//for protocal
#define bytesReceive 8
char command[bytesReceive]; //used to store the command from serial communication

//Every time initialise a game, this value need to be set to True
//after the game finished, need to reset this to false
int gameLock = false;

//for game 1
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2
#define ONE_MIN 60*1000
#define EASY 1
#define MEDIUM 2
#define HARD 3
int game1Blocks[9] = {0,1,2,3,4,5,6,7,8};  //to store the block No.
int numOfBlocks;
int game1_counter = 0;
unsigned long game1_currentTime;
unsigned long game1_iniTime;
int game1_prev_mode = EASY;
int game1_current_mode = EASY;

//for game 2
int game2_counter = 0;
int game2_current_mode = EASY;
int game2_prev_mode = EASY;
unsigned long game2_currentTime;
unsigned long game2_iniTime;

void setup() {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  for (int i=0;i<9;i++){
     pinMode(buttons[i], INPUT);
    for (int j=0;j<3;j++){
      pinMode((Block_LED[i])[j],OUTPUT);
    }
  }
  pinMode(52, OUTPUT);
  Serial.begin(19200);
  iniTime = millis();
}

void loop() {
    currentTime = millis();
    if (currentTime-iniTime < FIVE_MIN){
        game1();
        //win();
    }

}
