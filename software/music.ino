int speakerPin = 9;

//Hark the Herald
int length1 = 77;
char notes1[] = "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ";
int beats1[] = {2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8};

//God Rest Ye Merry Gentlemen
int length2 = 69;
char notes2[] = "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed";
int beats2[] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 };

int tempo = 150;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
  int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 12; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {

  sing(1);
  sing(2);
  exit(0); 
 
}

int song=1;
 
void sing(int s) {
  song = s;
  if (song == 1) {
    for (int i = 0; i < length1; i++) {
      if (notes1[i] == ' ') {
        delay(beats1[i] * tempo); // rest
      } else {
        playNote(notes1[i], beats1[i] * tempo);
      }
  
      // pause between notes
      delay(tempo / 2); 
    }
  
 } else {
   for (int i = 0; i < length2; i++) {
    if (notes2[i] == ' ') {
      delay(beats2[i] * tempo); // rest
    } else {
      playNote(notes2[i], beats2[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
 }
}
