void funLight1(){
  for (int i=0;i<9;i++){
    blockNo = i;
    int state=random(0, 100);
    float x=state/100.0;
    if (x<0.1){
      r=0;
      g=0;
      b=0;
      SerialCom();
//      for (int j=0;j<3;j++){
//        digitalWrite(Block_LED[i][j],LOW);
//      }
    } else {
      r=random(0, 255);
      g=random(0, 255);
      b=random(0, 255);
//      analogWrite(Block_LED[i][0],r);
//      analogWrite(Block_LED[i][1],g);
//      analogWrite(Block_LED[i][2],b);
      SerialCom();
    }
  }
}
