int aset;
int dtt2;
int newdtt1;
int digit1 = 11; 
int digit2 = 10; 
int digit3 = 9; 
int digit4 = 6; 
int digit5 = A3; 
int digit6 = A2; 
int Dot = 1;
int Hrchime = 0;
int segA = 2;
int segB = 3;    
int segC = 4; 
int segD = 5; 
int segE = 12; 
int segF = 7; 
int segG = 8; 
int SW0   =A0;
int SW1   =A1;
int almout =13;
int aset1 = 3; // set value as 3  for first time retrival of alarm set 
int alringt =1; // required alarm ring time in minute
int hrchringt = 6;// required time for hour chime in seconds
static unsigned int altim;
//#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#define EEADDR 166 // Start location to write EEPROM data.
RTC_DS3231 RTC;
// =====================setup()=================================
void setup() {
//Serial.begin(9600);
   RTC.begin();
  DateTime now = RTC.now();
//RTC.adjust(DateTime(__DATE__, __TIME__));// for setting clock   remove // from this line  and upload sketch
 //after setting clock again put // on the line and upload once more 

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(Dot, OUTPUT);
  pinMode(Hrchime, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(digit5, OUTPUT);
  pinMode(digit6, OUTPUT);
  pinMode(almout, OUTPUT);
  pinMode(SW0, INPUT);  // Alarm  setting SPST  switch
  pinMode(SW1, INPUT);  //Alarm setting  PUSH switch
  digitalWrite(SW0, LOW);
  digitalWrite(SW1, LOW);
  digitalWrite(almout, LOW);
  digitalWrite(Hrchime, LOW);


//  retrieving alarm set time from flash on first time power_on

int EEAddr = EEADDR;
if (aset1 == 3  ) {
  EEPROM.get(EEAddr , altim); EEAddr += sizeof(altim);
    newdtt1 = altim;
    dtt2 = altim; 
    aset1 = 6;
    aset  = 7;
  //Serial.print ("Flash first Read  "); 
  //Serial.print (dtt2);
 }
 else{}

//  end of alrm set time retrieving from flash memory
 
}//==================end of setup ()====================================



//******************** STARTING MAIN PROGRAM*****************************

void loop() {
  //digitalWrite(segDP, HIGH);

  int mt;
  int dt;
  int dtt;
  int almsethr;
  int almsetmn;
  int chm;

while ( digitalRead(SW0) == HIGH  && digitalRead(SW1) == LOW ){
 
    dt = almsethr;
    mt = almsetmn;
   
    for (int i = 20 ; i > 0  ; i--) {
      Light_HR_MIN(dtt2);
     Light_HR_MIN(dtt2);
    }
    }    //end of while loop

 
 while ( digitalRead(SW0) == HIGH  && digitalRead(SW1) == HIGH){
    digitalWrite(Dot, HIGH);
    digitalWrite(digit5, HIGH);
    digitalWrite(digit6, HIGH);
    
    dtt2++;
    int a;
    int b;
    a = dtt2 / 100;
    b = dtt2 % 100;

    if (b >= 60)
    { b = 0;
      a++;
    }
    else {}
    if (a >= 24) a = 0;
    else {}
    dtt2 =  a * 100 + b;

    for (int i = 20 ; i > 0  ; i--) {
     Light_HR_MIN(dtt2);
     Light_HR_MIN(dtt2);
      
    }
    almsethr = dt;
    almsetmn = mt;
    aset =1;
  
    }        //end of while loop


 while ( digitalRead(SW0) == LOW ){
   DateTime now = RTC.now();
   int rr= (now.hour());
   int gt=(now.minute());
   int timp5 = rr*100 + gt;
  
//----------- Writing Alarm set_time to Flash memory------
 
  
  if (aset == 1){
 ALARMSTORE(dtt2 ,1 , newdtt1);
aset = 6;
}
else{}

//---------------------------------Alarm ringing------

   if (timp5 == dtt2   ) {
           digitalWrite(almout, HIGH);
        }
   else{}
 if (timp5 == dtt2+alringt) {
   digitalWrite(almout, LOW);
}
  else{}
  
//-----------------------------Hour chime setting----------=----
 
if ( timp5 % 100 == 00   &&  now.second() <= hrchringt )    
       { digitalWrite(Hrchime, HIGH);
       }
    else{       
   digitalWrite(Hrchime , LOW); }

 
//------------STARTS LINES FOR DISPLAYING CURRENT TIME-----------
   
  if ( digitalRead(SW0) == LOW  ) {

 DateTime now = RTC.now();
  int tim = (now.hour());
  if (tim >  12) {
   tim = tim - 12;
    }
  else;
  if (tim ==  0) {
      tim = 12; }
    else;
    int timp = (tim * 100 + now.minute());
    int timp1 = now.second();
   
// For Digits display
    for (int i = 8 ; i > 0  ; i--) {
       Light_HR_MIN(timp);
       displaysecond(timp1); }
   }
  else {}

}   //end of WHILE loop 

 } // ==================END OF MAIN PROGRAM======================


// ***************SUB PROGRAMS************************************

//======================for display of Hour and Minute============
void Light_HR_MIN(int toDisplay) {
#define BRIGHTNESS  1000
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW
int hrr =toDisplay/100;

  if (digitalRead(SW1) == HIGH)
  { digitalWrite(digit5, LOW);
    digitalWrite(digit6, LOW);
  }
  else{}

  for (int digit = 4 ; digit > 0 ; digit--) {
        switch (digit) {
     
      case 1:
      if (hrr < 10  && hrr != 0 )
         {digitalWrite(digit1, DIGIT_OFF);
         }
         else{
         digitalWrite(digit1, DIGIT_ON);
         }
         break;
      case 2:
         digitalWrite(digit2, DIGIT_ON);
         break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
         break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        break;
    }
    
    ShowNumber(toDisplay % 10);
    toDisplay /= 10;
    delayMicroseconds(BRIGHTNESS);
    ShowNumber(10);
    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }
}

//====================for display of Second and dots============
void displaysecond(int sec) {
#define BRIGHTNESS 1000
#define BRIGHTNESS1  400

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW
  int yy = sec / 10;
  int aa = sec % 10;
  digitalWrite(digit5, DIGIT_ON);
  digitalWrite(digit6, DIGIT_OFF);
  if (sec % 2 == 0 ) {
    digitalWrite(Dot, LOW);
    delayMicroseconds(BRIGHTNESS);
  }
  else;
   digitalWrite(Dot, HIGH);
   delayMicroseconds(BRIGHTNESS1);
   digitalWrite(digit6, DIGIT_ON);
   digitalWrite(digit5, DIGIT_OFF);
 
ShowNumber(yy);
  delayMicroseconds(BRIGHTNESS);
  digitalWrite(digit5, DIGIT_ON);
  digitalWrite(digit6, DIGIT_OFF);
  
  ShowNumber(aa );
  delayMicroseconds(BRIGHTNESS);
  
  ShowNumber(10);
  digitalWrite(digit6, DIGIT_OFF);
  digitalWrite(digit5, DIGIT_OFF);
}
//================for diplay of each of the six digits=============
void ShowNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay) {
    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

  }}
//====================For storing alarnm data in flash memory===========

  void ALARMSTORE(int alrmtim , int rw ,  int newdtt1) {

   static unsigned int altim;
   int EEAddr = EEADDR;
   altim = alrmtim;
   if (rw == 1){ 
      EEPROM.update(EEAddr , altim); EEAddr += sizeof(altim);
   //   Serial.print("EEPROM Written");
   //   Serial.print(altim);
      newdtt1 = altim;
      dtt2 = altim;
   }   

 else{}
      if (rw == 0){
      EEPROM.get(EEAddr , altim); EEAddr += sizeof(altim);
     // Serial.print("EEPROMread");
    //  Serial.print(altim);
      newdtt1 = altim;
 dtt2 = altim; 
}
else{}

} // end of  ALRMSTORE
