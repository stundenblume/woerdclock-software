//void writeChar(char val){
//  int writeLED = 0;
//  //DEBUG_PRINT("writeChar");
//  //DEBUG_PRINT(val);
//  waitUntilwriteChar = millis();
//  
//  for(int i=9; i>=0; i--){ 
//      //DEBUG_PRINT("for");  
//      if(millis() >= waitUntilwriteChar) {
//        //DEBUG_PRINT("if");
//          waitUntilwriteChar = millis();
//          resetAndBlack();
//            for(int j=0;j<9;j++){
//               for(int k=9-i;k>=0;k--){
//                        switch (val){
//                            case 'A':
//                              writeLED = arrayA[k][j];
//                              break;
//                            case 'B':
//                              writeLED = arrayB[k][j];
//                              break;
//                            case 'C':
//                              writeLED = arrayC[k][j];
//                              break;
//                            case 'D':
//                              writeLED = arrayD[k][j];
//                              break;
//                            case 'E':
//                              writeLED = arrayE[k][j];
//                              break;
////                            case 'F':
////                              writeLED = arrayF[k][j];
////                              break;
////                            case 'G':
////                              writeLED = arrayG[k][j];
////                              break;
//                            case 'H':
//                              writeLED = arrayH[k][j];
//                              break;
//                            case 'I':
//                              writeLED = arrayI[k][j];
//                              break;
////                            case 'J':
////                              writeLED = arrayJ[k][j];
////                              break;
////                            case 'K':
////                              writeLED = arrayK[k][j];
////                              break;
//                            case 'L':
//                              writeLED = arrayL[k][j];
//                              break;
////                            case 'M':
////                              writeLED = arrayM[k][j];
////                              break;
//                            case 'N':
//                              writeLED = arrayN[k][j];
//                              break;
//                            case 'O':
//                              writeLED = arrayO[k][j];
//                              break;
////                            case 'P':
////                              writeLED = arrayP[k][j];
////                              break;
////                            case 'Q':
////                              writeLED = arrayQ[k][j];
////                              break;
//                            case 'R':
//                              writeLED = arrayR[k][j];
//                              break;
////                            case 'S':
////                              writeLED = arrayS[k][j];
////                              break;
//                            case 'T':
//                              writeLED = arrayT[k][j];
//                              break;
//                            case 'U':
//                              writeLED = arrayU[k][j];
//                              break;
////                            case 'V':
////                              writeLED = arrayV[k][j];
////                              break;
////                            case 'W':
////                              writeLED = arrayW[k][j];
////                              break;
////                            case 'X':
////                              writeLED = arrayX[k][j];
////                              break;
////                            case 'Y':
////                              writeLED = arrayY[k][j];
////                              break;
////                            case 'Z':
////                              writeLED = arrayZ[k][j];
////                              break;
//                            case ' ':         
//                              break;
//                            case '1':
//                              writeLED = array1[k][j];
//                              break;
//                            case '2':
//                              writeLED = array2[k][j];
//                              break;
//                            case '3':
//                              writeLED = array3[k][j];
//                              break;
//                            case '4':
//                              writeLED = array4[k][j];
//                              break;
//                            case '5':
//                              writeLED = array5[k][j];
//                              break;
//                            case '6':
//                              writeLED = array6[k][j];
//                              break;
//                            case '7':
//                              writeLED = array7[k][j];
//                              break;
//                            case '8':
//                              writeLED = array8[k][j];
//                              break;
//                            case '9':
//                              writeLED = array9[k][j];
//                              break;
//                            case '0':
//                              writeLED = array0[k][j];
//                              break;     
//                            default:
//                              pushToStrip(0);
//                              pushToStrip(1);
//                              pushToStrip(2);
//                              pushToStrip(3);
//                          }
//                       if (writeLED == 1){
//                         pushToStrip(koordinate(k+1+i,j));
//                       }
//                 }
//            }   
//          displayStrip(CRGB::Red);
//        }
//        waitUntilwriteChar += oneSecondDelay;
//        while(millis() < waitUntilwriteChar){
//           //DEBUG_PRINT("while");
//          //delay(10);
//        }
//    }    
//}
//
//

