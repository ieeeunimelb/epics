<<<<<<< HEAD

float saturation,lightness;
int spetrum[360][3];
//The larger the space, the easier to distinguish the color in adjacent rows
int space = 20;

int tlDiagonal[] =  {0, 1, 3, 2, 4, 6, 5, 7, 8}; //top left diagonal flow
int trDiagonal[] = {2, 1, 5, 0, 4, 8, 3, 7, 6}; //top right diagonal flow
int brDiagonal[] = {8, 7, 5, 2, 4, 6, 3, 1, 0}; //bottom left diagonal flow
int blDiagonal[] = {6, 7, 3, 0, 4, 8, 5, 1, 0}; //bottom left diagonal flow
int tbLinear[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};  //top bottom horizontal flow
int btLinear[] = {8, 7, 6, 5, 4, 3, 2, 1, 0}; //bottom top horizontal flow
int lrLinear[] = {0, 3, 6, 1, 4, 7, 2, 5, 8}; //left right vertical flow
int rlLinear[] = {2, 5, 8, 1, 4, 7, 0, 3, 6}; // right left vertical flow

int diagonal[][] = {tlDiagonal, trDiagonal, brDiagonal, blDiagonal};
int linear[][] = {tbLinear, btLinear, lrLinear, rlLinear};

void ColorFlow2(){
    //randomly select flow setting
    randPinSequence = rand(0, 12);

    //generate the saturation and lightness
    saturation = random(50,100)/100.0; //below 0.5 will be ver dark
    lightness = random(50,81)/100.0;   //below 0.5 will be ver dark, and above
                                       //0.8 will be close to white

    //then move the hue from 0 to 359 and compute the corresponding
    // R,G,B values
    float C,X,m,R_prime,G_prime,B_prime;
    for(int hue =0;hue<360;hue++){
        C = (1-fabs(2*lightness-1))*saturation;
        X = C*(1-fabs(fmod(hue/60.0,2)-1));
        m = lightness-C/2;
        if(hue<60){
            R_prime = C;
            G_prime = X;
            B_prime = 0;
        }else if(hue<120){
            R_prime = X;
            G_prime = C;
            B_prime = 0;
        }else if(hue<180){
            R_prime = 0;
            G_prime = C;
            B_prime = X;
        }else if(hue<240){
            R_prime = 0;
            G_prime = X;
            B_prime = C;
        }else if(hue<300){
            R_prime = X;
            G_prime = 0;
            B_prime = C;
        }else if(hue<360){
            R_prime = C;
            G_prime = 0;
            B_prime = X;
        }
        spetrum[hue][0] = (R_prime+m)*255;
        spetrum[hue][1] = (G_prime+m)*255;
        spetrum[hue][2] = (B_prime+m)*255;
    }



  if(randPinSequence<3){
      for(int i=0; i<3; i++){
        solidFlow();
      }

  } else if(3<=randPinSequence && randPinSequence<8){

    for(int i=0; i<3; i++){
        diagonalFlow(randPinSequence);
    }

  }else if (randPinSequence<12){
    for(int i=0; i<3; i++){
        linearFlow(randPinSequence);
    }


  }


}

void solidFlow(){
    //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
      for(int i=1; i<=9; i++){

        SerialSend(i,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        }
      delay(50);
    }

    for(int i=temp-1;i>=0;i--){
      for(int i=1; i<=9; i++){

        SerialSend(i,spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);

        }
      delay(50);
    }
}

