#include "Adafruit_LIS3DH.h"
#include "Adafruit_GPS.h"
#include "Adafruit_Sensor.h"
#include "AssetTracker.h"
#include "time.h"

//Code to enable a feature in the electron called reatained memory
STARTUP(System.enableFeature(FEATURE_RETAINED_MEMORY));


//recorded unix time the pin went HIGH
float HeatStartTime = 0;
//recorded unix time the pun went LOW
float HeatEndTime = 0;
//calculated deltaTIME between Start and End
//float DeltaHeatTime = 0;
float DeltaHeatTime = (HeatEndTime - HeatStartTime);
//Reported Variable(required double) to GoogleSheetAPI
retained double TotalHeatTime = (TotalHeatTime + DeltaHeatTime);

//Blue led on board
int led = D7;
//SD is "set" on latching relay, NO contact. When High for 1sec it will shutdown heat.
int SD = B3;
//SD is "reset" on latching relay, NC contact. When High for 1sec it will Enable heat.
int SDreset = B5;


void setup() {
    //Declaring B0 as input
    pinMode(B0, INPUT);
    //Start with on-board led off
    pinMode(led, OUTPUT);
    
    //No power to latching relay unless done by admin
    pinMode(SD, OUTPUT);
    digitalWrite(SD, LOW);
    ////No power to latching relay unless done by admin
    pinMode(SDreset, OUTPUT);
    digitalWrite(SDreset, LOW);
    
    Particle.function("toggleSD", toggleSD);
    Particle.function("toggleSDreset", toggleSDreset);
    Particle.variable("TotalHeatTime", TotalHeatTime);
      
}
/*
Start Hour Meter Code */
 
 
    //While B0==true
//    if (digitalRead(B0)); 
    
    //Record time_t and store it in HeatStartTime(float)
//    time_t("rightNow") = HeatStartTime();
   
    //If B0==false, record time_t and store it in HeatEndTime(float)
//    if B0 == false();
    
    //If HeatStartTime < HeatEndTime 
//    time_t = HeatEndTime();
      
    //Calculate the DeltaTime and store it in DeltaHeatTime(float)
// (HeatStartTime - HeatEndTime) = DeltaHeatTime();
  
    //Add DeltaHeatTime to TotalHeatTime
//    digitalWrite(DeltaHeatTime, TotalHeatTime);


//Command to Shutdown with the "set" on latching relay
int toggleSD(String command){
    //requests are case sensitive...Program accepts "off", "Off", or "OFF" to shutdown heat
    if (command == "off" || command == "Off" || command == "OFF");
    //SD("set" is the NO contact on the latching relay
    digitalWrite(SD, HIGH);
    delay(1500);
    digitalWrite(SD, LOW);
    //If heat was shutdown, return "1"
    return 1;
    }
//Command to "Reset" latching relay, Run machine again. 
int toggleSDreset(String command){
    //requests are case sensitive...Program accepts "on", "On", or "ON" to enable heat again
    if (command == "on" || command == "On" || command == "ON");
    //SDreset("reset" is the NC contact on the latching relay
    digitalWrite(SDreset, HIGH);
    delay(1500);
    digitalWrite(SDreset, LOW);
    //If heat was enabled, return "1"
    return 1;
    }


void loop() {
    if (digitalRead(B0==TRUE)); {
    digitalWrite(led, HIGH);
    time_t now = HeatStartTime;
  } if (digitalRead(B0==FALSE)); {
    digitalWrite(led, LOW);
    time_t now = HeatEndTime;
  }
}
