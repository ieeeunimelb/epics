void SerialSend(int blockNo,int r,int g,int b) {
  // convert int r,g,b into a string of 3 characters
  String colour[3];
  int col[3]={r,g,b};
  for (int i=0;i<3;i++){
    if (col[i]>=0 && col[i]<=9){
      colour[i]="00"+ (String)col[i];
    }else if(col[i]>=10 && col[i]<=99){
      colour[i]="0"+ (String)col[i];
    }else if(col[i]>=100){
      colour[i]= (String)col[i];
    }
  }

  Serial.print('s'+(String)blockNo+colour[0]+colour[1]+colour[2]+'e'+'\n');
}

//this function should come up with an external statement to check whether the
// seriable is available
void SerialRead(char* command, int bytes){
    Serial.readBytes(command,bytes);
    //if the command is from the rotary switch and due to the setting in the GUI.py file
    //it would only receive message when some states changed
    if(command[0] == 'r' ){  //'r' stands for rotary switch
        //r1_2_3_e
        //check if the first rotary switch is changed
        if((command[2]+'\0') != 48 ){
            switch (command[2]){
                case 'E':
                game1_current_mode = EASY;
                break;
                case 'M':
                game1_current_mode = MEDIUM;
                break;
                case 'H':
                game1_current_mode = HARD;
                break;
            }
            if(game1_current_mode != game1_prev_mode){
                gameLock = false;
                game1_counter = 0;
                game1_prev_mode = game1_current_mode;
            }
        }
    }else if(command[0] == 'b' && command[1] == 'r'){
        while(Serial.available() > 0) {
            char* temp = Serial.read();
        }
        gameLock = false;
        game1_counter = 0;
    }
}

void flush(){
    while(Serial.available() > 0) {
        SerialRead(command,bytesReceive);
        for(int i=0;i<bytesReceive;i++){
            command[i] = 'e';
        }
        delay(200);
    }
}
