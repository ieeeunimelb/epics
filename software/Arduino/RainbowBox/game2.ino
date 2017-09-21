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
//     if(gameLock == true){
//         game2_currentTime = millis();
//         if (game1_currentTime-game1_iniTime < ONE_MIN){
//             if(Serial.available()>0){
//                 SerialRead(command,bytesReceive);
//             }
//         }
//     }
// }
