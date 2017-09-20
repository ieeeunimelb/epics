void game1(){
  if(gameLock == false){
      game1_counter = 0;
      gameLock = true;  //lock the mode
      switch(game1_current_mode){
          case EASY:
          game1_easy();
          break;
          case MEDIUM:
          game1_medium();
          break;
          case HARD:
          game1_hard();
          break;
      }
      //clean the buffer
      flush();
      //start timing
      game1_iniTime = millis();
  }
  if(gameLock == true){
      game1_currentTime = millis();
      if (game1_currentTime-game1_iniTime < ONE_MIN){
          if(Serial.available()>0){
              SerialRead(command,bytesReceive);
              if(command[0] == 'b' && (command[1]+'\0') == (game1Blocks[game1_counter]+48)){
                  game1_counter++; //pressed the right button, move the ptr to the next element
              }else if(command[0] == 'b'){
                  //pressed the wrong button, produce a new pattern
                  fail();
                  for(int i=0;i<3;i++){
                      SerialSend(4,255,0,0);
                      delay(500);
                      SerialSend(4,0,0,0);
                      delay(500);
                  }
                  gameLock = false;
                  game1_counter = 0;
              }
          }
          if(game1_counter == numOfBlocks){
              gameLock = false;  //reset the lock
              game1_counter = 0;
              //do something to show that you win!
              win();
              for(int i=0;i<3;i++){
                  SerialSend(4,0,255,0);
                  delay(500);
                  SerialSend(4,0,0,0);
                  delay(500);
              }

              //clean the buffer
              flush();
          }
      }else{ // timeout
          gameLock = false;  //reset the lock
          game1_counter = 0;
      }
  }
}

void game1_easy(){
    numOfBlocks = 3;
    int pattern = random(numOfBlocks);  //pick the right sequence of LEDS
    int* LEDS[3];
    int color[3] = {random(10,255),random(10,255),random(10,255)};
    switch (pattern){
        case HORIZONTAL:{
          int row = 3*random(3);
          for(int i=0;i<numOfBlocks;i++){
              LEDS[i] = Block_LED[row+i];
              game1Blocks[i] = row+i;
          }
        }
        break;
        case VERTICAL:{
          int col = random(3);
          for(int i=0;i<numOfBlocks;i++){
              LEDS[i] = Block_LED[col+i*3];
              game1Blocks[i] = col+i*3;
          }
        }
        break;
        case DIAGONAL:{
          int dig = random(2);
          if(dig == 0){
              for(int i=0;i<numOfBlocks;i++){
                  LEDS[i] = Block_LED[dig+i*4];
                  game1Blocks[i] = dig+i*4;
              }
          }
          else{
              for(int i=0;i<numOfBlocks;i++){
                  LEDS[i] = Block_LED[dig+1+i*2];
                  game1Blocks[i] = dig+1+i*2;
              }
          }
        }
        break;
    }
    for(int i=0;i<numOfBlocks;i++){
      //   for(int j=0;j<3;j++){
      //       digitalWrite(LEDS[i][j], HIGH);
      //   }
        SerialSend(game1Blocks[i],color[0],color[1],color[2]);
        delay(1000);
      //   for(int j=0;j<3;j++){
      //       digitalWrite(LEDS[i][j], LOW);
      //   }
        SerialSend(game1Blocks[i],0,0,0);
    }
}

void game1_medium(){
    numOfBlocks = random(4,6);
    int color[3] = {random(10,255),random(10,255),random(10,255)};
    sequenceGenerator();
    int temp;
    for(int i=0;i<numOfBlocks;i++){
        //Serial.println(String(game1Blocks[i]));
        temp = game1Blocks[i];
        SerialSend(temp,color[0],color[1],color[2]);
        delay(1000);
        SerialSend(temp,0,0,0);
    }
}

void game1_hard(){
    numOfBlocks = random(6,8);
    sequenceGenerator();
    int color[3] = {random(10,255),random(10,255),random(10,255)};
    for(int i=0;i<numOfBlocks;i++){
        SerialSend(game1Blocks[i],color[0],color[1],color[2]);
        delay(1000);
        SerialSend(game1Blocks[i],0,0,0);
    }
}

void sequenceGenerator(){
    //reset
    for(int i=0;i<NUM_LEDS;i++){
        game1Blocks[i] = i;
    }

    int temp,pos;
    for(int i=0;i<NUM_LEDS/2;i++){
        temp = game1Blocks[i];
        pos = random(NUM_LEDS);
        game1Blocks[i] = game1Blocks[pos];
        game1Blocks[pos] = temp;
    }
}
