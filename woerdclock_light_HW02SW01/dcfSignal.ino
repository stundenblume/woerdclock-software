#if DCFMODUL

//void digitalClockDisplay(){
//  // digital clock display of the time
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.print(" ");
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year()); 
//  Serial.println(); 
//}

//void printDigits(int digits){
//  // utility function for digital clock display: prints preceding colon and leading 0
//  Serial.print(":");
//  if(digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//}

void initializeDCF(void) 
{	
	leadingEdge           = 0;
	trailingEdge          = 0;
	PreviousLeadingEdge   = 0;
	Up                    = false;
	runningBuffer		  = 0;
	FilledBufferAvailable = false;
	bufferPosition        = 0;
	flags.parityDate      = 0;
	flags.parityFlag      = 0;
	flags.parityHour      = 0;
	flags.parityMin       = 0;
	CEST		      = 0;
}

void StartDCF(void) 
{
		EICRB |= (1<<ISC60)|(0<<ISC61); // sets the interrupt type for EICRB (INT6).
                //EICRA |= (0<<ISC21)|(1<<ISC20);
		EIMSK |= (1<<INT6); // activates the interrupt. 6 for 6
	        //EIMSK |= (1<<INT2);
}

inline void bufferinit(void) 
{
	runningBuffer    = 0;
	bufferPosition   = 0;
}

ISR(INT6_vect) {
  
  //test = 1;	
  
        int flankTime = millis();
	volatile byte sensorValue = digitalRead(DCF_PIN);
	//byte sensorValue = sensorValue2 ^ 1;

	// If flank is detected quickly after previous flank up
	// this will be an incorrect pulse that we shall reject
	if ((flankTime-PreviousLeadingEdge)<DCFRejectionTime) {
		//LogLn("rCT");
                //test = 2;
		return;
	}
	
	// If the detected pulse is too short it will be an
	// incorrect pulse that we shall reject as well
	if ((flankTime-leadingEdge)<DCFRejectPulseWidth) {
	    //LogLn("rPW");
                //test = 3;
		return;
	}
	
	if(sensorValue==pulseStart) {
		if (!Up) {
			// Flank up
			leadingEdge=flankTime;
                        //test = 4;
			Up = true;		                
		} 
	} else {
		if (Up) {
			// Flank down
			trailingEdge=flankTime;
			int difference=trailingEdge - leadingEdge;            
          		
			if ((leadingEdge-PreviousLeadingEdge) > DCFSyncTime) {
				finalizeBuffer();
                                //test = 5;
			}         
			PreviousLeadingEdge = leadingEdge;       
			// Distinguish between long and short pulses
			if (difference < DCFSplitTime) { 
                        appendSignal(0);
                        //test = 6;
                        } 
                        else {
                        appendSignal(1);
                        //test = 7; 
                        }
			Up = false;	 
		}
	}  
}

inline void appendSignal(unsigned char signal) {
	//Log(signal, DEC);
	runningBuffer = runningBuffer | ((unsigned long long) signal << bufferPosition);  
	bufferPosition++;
	if (bufferPosition > 59) {
		// Buffer is full before at end of time-sequence 
		// this may be due to noise giving additional peaks
		//LogLn("EoB");
//                Serial.print("EoB");
//                Serial.println();
		finalizeBuffer();
	}
}

inline void finalizeBuffer(void) {
  if (bufferPosition == 59) {
		// Buffer is full
		//LogLn("BF");
//                Serial.print("BF");
//                Serial.println();
		// Prepare filled buffer and time stamp for main loop
		filledBuffer = runningBuffer;
		filledTimestamp = now();
		// Reset running buffer
		bufferinit();
		FilledBufferAvailable = true;    
    } else {
		// Buffer is not yet full at end of time-sequence
		//LogLn("EoM");
//		Serial.print("EoM");
//                Serial.println();
		// Reset running buffer
		bufferinit();      
    }
}

