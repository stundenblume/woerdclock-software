//this function will display binary in column x, start in row 9

void showINT(int x,int val){

  if (val<0) return;
    //resetAndBlack();    
  
  for (int i=0;i<10;i++){
    pushToStrip(koordinate(x,bitRead(val,9-i)));
  }
}
