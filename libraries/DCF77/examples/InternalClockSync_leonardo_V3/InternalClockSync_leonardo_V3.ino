/*
 * InternalClockSync.pde
 * example code illustrating time synced from a DCF77 receiver
 * Thijs Elenbaas, 2012
 * This example code is in the public domain.
 
  This example shows how to fetch a DCF77 time and synchronize
  the internal clock. In order for this example to give clear output,
  make sure that you disable logging  from the DCF library. You can 
  do this by commenting out   #define VERBOSE_DEBUG 1   in Utils.cpp. 
 */

//#include "DCF77.h"
#include <Time.h>
#include <Utils.h>  

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#define MIN_TIME 1334102400     // Date: 11-4-2012
#define MAX_TIME 4102444800     // Date:  1-1-2100

#define DCFRejectionTime 700	// Pulse-to-Pulse rejection time. 
#define DCFRejectPulseWidth 50  // Minimal pulse width
#define DCFSplitTime 180		// Specifications distinguishes pulse width 100 ms and 200 ms. In practice we see 130 ms and 230
#define DCFSyncTime 1500		// Specifications defines 2000 ms pulse for end of sequence

#define DCF_PIN 7	         // Connection pin to DCF 77 device
#define DCF_INTERRUPT 4		 // Interrupt number associated with pin


bool initialized;	
//static int dCF77Pin;
//static int dCFinterrupt;
static byte pulseStart;

// DCF77 and internal timestamps
	static time_t previousUpdatedTime;
	static time_t latestupdatedTime;           	
	static time_t processingTimestamp;
	static time_t previousProcessingTimestamp;		
	static unsigned char CEST;
	// DCF time format structure
	struct DCF77Buffer {
	  //unsigned long long prefix		:21;
	  unsigned long long prefix		:17;
	  unsigned long long CEST		:1; // CEST 
	  unsigned long long CET		:1; // CET 
	  unsigned long long unused		:2; // unused bits
	  unsigned long long Min		:7;	// minutes
	  unsigned long long P1			:1;	// parity minutes
	  unsigned long long Hour		:6;	// hours
	  unsigned long long P2			:1;	// parity hours
	  unsigned long long Day		:6;	// day
	  unsigned long long Weekday	:3;	// day of week
	  unsigned long long Month		:5;	// month
	  unsigned long long Year		:8;	// year (5 -> 2005)
	  unsigned long long P3			:1;	// parity
	};

// DCF Parity format structure
	struct ParityFlags{
		unsigned char parityFlag	:1;
		unsigned char parityMin		:1;
		unsigned char parityHour	:1;
		unsigned char parityDate	:1;
	} static flags;

// Parameters shared between interupt loop and main loop
        static volatile int test;
	static volatile bool FilledBufferAvailable;
	static volatile unsigned long long filledBuffer;
	static volatile time_t filledTimestamp;

	// DCF Buffers and indicators
	static int  bufferPosition;
	static unsigned long long runningBuffer;
	static unsigned long long processingBuffer;

	// Pulse flanks
	static   int leadingEdge;
	static   int trailingEdge;
	static   int PreviousLeadingEdge;
	static   bool Up;

time_t time;
//DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);


void setup() {
  Serial.begin(9600); 
  pinMode(DCF_PIN, INPUT);	
  initialize();
  Start();
  test = 0;
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
}

void loop() {
  delay(1000);
  //Serial.print("Test");
  //Serial.print(test);
  //Serial.println();
  //Serial.print("Pufferposition");
  //Serial.print(bufferPosition);
  //Serial.println();
  time_t DCFtime = getTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
  }	
  digitalClockDisplay();  
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void initialize(void) 
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

void Start(void) 
{
		EICRB |= (1<<ISC60)|(0<<ISC61); // sets the interrupt type for EICRB (INT6).
		EIMSK |= (1<<INT6); // activates the interrupt. 6 for 6
	
}

inline void bufferinit(void) 
{
	runningBuffer    = 0;
	bufferPosition   = 0;
}

ISR(INT6_vect) {
  
  test = 1;	
  
        int flankTime = millis();
	volatile byte sensorValue = digitalRead(DCF_PIN);
	//byte sensorValue = sensorValue2 ^ 1;

	// If flank is detected quickly after previous flank up
	// this will be an incorrect pulse that we shall reject
	if ((flankTime-PreviousLeadingEdge)<DCFRejectionTime) {
		//LogLn("rCT");
                test = 2;
		return;
	}
	
	// If the detected pulse is too short it will be an
	// incorrect pulse that we shall reject as well
	if ((flankTime-leadingEdge)<DCFRejectPulseWidth) {
	    //LogLn("rPW");
                test = 3;
		return;
	}
	
	if(sensorValue==pulseStart) {
		if (!Up) {
			// Flank up
			leadingEdge=flankTime;
                        test = 4;
			Up = true;		                
		} 
	} else {
		if (Up) {
			// Flank down
			trailingEdge=flankTime;
			int difference=trailingEdge - leadingEdge;            
          		
			if ((leadingEdge-PreviousLeadingEdge) > DCFSyncTime) {
				finalizeBuffer();
                                test = 5;
			}         
			PreviousLeadingEdge = leadingEdge;       
			// Distinguish between long and short pulses
			if (difference < DCFSplitTime) { 
                        appendSignal(0);
                        test = 6;
                        } 
                        else {
                        appendSignal(1);
                        test = 7; 
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
                Serial.print("EoB");
                Serial.println();
		finalizeBuffer();
	}
}

inline void finalizeBuffer(void) {
  if (bufferPosition == 59) {
		// Buffer is full
		//LogLn("BF");
                Serial.print("BF");
                Serial.println();
		// Prepare filled buffer and time stamp for main loop
		filledBuffer = runningBuffer;
		filledTimestamp = now();
		// Reset running buffer
		bufferinit();
		FilledBufferAvailable = true;    
    } else {
		// Buffer is not yet full at end of time-sequence
		//LogLn("EoM");
		Serial.print("EoM");
                Serial.println();
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
		Serial.print("Invalid parity");
                Serial.println();
		return false;
	}
	
	// Since the received signal is error-prone, and the parity check is not very strong, 
	// we will do some sanity checks on the time
	time_t processedTime = latestupdatedTime + (now() - processingTimestamp);
	if (processedTime<MIN_TIME || processedTime>MAX_TIME) {
		//LogLn("Time outside of bounds");
		Serial.print("Time outside of bounds");
                Serial.println();
		return false;
	}

	// If received time is close to internal clock (2 min) we are satisfied
	time_t difference = abs(processedTime - now());
	if(difference < 2*SECS_PER_MIN) {
		//LogLn("close to internal clock");
		Serial.print("close to internal clock");
                Serial.println();
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
                Serial.print("time lag consistent");
                Serial.println();		
		return true;
	} else {
		//LogLn("time lag inconsistent");
                Serial.print("time lag inconsistent");
                Serial.println();
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