void linearFlow(int randPinSequence){

  int linearSeq[] = linear[randPinSequence%4];

  //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
        SerialSend(linearSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[1],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[2],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        SerialSend(linearSeq[3],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[4],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[5],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);

        SerialSend(linearSeq[6],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[7],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[8],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        delay(50);
    }

    for(int i=temp-1; i>=0; i--){
        SerialSend(linearSeq[0],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[1],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[2],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);

        SerialSend(linearSeq[3],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[4],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[5],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);

        SerialSend(linearSeq[6],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[7],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[8],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        delay(50);
    }
}


void diagonalFlow(int randPinSequence){
    //randomly assign colour change pattern
  int diagonalSeq[] = diagonal[randpinSequence%4];

  //turn on the LEDs
  int temp = 360/space-2;
  for(int i=0;i<temp;i++){
      SerialSend(diagonalSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);
      SerialSend(diagonalSeq[2],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);

      SerialSend(diagonalSeq[3],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[4],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[5],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);

      SerialSend(diagonalSeq[6],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      SerialSend(diagonalSeq[7],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);

      SerialSend(diagonalSeq[8],spetrum[(4*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      delay(50);
    }

    for(int i=temp-1; i>=0; i--){
      SerialSend(diagonalSeq[0],spetrum[temp-space*i][0],spetrum[temp-space*i][1],spetrum[temp-space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);
      SerialSend(diagonalSeq[2],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);

      SerialSend(diagonalSeq[3],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[4],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[5],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);

      SerialSend(diagonalSeq[6],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      SerialSend(diagonalSeq[7],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);

      SerialSend(diagonalSeq[8],spetrum[temp-((4*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      delay(50);

    }
  }
=======
float saturation,lightness;
int spetrum[360][3];
//The larger the space, the easier to distinguish the color in adjacent rows
int space = 20;

int tlDiagonal[] =  {0, 1, 3, 2, 4, 6, 5, 7, 8}; //top left diagonal flow
int trDiagonal[] = {2, 1, 5, 0, 4, 8, 3, 7, 6}; //top right diagonal flow
int brDiagonal[] = {8, 7, 5, 2, 4, 6, 3, 1, 0}; //bottom left diagonal flow
int blDiagonal[] = {6, 7, 3, 0, 4, 8, 5, 1, 0}; //bottom left diagonal flow
int tbLinear[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};  //top bottom horizontal flow
int btLinear[] = {8, 7, 6, 5, 4, 3, 2, 1, 0}; //bottom top horizontal flow
int lrLinear[] = {0, 3, 6, 1, 4, 7, 2, 5, 8}; //left right vertical flow
int rlLinear[] = {2, 5, 8, 1, 4, 7, 0, 3, 6}; // right left vertical flow

int diagonal[][] = {tlDiagonal, trDiagonal, brDiagonal, blDiagonal};
int linear[][] = {tbLinear, btLinear, lrLinear, rlLinear};

void ColorFlow(){
    //randomly select flow setting
    randPinSequence = rand(0, 12);

    //generate the saturation and lightness
    saturation = random(50,100)/100.0; //below 0.5 will be ver dark
    lightness = random(50,81)/100.0;   //below 0.5 will be ver dark, and above
                                       //0.8 will be close to white

    //then move the hue from 0 to 359 and compute the corresponding
    // R,G,B values
    float C,X,m,R_prime,G_prime,B_prime;
    for(int hue =0;hue<360;hue++){
        C = (1-fabs(2*lightness-1))*saturation;
        X = C*(1-fabs(fmod(hue/60.0,2)-1));
        m = lightness-C/2;
        if(hue<60){
            R_prime = C;
            G_prime = X;
            B_prime = 0;
        }else if(hue<120){
            R_prime = X;
            G_prime = C;
            B_prime = 0;
        }else if(hue<180){
            R_prime = 0;
            G_prime = C;
            B_prime = X;
        }else if(hue<240){
            R_prime = 0;
            G_prime = X;
            B_prime = C;
        }else if(hue<300){
            R_prime = X;
            G_prime = 0;
            B_prime = C;
        }else if(hue<360){
            R_prime = C;
            G_prime = 0;
            B_prime = X;
        }
        spetrum[hue][0] = (R_prime+m)*255;
        spetrum[hue][1] = (G_prime+m)*255;
        spetrum[hue][2] = (B_prime+m)*255;
    }



  if(randPinSequence<3){
      for(int i=0; i<3; i++){
        solidFlow();
      }

  } else if(3<=randPinSequence && randPinSequence<8){

    for(int i=0; i<3; i++){
        diagonalFlow(randPinSequence);
    }

  }else if (randPinSequence<12){
    for(int i=0; i<3; i++){
        linearFlow(randPinSequence);
    }


  }


}

void solidFlow(){
    //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
      for(int i=1; i<=9; i++){

        SerialSend(i,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        }
      delay(50);
    }

    for(int i=temp-1;i>=0;i--){
      for(int i=1; i<=9; i++){

        SerialSend(i,spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);

        }
      delay(50);
    }
}

void linearFlow(int randPinSequence){

  int linearSeq[] = linear[randPinSequence%4];

  //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
        SerialSend(linearSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[1],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[2],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        SerialSend(linearSeq[3],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[4],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[5],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);

        SerialSend(linearSeq[6],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[7],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[8],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        delay(50);
    }

    for(int i=temp-1; i>=0; i--){
        SerialSend(linearSeq[0],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[1],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[2],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);

        SerialSend(linearSeq[3],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[4],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[5],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);

        SerialSend(linearSeq[6],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[7],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[8],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        delay(50);
    }
}


void diagonalFlow(int randPinSequence){
    //randomly assign colour change pattern
  int diagonalSeq[] = diagonal[randPinSequence%4];

  //turn on the LEDs
  int temp = 360/space-2;
  for(int i=0;i<temp;i++){
      SerialSend(diagonalSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);
      SerialSend(diagonalSeq[2],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);

      SerialSend(diagonalSeq[3],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[4],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[5],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);

      SerialSend(diagonalSeq[6],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      SerialSend(diagonalSeq[7],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);

      SerialSend(diagonalSeq[8],spetrum[(4*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      delay(50);
    }

    for(int i=temp-1; i>=0; i--){
      SerialSend(diagonalSeq[0],spetrum[temp-space*i][0],spetrum[temp-space*i][1],spetrum[temp-space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);
      SerialSend(diagonalSeq[2],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);

      SerialSend(diagonalSeq[3],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[4],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[5],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);

      SerialSend(diagonalSeq[6],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      SerialSend(diagonalSeq[7],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);

      SerialSend(diagonalSeq[8],spetrum[temp-((4*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      delay(50);

    }
  }
>>>>>>> origin/master
=======
float saturation,lightness;
int spetrum[360][3];
//The larger the space, the easier to distinguish the color in adjacent rows
int space = 20;

int tlDiagonal[] =  {0, 1, 3, 2, 4, 6, 5, 7, 8}; //top left diagonal flow
int trDiagonal[] = {2, 1, 5, 0, 4, 8, 3, 7, 6}; //top right diagonal flow
int brDiagonal[] = {8, 7, 5, 2, 4, 6, 3, 1, 0}; //bottom left diagonal flow
int blDiagonal[] = {6, 7, 3, 0, 4, 8, 5, 1, 0}; //bottom left diagonal flow
int tbLinear[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};  //top bottom horizontal flow
int btLinear[] = {8, 7, 6, 5, 4, 3, 2, 1, 0}; //bottom top horizontal flow
int lrLinear[] = {0, 3, 6, 1, 4, 7, 2, 5, 8}; //left right vertical flow 
int rlLinear[] = {2, 5, 8, 1, 4, 7, 0, 3, 6}; // right left vertical flow 

int diagonal[][] = {tlDiagonal, trDiagonal, brDiagonal, blDiagonal};
int linear[][] = {tbLinear, btLinear, lrLinear, rlLinear};

void ColorFlow(){
    //randomly select flow setting 
    randPinSequence = rand(0, 12);

    //generate the saturation and lightness
    saturation = random(50,100)/100.0; //below 0.5 will be ver dark
    lightness = random(50,81)/100.0;   //below 0.5 will be ver dark, and above
                                       //0.8 will be close to white

    //then move the hue from 0 to 359 and compute the corresponding
    // R,G,B values
    float C,X,m,R_prime,G_prime,B_prime;
    for(int hue =0;hue<360;hue++){
        C = (1-fabs(2*lightness-1))*saturation;
        X = C*(1-fabs(fmod(hue/60.0,2)-1));
        m = lightness-C/2;
        if(hue<60){
            R_prime = C;
            G_prime = X;
            B_prime = 0;
        }else if(hue<120){
            R_prime = X;
            G_prime = C;
            B_prime = 0;
        }else if(hue<180){
            R_prime = 0;
            G_prime = C;
            B_prime = X;
        }else if(hue<240){
            R_prime = 0;
            G_prime = X;
            B_prime = C;
        }else if(hue<300){
            R_prime = X;
            G_prime = 0;
            B_prime = C;
        }else if(hue<360){
            R_prime = C;
            G_prime = 0;
            B_prime = X;
        }
        spetrum[hue][0] = (R_prime+m)*255;
        spetrum[hue][1] = (G_prime+m)*255;
        spetrum[hue][2] = (B_prime+m)*255;
    }



  if(randPinSequence<3){
      for(int i=0; i<3; i++){
        solidFlow();
      }
      
  } else if(3<=randPinSequence && randPinSequence<8){
    
    for(int i=0; i<3; i++){
        diagonalFlow(randPinSequence);
    }  
    
  }else if (randPinSequence<12){
    for(int i=0; i<3; i++){
        linearFlow(randPinSequence);
    } 
    
  
  }
    

}

void solidFlow(){
    //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
      for(int i=1; i<=9; i++){
        
        SerialSend(i,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
                
        }
      delay(50);
    }

    for(int i=temp-1;i>=0;i--){
      for(int i=1; i<=9; i++){
        
        SerialSend(i,spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
                
        }
      delay(50);
    }
}

void linearFlow(int randPinSequence){

  int* linearSeq = linear[randPinSequence%4];

  //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
        SerialSend(linearSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[1],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(linearSeq[2],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        SerialSend(linearSeq[3],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[4],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(linearSeq[5],spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);

        SerialSend(linearSeq[6],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[7],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(linearSeq[8],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        delay(50);
    }

    for(int i=temp-1; i>=0; i--){
        SerialSend(linearSeq[0],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[1],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);
        SerialSend(linearSeq[2],spetrum[temp-(space*i)][0],spetrum[temp-(space*i)][1],spetrum[temp-(space*i)][2]);

        SerialSend(linearSeq[3],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[4],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);
        SerialSend(linearSeq[5],spetrum[temp-(space+space*i)][0],spetrum[temp-(space+space*i)][1],spetrum[temp-(space+space*i)][2]);

        SerialSend(linearSeq[6],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[7],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        SerialSend(linearSeq[8],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-(2*space-1)+space*i][1],spetrum[temp-((2*space-1)+space*i)][i]);
        delay(50);
    }
}


void diagonalFlow(int randPinSequence){
    //randomly assign colour change pattern 
  int* diagonalSeq = diagonal[randPinSequence%4];

  //turn on the LEDs
  int temp = 360/space-2;
  for(int i=0;i<temp;i++){
      SerialSend(diagonalSeq[0],spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);
      SerialSend(diagonalSeq[2],spetrum[space + space*i][0],spetrum[space + space*i][1],spetrum[space + space*i][2]);

      SerialSend(diagonalSeq[3],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[4],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);
      SerialSend(diagonalSeq[5],spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][2]);

      SerialSend(diagonalSeq[6],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      SerialSend(diagonalSeq[7],spetrum[(3*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      
      SerialSend(diagonalSeq[8],spetrum[(4*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
      delay(50);
    }

    for(int i=temp-1; i>=0; i--){
      SerialSend(diagonalSeq[0],spetrum[temp-space*i][0],spetrum[temp-space*i][1],spetrum[temp-space*i][2]);

      SerialSend(diagonalSeq[1],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);
      SerialSend(diagonalSeq[2],spetrum[temp-(space + space*i)][0],spetrum[temp-(space + space*i)][1],spetrum[temp-(space + space*i)][2]);

      SerialSend(diagonalSeq[3],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[4],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);
      SerialSend(diagonalSeq[5],spetrum[temp-((2*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][2]);

      SerialSend(diagonalSeq[6],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      SerialSend(diagonalSeq[7],spetrum[temp-((3*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      
      SerialSend(diagonalSeq[8],spetrum[temp-((4*space-1)+space*i)][0],spetrum[temp-((2*space-1)+space*i)][1],spetrum[temp-((2*space-1)+space*i)][i]);
      delay(50);

    }
  }
>>>>>>> origin/master
