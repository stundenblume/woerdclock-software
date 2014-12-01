void writeChar(char val){
  int writeLED = 0;
  int l = 10;                                     //erste Spalte schreiben
  //DEBUG_PRINT("writeChar");
  //DEBUG_PRINT(val);
  
  for(int k=0;k<10;k++){                          //verschieben des Buchstaben in den Zeilen
 
            resetAndBlack();
            for(int i=0;i<6;i++){                        //Zeile Buchstabe
               for(int j=0;j<10;j++){                     //Spalte Buchstabe
                        switch (val){
                            case 'A':
                              writeLED = arrayA[i][j];
                              break;
                            case 'B':
                              writeLED = arrayB[i][j];
                              break;
                            case 'C':
                              writeLED = arrayC[i][j];
                              break;
                            case 'D':
                              writeLED = arrayD[k][j];
                              break;
                            case 'E':
                              writeLED = arrayE[i][j];
                              break;
//                            case 'F':
//                              writeLED = arrayF[i][j];
//                              break;
//                            case 'G':
//                              writeLED = arrayG[i][j];
//                              break;
                            case 'H':
                              writeLED = arrayH[i][j];
                              break;
                            case 'I':
                              writeLED = arrayI[i][j];
                              break;
//                            case 'J':
//                              writeLED = arrayJ[i][j];
//                              break;
//                            case 'K':
//                              writeLED = arrayK[i][j];
//                              break;
                            case 'L':
                              writeLED = arrayL[i][j];
                              break;
//                            case 'M':
//                              writeLED = arrayM[i][j];
//                              break;
                            case 'N':
                              writeLED = arrayN[i][j];
                              break;
                            case 'O':
                              writeLED = arrayO[i][j];
                              break;
//                            case 'P':
//                              writeLED = arrayP[i][j];
//                              break;
//                            case 'Q':
//                              writeLED = arrayQ[i][j];
//                              break;
                            case 'R':
                              writeLED = arrayR[i][j];
                              break;
//                            case 'S':
//                              writeLED = arrayS[i][j];
//                              break;
                            case 'T':
                              writeLED = arrayT[i][j];
                              break;
                            case 'U':
                              writeLED = arrayU[i][j];
                              break;
//                            case 'V':
//                              writeLED = arrayV[i][j];
//                              break;
//                            case 'W':
//                              writeLED = arrayW[i][j];
//                              break;
//                            case 'X':
//                              writeLED = arrayX[i][j];
//                              break;
//                            case 'Y':
//                              writeLED = arrayY[i][j];
//                              break;
//                            case 'Z':
//                              writeLED = arrayZ[i][j];
//                              break;
                            case ' ':         
                              break;
                            case '1':
                              writeLED = array1[i][j];
                              break;
                            case '2':
                              writeLED = array2[i][j];
                              break;
                            case '3':
                              writeLED = array3[i][j];
                              break;
                            case '4':
                              writeLED = array4[i][j];
                              break;
                            case '5':
                              writeLED = array5[i][j];
                              break;
                            case '6':
                              writeLED = array6[i][j];
                              break;
                            case '7':
                              writeLED = array7[i][j];
                              break;
                            case '8':
                              writeLED = array8[i][j];
                              break;
                            case '9':
                              writeLED = array9[i][j];
                              break;
                            case '0':
                              writeLED = array0[i][j];
                              break;     
                            default:
                              pushToStrip(0);
                              pushToStrip(1);
                              pushToStrip(2);
                              pushToStrip(3);
                          }
                       if (writeLED == 1){
                         pushToStrip(koordinate(l,j));
                       }
                 }
                 if (k == i){                  //letzte Spalte?
                  i=6;
                 }
            }   
          displayStrip(CRGB::Red);
          delay(1000);                                  //verzögerung für die Verschiebung
          l--;                                 //Spalte in der Matrix nach links
    }
    
}



