String rr;
String gg;
String bb;
String colour[3]={rr,gg,bb};


void SerialCom() {
  // convert int r,g,b into a string of 3 characters
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
  
  // Serial communication
  Serial.print('s');
  Serial.print((String)blockNo);
  Serial.print(colour[0]);
  Serial.print(colour[1]);
  Serial.print(colour[2]);
  Serial.println('e');
}

