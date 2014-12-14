//Zuordnung Zeit zu den Wörtern der Woerdclock
void timeToStrip(uint8_t hours,uint8_t minutes)
{
	pushES_IST();

	//show minutes
	if(minutes >= 5 && minutes < 10) {
		pushFUENF1();
		pushNACH();
	} else if(minutes >= 10 && minutes < 15) {
		pushZEHN1();
		pushNACH();
	} else if(minutes >= 15 && minutes < 20) {
		pushVIERTEL();
		pushNACH();
	} else if(minutes >= 20 && minutes < 25) {
		//if(selectedLanguageMode == RHEIN_RUHR_MODE) {
			pushZWANZIG();
			pushNACH();
		//} else if(selectedLanguageMode == WESSI_MODE) {
//			pushZEHN1();
//			pushVOR();
//			pushHALB();
		//}
	} else if(minutes >= 25 && minutes < 30) {
		pushFUENF1();
		pushVOR();
		pushHALB();
	} else if(minutes >= 30 && minutes < 35) {
		pushHALB();
	} else if(minutes >= 35 && minutes < 40) {
		pushFUENF1();
		pushNACH();
		pushHALB();
	} else if(minutes >= 40 && minutes < 45) {
		//if(selectedLanguageMode == RHEIN_RUHR_MODE) {
			pushZWANZIG();
			pushVOR();
		//} else if(selectedLanguageMode == WESSI_MODE) {
//			pushZEHN1();
//			pushNACH();
//			pushHALB();
//		}
	} else if(minutes >= 45 && minutes < 50) {
		pushVIERTEL();
		pushVOR();
	} else if(minutes >= 50 && minutes < 55) {
		pushZEHN1();
		pushVOR();
	} else if(minutes >= 55 && minutes < 60) {
		pushFUENF1();
		pushVOR();
	}
	
 //Errechnung der Minute
	int singleMinutes = minutes % 5;
	switch(singleMinutes) {
		case 1:
			pushONE();
			break;
		case 2:
			pushONE();
			pushTWO();
			break;
		case 3:
			pushONE();
			pushTWO();
			pushTHREE();
			break;
		case 4:
			pushONE();
			pushTWO();
			pushTHREE();
			pushFOUR();
		break;
	}

	if(hours >= 12) {
		hours -= 12;
	}

	//if(selectedLanguageMode == RHEIN_RUHR_MODE) {
		if(minutes >= 25) {
			hours++;
		}
//	} else if(selectedLanguageMode == WESSI_MODE) {
//		if(minutes >= 20) {
//			hours++;
//		}
//	}

	if(hours == 12) {
		hours = 0;
	}

//show hours , Anzeige der Stunden
	switch(hours) {
		case 0:
			pushZWOELF();
			break;
		case 1:
			if(minutes > 4) {
				pushEINS(true);
			} else {
				pushEINS(false);
			}
			break;
		case 2:
			pushZWEI();
			break;
		case 3:
			pushDREI();
			break;
		case 4:
			pushVIER();
			break;
		case 5:
			pushFUENF2();
			break;
		case 6:
			pushSECHS();
			break;
		case 7:
			pushSIEBEN();
			break;
		case 8:
			pushACHT();
			break;
		case 9:
			pushNEUN();
			break;
		case 10:
			pushZEHN();
			break;
		case 11:
			pushELF();
			break;
	}
	
	//show uhr
	if(minutes < 5) {
		pushUHR();
	}
}

///////////////////////
//PUSH WORD HELPER , Zuordnung der Wörter zu den LED´s
///////////////////////
void pushES_IST()  {
	pushToStrip(koordinate(0,0));
	pushToStrip(koordinate(1,0));
	pushToStrip(koordinate(3,0));
	pushToStrip(koordinate(4,0));
	pushToStrip(koordinate(5,0));
}

void pushFUENF1() {
	pushToStrip(koordinate(7,0));
	pushToStrip(koordinate(8,0));
	pushToStrip(koordinate(9,0));
	pushToStrip(koordinate(10,0));
}

void pushFUENF2() {
	pushToStrip(koordinate(7,6));
	pushToStrip(koordinate(8,6));
	pushToStrip(koordinate(9,6));
	pushToStrip(koordinate(10,6));
}

