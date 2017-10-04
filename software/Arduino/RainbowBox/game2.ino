// void game2(){
//     if(gameLock == false){
//         game2_counter = 0;
//         gameLock = true;
//         switch(game2_current_mode){
//             case EASY:
//             game2_easy();
//             break;
//             case MEDIUM:
//             game2_medium();
//             break;
//             case HARD:
//             game2_hard();
//             break;
//         }
//         //clean the buffer
//         flush();
//         //start timing
//         game2_iniTime = millis();
//     }
//
//     if(gameLock == true){
//         game2_currentTime = millis();
//         if (game1_currentTime-game1_iniTime < ONE_MIN){
//             if(Serial.available()>0){
//                 SerialRead(command,bytesReceive);
//                 if(command[0] == 'b')
//             }
//         }
//     }
// }
//
// void game2_easy(){
//     numOfBlocks = random(3,5);
//     numOfColor = 1;
//     sequenceGenerator();
//     for(int i=0;i<numOfBlocks;i++){
//         SerialSend(gameBlocks[i],game2Color[0][0],game2Color[0][1],game2Color[0][2]);
//     }
//     delay(1000);
//     for(int i=0;i<numOfBlocks;i++){
//         SerialSend(gameBlocks[i],0,0,0);
//     }
// }
//
//
// void colorGenerator(){
//     for(int i=0; i<MAX_NUM_COLOR; i++){
//         for(int j=0;i<3;j++){
//             game2Color[i][j] = random(50,256);
//         }
//     }
// }
