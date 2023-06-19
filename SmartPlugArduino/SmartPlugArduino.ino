#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX
static bool dataStarted = false;
char receivedChar;

#define  SAMPLES 300

#define sensor1 A0 
#define sensor2 A1 
#define sensor3 A2 

float High_peak,Low_peak;         //Variables to measure or calculate
float Amps_Peak_Peak1, Amps_Peak_Peak2, Amps_Peak_Peak3;

float amper1 = 0,
      amper2 = 0,
      amper3 = 0;
       
String receivedData;
void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
}

void loop() {
  sensor1_oku();
  amper1 = Amps_Peak_Peak1*0.3536*0.04;
  if (amper1 < 0.17){
    amper1 = 0;
  }

  sensor2_oku();
  amper2 = Amps_Peak_Peak2*0.3536*0.06;
  if (amper2 < 0.39){
    amper2 = 0;
  }
  
  sensor3_oku();
  amper3 = Amps_Peak_Peak3*0.3536*0.06;
  if (amper3 < 0.39){
    amper3 = 0;
  }

  float veri[3] = { amper1, amper2, amper3 };

  String metin = String(amper1);
  metin += String("-");
  metin += String(amper2);
  metin += String("-");
  metin += String(amper3);

  mySerial.println(metin);

  Serial.print(veri[0]);
  Serial.print("-");
  Serial.print(veri[1]);
  Serial.print("-");
  Serial.println(veri[2]);
}

void sensor1_oku()
{
  int cnt;            
  High_peak = 0;      
  Low_peak = 1024;
  
      for(cnt=0 ; cnt<SAMPLES ; cnt++)          //everytime a sample (module value)  is taken it will go through test
      {
        float ACS_Value = analogRead(sensor1);  //We read a single value from the module

        
        if(ACS_Value  > High_peak)                //If that value is higher than the high peak (at first  is 0)
            {
              High_peak = ACS_Value;            //The  high peak will change from 0 to that value found
            }
        
        if(ACS_Value < Low_peak)                //If that value is lower than the  low peak (at first is 1024)
            {
              Low_peak = ACS_Value;             //The low peak will change from 1024 to that value found
            }
      }                                        //We keep looping until we take all  samples and at the end we will have the high/low peaks values
      
  Amps_Peak_Peak1  = High_peak - Low_peak;
}
void sensor2_oku()
{
  int cnt;            //Counter
  High_peak = 0;      //We first assume that our high peak  is equal to 0 and low peak is 1024, yes inverted
  Low_peak = 1024;
  
      for(cnt=0 ; cnt<SAMPLES ; cnt++)          //everytime a sample (module value)  is taken it will go through test
      {
        float ACS_Value = analogRead(sensor2);  //We read a single value from the module

        
        if(ACS_Value  > High_peak) 
            {
              High_peak = ACS_Value;
            }
        
        if(ACS_Value < Low_peak)    
            {
              Low_peak = ACS_Value; 
            }
      }                             
      
  Amps_Peak_Peak2  = High_peak - Low_peak;
}

void sensor3_oku()
{
  int cnt;            
  High_peak = 0;      
  Low_peak = 1024;
  
      for(cnt=0 ; cnt<SAMPLES ; cnt++) 
      {
        float ACS_Value = analogRead(sensor3);

        
        if(ACS_Value  > High_peak)            
            {
              High_peak = ACS_Value;          
            }
        
        if(ACS_Value < Low_peak)              
            {
              Low_peak = ACS_Value;           
            }
      }                                       
      
  Amps_Peak_Peak3  = High_peak - Low_peak;
}