void pushNACH() {
	pushToStrip(koordinate(2,3));
	pushToStrip(koordinate(3,3));
	pushToStrip(koordinate(4,3));
	pushToStrip(koordinate(5,3));
}

void pushZEHN1() {
	pushToStrip(koordinate(0,1));
	pushToStrip(koordinate(1,1));
	pushToStrip(koordinate(2,1));
	pushToStrip(koordinate(3,1));
}

void pushVIERTEL() {
	pushToStrip(koordinate(4,2));
	pushToStrip(koordinate(5,2));
	pushToStrip(koordinate(6,2));
	pushToStrip(koordinate(7,2));
	pushToStrip(koordinate(8,2));
	pushToStrip(koordinate(9,2));
	pushToStrip(koordinate(10,2));
}

void pushVOR() {
	pushToStrip(koordinate(6,3));
	pushToStrip(koordinate(7,3));
	pushToStrip(koordinate(8,3));
}

void pushHALB() {
	pushToStrip(koordinate(0,4));
	pushToStrip(koordinate(1,4));
	pushToStrip(koordinate(2,4));
	pushToStrip(koordinate(3,4));
}

void pushONE() {
	pushToStrip(3);
}

void pushTWO() {
	pushToStrip(2);
}

void pushTHREE() {
	pushToStrip(1);
}

void pushFOUR() {
	pushToStrip(0);
}

void pushZWANZIG() {
	pushToStrip(koordinate(4,1));
	pushToStrip(koordinate(5,1));
	pushToStrip(koordinate(6,1));
	pushToStrip(koordinate(7,1));
	pushToStrip(koordinate(8,1));
	pushToStrip(koordinate(9,1));
	pushToStrip(koordinate(10,1));
}

void pushZWOELF() {
	pushToStrip(koordinate(5,4));
	pushToStrip(koordinate(6,4));
	pushToStrip(koordinate(7,4));
	pushToStrip(koordinate(8,4));
	pushToStrip(koordinate(9,4));
}

void pushEINS(bool s) 
{
	pushToStrip(koordinate(2,5));
	pushToStrip(koordinate(3,5));
	pushToStrip(koordinate(4,5));
	if(s) {
		pushToStrip(koordinate(5,5));
	}
}

void pushZWEI() {
	pushToStrip(koordinate(0,5));
	pushToStrip(koordinate(1,5));
	pushToStrip(koordinate(2,5));
	pushToStrip(koordinate(3,5));
}

void pushDREI() {
	pushToStrip(koordinate(1,6));
	pushToStrip(koordinate(2,6));
	pushToStrip(koordinate(3,6));
	pushToStrip(koordinate(4,6));
}

void pushVIER() {
	pushToStrip(koordinate(7,7));
	pushToStrip(koordinate(8,7));
	pushToStrip(koordinate(9,7));
	pushToStrip(koordinate(10,7));
}

void pushSECHS() {
	pushToStrip(koordinate(1,9));
	pushToStrip(koordinate(2,9));
	pushToStrip(koordinate(3,9));
	pushToStrip(koordinate(4,9));
	pushToStrip(koordinate(5,9));
}

void pushSIEBEN() {
	pushToStrip(koordinate(5,5));
	pushToStrip(koordinate(6,5));
	pushToStrip(koordinate(7,5));
	pushToStrip(koordinate(8,5));
	pushToStrip(koordinate(9,5));
	pushToStrip(koordinate(10,5));
}

void pushACHT() {
	pushToStrip(koordinate(1,8));
	pushToStrip(koordinate(2,8));
	pushToStrip(koordinate(3,8));
	pushToStrip(koordinate(4,8));
}

void pushNEUN() {
	pushToStrip(koordinate(3,7));
	pushToStrip(koordinate(4,7));
	pushToStrip(koordinate(5,7));
	pushToStrip(koordinate(6,7));
}

void pushZEHN() {
	pushToStrip(koordinate(5,8));
	pushToStrip(koordinate(6,8));
	pushToStrip(koordinate(7,8));
	pushToStrip(koordinate(8,8));
}

void pushELF() {
	pushToStrip(koordinate(0,7));
	pushToStrip(koordinate(1,7));
	pushToStrip(koordinate(2,7));
}

void pushUHR() {
	pushToStrip(koordinate(8,9));
	pushToStrip(koordinate(9,9));
	pushToStrip(koordinate(10,9));
}
