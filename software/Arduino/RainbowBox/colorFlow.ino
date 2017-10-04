float saturation,lightness;
int spetrum[360][3];
//The larger the space, the easier to distinguish the color in adjacent rows
int space = 20;

void colorFlow(){
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
    
    //turn on the LEDs
    int temp = 360/space-2;
    for(int i=0;i<temp;i++){
        SerialSend(6,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(7,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);
        SerialSend(8,spetrum[space*i][0],spetrum[space*i][1],spetrum[space*i][2]);

        SerialSend(3,spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(4,spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);
        SerialSend(5,spetrum[space+space*i][0],spetrum[space+space*i][1],spetrum[space+space*i][2]);

        SerialSend(0,spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(1,spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        SerialSend(2,spetrum[(2*space-1)+space*i][0],spetrum[(2*space-1)+space*i][1],spetrum[(2*space-1)+space*i][i]);
        delay(50);
    }

}
