/*
  0 1 2 3 4 5 6 7 8 9 10 x
 0 E S K I S T A F Ü N F
 1 Z E H N Z W A N Z I G
 2 D R E I V I E R T E L
 3 V O R F Ü N F N A C H
 4 H A L B A E L F Ü N F
 5 E I N S X A M Z W E I
 6 D R E I Ä U J V I E R
 7 S E C H S N L A C H T
 8 S I E B E N Z W Ö L F
 9 Z E H N E U N K U H R
 y
 */

byte koordinate(byte x, byte y) {
  byte m = x; //Multiplikator
  byte a = y; //Addierer
  byte led = 0; // LED in der Matrix
  //Gerade Ungerade x koordinate?
  if ((m + 1) % 2 == 0){
    led = (a + 4) + 100 - (m * 10);
  }
  else{
    led = (13 - a) + 100 - (m * 10);
  }
  return led;
}

