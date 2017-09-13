unsigned long time;
unsigned long iniTime;
int blocks[3];

#define HORIZON 0
#define VERTICAL 1
#define DIAGONAL 2

void game1(){
  // iniTime = millis();
  // time = millis();
  // int fiveMin = 5*60*1000;
  // if (time-iniTime > fiveMin){
  //   //go back to funlight mode
  // }

  //pick the right sequence of LEDS
  int pattern = random(9);
  int* LEDS[3];
  switch (pattern){
      case HORIZON:{
        int row = 3*random(3);
        for(int i=0;i<3;i++){
            LEDS[i] = Block_LED[row+i];
            blocks[i] = row+i;
        }
      }
      break;
      case VERTICAL:{
        int col = random(3);
        for(int i=0;i<3;i++){
            LEDS[i] = Block_LED[col+i*3];
            blocks[i] = col+i*3;
        }
      }
      break;
      case DIAGONAL:{
        int dig = random(2);
        if(dig == 0){
            for(int i=0;i<3;i++){
                LEDS[i] = Block_LED[dig+i*4];
                blocks[i] = dig+i*4;
            }
        }
        else{
            for(int i=0;i<3;i++){
                LEDS[i] = Block_LED[dig+1+i*2];
                blocks[i] = dig+1+i*2;
            }
        }
      }
      break;
  }
  for(int i=0;i<3;i++){
    //   for(int j=0;j<3;j++){
    //       digitalWrite(LEDS[i][j], HIGH);
    //       Serial.println(blocks[i]);
    //   }
      SerialCom(blocks[i],125,125,125);
      delay(1500);
    //   for(int j=0;j<3;j++){
    //       digitalWrite(LEDS[i][j], LOW);
    //   }
      SerialCom(blocks[i],255,255,255);
  }
}

// int buttonPressed(){
//     for(int i=0;i<NUM_LEDS;i++){
//         if(digitalRead(buttons[i]) == 0)
//             return i+1;
//     }
//     //return 0 if no buttons
//     return 0;
// }
