#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>

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
// all the following pins should be PWM

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


void setup() {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  // all LED pins as OUTPUT

  for (int i=0;i<9;i++){
     pinMode(buttons[i], INPUT);
    for (int j=0;j<3;j++){
      pinMode((Block_LED[i])[j],OUTPUT);
    }
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  game1();
  delay(500);
}
