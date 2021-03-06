#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>
#include "musical_notes.h"
#include "SparkFun_Tlc5940.h"
#include <math.h>

// For speaker
int speakerPin = 52; // speaker connected to digital pin 9

// all the following pins should be PWM
#define FIVE_MIN  5*60*1000
#define ONE_MIN 60*1000

int NUM_LEDS = 9;

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

//for games
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define MAX_NUM_COLOR 4
int gameBlocks[9] = {0,1,2,3,4,5,6,7,8};  //to store the block No.
int numOfBlocks;
int numOfColor; //for game 2
int game1_counter = 0;
unsigned long game1_currentTime;
unsigned long game1_iniTime;
int game1_prev_mode = EASY;
int game1_current_mode = EASY;
int game2_counter = 0;
int game2_current_mode = EASY;
int game2_prev_mode = EASY;
unsigned long game2_currentTime;
unsigned long game2_iniTime;
int game2Color[MAX_NUM_COLOR][3];

void setup() {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
//  for (int i=0;i<9;i++){
//     pinMode(buttons[i], INPUT);
//    for (int j=0;j<3;j++){
//      pinMode((Block_LED[i])[j],OUTPUT);
//    }
//  }
  pinMode(52, OUTPUT);
  Serial.begin(9600);
  iniTime = millis();

  /* Call Tlc.init() to setup the tlc.
     You can optionally pass an initial PWM value (0 - 4095) for all channels.*/
  Tlc.init();
  Tlc.clear();
}

void loop() {
    currentTime = millis();
    if (currentTime-iniTime < FIVE_MIN){
      funLight1();
//        game1();
        //win();
        //colorFlow();
//        ColorFlow2();
    }

}