bool receivedTimeUpdate(void) {
	// If buffer is not filled, there is no new time
	if(!FilledBufferAvailable) {
		return false;
	}
	// if buffer is filled, we will process it and see if this results in valid parity
	if (!processBuffer()) {
		//LogLn("Invalid parity");
//		Serial.print("Invalid parity");
//                Serial.println();
		return false;
	}
	
	// Since the received signal is error-prone, and the parity check is not very strong, 
	// we will do some sanity checks on the time
	time_t processedTime = latestupdatedTime + (now() - processingTimestamp);
	if (processedTime<MIN_TIME || processedTime>MAX_TIME) {
		//LogLn("Time outside of bounds");
//		Serial.print("Time outside of bounds");
//                Serial.println();
		return false;
	}

	// If received time is close to internal clock (2 min) we are satisfied
	time_t difference = abs(processedTime - now());
	if(difference < 2*SECS_PER_MIN) {
		//LogLn("close to internal clock");
//		Serial.print("close to internal clock");
//                Serial.println();
		storePreviousTime();
		return true;
	}

	// Time can be further from internal clock for several reasons
	// We will check if lag from internal clock is consistent
	time_t shiftPrevious = (previousUpdatedTime - previousProcessingTimestamp);
	time_t shiftCurrent = (latestupdatedTime - processingTimestamp);	
	time_t shiftDifference = abs(shiftCurrent-shiftPrevious);
	storePreviousTime();
	if(shiftDifference < 2*SECS_PER_MIN) {
		//LogLn("time lag consistent");
//                Serial.print("time lag consistent");
//                Serial.println();		
		return true;
	} else {
		//LogLn("time lag inconsistent");
//                Serial.print("time lag inconsistent");
//                Serial.println();
	}
	
	// If lag is inconsistent, this may be because of no previous stored date 
	// This would be resolved in a second run.
	return false;
}

void storePreviousTime(void) {
	previousUpdatedTime = latestupdatedTime;
	previousProcessingTimestamp = processingTimestamp;
}

void calculateBufferParities(void) {	
	// Calculate Parity 
	flags.parityFlag = 0;	
	for(int pos=0;pos<59;pos++) {
		bool s = (processingBuffer >> pos) & 1;  
		
		// Update the parity bits. First: Reset when minute, hour or date starts.
		if (pos ==  21 || pos ==  29 || pos ==  36) {
			flags.parityFlag = 0;
		}
		// save the parity when the corresponding segment ends
		if (pos ==  28) {flags.parityMin = flags.parityFlag;};
		if (pos ==  35) {flags.parityHour = flags.parityFlag;};
		if (pos ==  58) {flags.parityDate = flags.parityFlag;};
		// When we received a 1, toggle the parity flag
		if (s == 1) {
			flags.parityFlag = flags.parityFlag ^ 1;
		}
	}
}

bool processBuffer(void) {	
	
	/////  Start interaction with interrupt driven loop  /////
	
	// Copy filled buffer and timestamp from interrupt driven loop
	processingBuffer = filledBuffer;
	processingTimestamp = filledTimestamp;
	// Indicate that there is no filled, unprocessed buffer anymore
	FilledBufferAvailable = false;  
	
	/////  End interaction with interrupt driven loop   /////

	//  Calculate parities for checking buffer
	calculateBufferParities();
	tmElements_t time;
	bool proccessedSucces;

	struct DCF77Buffer *rx_buffer;
	rx_buffer = (struct DCF77Buffer *)(unsigned long long)&processingBuffer;

	// Check parities
    if (flags.parityMin == rx_buffer->P1  &&
        flags.parityHour == rx_buffer->P2 &&
        flags.parityDate == rx_buffer->P3 &&
		rx_buffer->CEST != rx_buffer->CET) 
    { 
      //convert the received buffer into time	  	  	 
      time.Second = 0;
	  time.Minute = rx_buffer->Min-((rx_buffer->Min/16)*6);
      time.Hour   = rx_buffer->Hour-((rx_buffer->Hour/16)*6);
      time.Day    = rx_buffer->Day-((rx_buffer->Day/16)*6); 
      time.Month  = rx_buffer->Month-((rx_buffer->Month/16)*6);
      time.Year   = 2000 + rx_buffer->Year-((rx_buffer->Year/16)*6) -1970;
	  latestupdatedTime = makeTime(time);	 
	  CEST = rx_buffer->CEST;
	  //Parity correct
	  return true;
	} else {
	  //Parity incorrect
	  return false;
	}
}

time_t getTime(void)
{
	if (!receivedTimeUpdate()) {
		return(0);
	} else {
		// Send out time, taking into account the difference between when the DCF time was received and the current time
		time_t currentTime =latestupdatedTime + (now() - processingTimestamp);
		return(currentTime);
	}
}

time_t getUTCTime(void)
{
	if (!receivedTimeUpdate()) {
		return(0);
	} else {
		// Send out time UTC time
		int UTCTimeDifference = (CEST ? 2 : 1)*SECS_PER_HOUR;
		time_t currentTime =latestupdatedTime - UTCTimeDifference + (now() - processingTimestamp);
		return(currentTime);
	}
}

#endif
