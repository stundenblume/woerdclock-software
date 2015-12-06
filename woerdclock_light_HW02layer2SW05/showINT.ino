//this function will display binary in column x, start in row 9

void showINT(int x,int val){    
  for (int i=0;i<10;i++){
    if(bitRead(val,9-i)==1){
      pushToStrip(koordinate(x,i));
    }
  }
}
