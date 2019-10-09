// This #include statement was automatically added by the Particle IDE.
//#include <AssetTracker.h>

// This #include statement was automatically added by the Particle IDE.
//#include <AssetTracker.h>

//#include "Adafruit_LIS3DH.h"
//#include "Adafruit_GPS.h"
//#include "Adafruit_Sensor.h"
//#include "AssetTracker.h"
#include "time.h"

//STARTUP(System.enableFeature(FEATURE_RETAINED_MEMORY));  //Code to enable a feature in the electron called reatained memory

//SSI Code - Variables:

    bool isHeating = false;     //Statement for heatStopTime. Is Heat Injector Heating
    long heatStartTime = 0;    //recorded millis time the pin went HIGH
    long heatStopTime = 0;     //recorded millis time the pinState went LOW
    long deltaHeatTime = 0;    //calculated delta between Start and End times
    long totalHeatTime = 0;    //needs to be backed up on the API
    int led = D7;   //On-Board Blue led
    int collectHours = B0;
    int SD = B3;    //SD is "set" on latching relay, NO contact. When High for 1sec it will shutdown heat.
    int SDreset = B5;   //SDreset is "reset" on latching relay, NC contact. When High for 1sec it will Enable heat.
/* GPS Features - Variables
    int transmittingData = 1;   // 1 will Particle.publish AND Serial.print, 0 will just Serial.print. You can also change this remotely using the Particle.function "tmode" defined in setup()
    long lastPublish = 0;    // Used to keep track of the last time we published data
    int delayMinutes = 60;  // How many minutes between publishes? 10+ recommended for long-time continuous publishing!

    AssetTracker t = AssetTracker();    // Creating an AssetTracker named 't' for us to reference
    FuelGauge fuel;     // A FuelGauge named 'fuel' for checking on the battery state
*/
void setup() 

{
    Particle.publish("1.Entering Setup");
//GPS Features - Setup()
/*
    t.begin();  // Sets up all the necessary AssetTracker bits
    t.gpsOn();  // Enable the GPS module. Defaults to off to save power. Takes 1.5s or so because of delays.

    //Serial.begin(9600);   // Opens up a Serial port so you can listen over USB

    // These three functions are useful for remote diagnostics. Read more below.
    Particle.function("tmode", transmitMode);
    Particle.function("batt", batteryStatus);
    Particle.function("gps", gpsPublish);
*/    
//SSI Code - Setup()
    
    pinMode(collectHours, INPUT_PULLDOWN);
    //Declaring B0 as input
    
    
    pinMode(led, OUTPUT);   //On-Board Led output
    digitalWrite(led, LOW);     
    
    pinMode(SD, OUTPUT);    //Shutdown output
    digitalWrite(SD, LOW);
    
    pinMode(SDreset, OUTPUT);
    digitalWrite(SDreset, LOW);     //Shutdown Reset output
    
    Particle.publish("2.Done Declaring Pins");

    
    //Particle Functions and Variables
    //Particle.function("toggleSD", toggleSD);
    //Particle.function("toggleSDreset", toggleSDreset);
    Particle.variable("totalHeatTime", totalHeatTime);
    Particle.variable("heatStartTime", heatStartTime);
    Particle.variable("heatStopTime", heatStopTime);
    Particle.variable("deltaHeatTime", deltaHeatTime);
    Particle.variable("isHeating", isHeating);
    //Particle Publish Events
    //Particle.publish("totalHeatTime", totalHeatTime);
    //Particle.publish("heatStartTime", heatStartTime);
    //Particle.publish("heatStopTime", heatStopTime);
    //Particle.publish("deltaHeatTime", deltaHeatTime);
    //Particle.publish("isHeating", isHeating);
    Particle.publish("3.Done Listing Variables");
    
    if (digitalRead(collectHours == TRUE));     //When Heat is Started and pinState goes HIGH
    {
        isHeating = TRUE;
        digitalWrite(led, HIGH);    //Turn on blue LED  
        heatStartTime = millis();   //Store current millis in (Start Time)
        Particle.publish("heatStartTime:Recorded");
        Particle.publish (String(heatStartTime), PUBLIC);    //Publish the (Start Time) value
       
        while(1)    //While the pinState is TRUE, loop the following if statment
        {
            if (digitalRead(collectHours == FALSE));    //When the Heat turns off, do the following:
            {
                isHeating = FALSE;
                digitalWrite(led, LOW);     //Turn the blue LED off
                heatStopTime = millis();    //Store current millis in (Stop Time)
                Particle.publish("heatStopTime:Recorded");
                Particle.publish(String(heatStopTime), PRIVATE);     //Publish the (Stop Time) value
            }
        deltaHeatTime = heatStopTime - heatStartTime;   //After the if statment during the while loop, update the (Delta Time)
        Particle.publish("deltaHeatTime:Recorded");
        Particle.publish(String(deltaHeatTime), PRIVATE);    //Publish the (DeltaTime) value
        totalHeatTime = deltaHeatTime + totalHeatTime;      //Update the new (Total Time) value
        Particle.publish("totalHeatTime:Recorded");
        Particle.publish(String(totalHeatTime), PRIVATE);    //Publish the (TotalTime) value
        }
        
    delay(1000);
    }
    Particle.publish("4.Waiting for Shutdown Commands");
    /*
    int toggleSD(String command)    //Command to Shutdown with the "set" on latching relay
    {
        if (command == "off" || command == "Off" || command == "OFF");  //requests are case sensitive...Program accepts "off", "Off", or "OFF" to shutdown heat
        digitalWrite(SD, HIGH);
        delay(1000);
        digitalWrite(SD, LOW);
        return 1;   //If heat was shutdown, return "1"
    }
    
    int toggleSDreset(String command)   //Command to "Reset" latching relay, Run machine again. 
    {
        if (command == "on" || command == "On" || command == "ON");  //requests are case sensitive...Program accepts "on", "On", or "ON" to enable heat again
        digitalWrite(SDreset, HIGH);
        delay(1000);
        digitalWrite(SDreset, LOW);
        return 1;   //If heat was enabled, return "1"
    }
    */
    
}


void loop() 

{
   Particle.publish("5.Checking if Heat is ON");  
    //Begins the function of commands
    
    if (digitalRead(collectHours == HIGH));     //When Heat is Started and pinState goes HIGH
    {
        isHeating = TRUE;
        digitalWrite(led, HIGH);    //Turn on blue LED  
        heatStartTime = millis();   //Store current millis in (Start Time)
        Particle.publish("heatStartTime:Recorded");
        Particle.publish(String(heatStartTime), PRIVATE);    //Publish the (Start Time) value
       
        while(1)    //While the pinState is TRUE, loop the following if statment
        {
            if (digitalRead(collectHours == LOW));    //When the Heat turns off, do the following:
            {
                isHeating = FALSE;
                digitalWrite(led, LOW);     //Turn the blue LED off
                heatStopTime = millis();    //Store current millis in (Stop Time)
                Particle.publish("heatStopTime:Recorded");
                Particle.publish(String(heatStopTime), PRIVATE);     //Publish the (Stop Time) value
            }
        deltaHeatTime = heatStopTime - heatStartTime;   //After the if statment during the while loop, update the (Delta Time)
        Particle.publish("deltaHeatTime:Recorded");
        Particle.publish(String(deltaHeatTime), PRIVATE);    //Publish the (DeltaTime) value
        totalHeatTime = deltaHeatTime + totalHeatTime;      //Update the new (Total Time) value
        Particle.publish("totalHeatTime:Recorded");
        Particle.publish(String(totalHeatTime), PRIVATE);    //Publish the (TotalTime) value
        }
        
    delay(1000);
    }
}


//GPS Features - loop()
/*
    t.updateGPS();  // You'll need to run this every loop to capture the GPS output

    
    if (millis()-lastPublish > delayMinutes*60*1000) // if the current time - the last time we published is greater than your set delay...
{  
    lastPublish = millis(); // Remember when we published

    //String pubAccel = String::format("%d,%d,%d", t.readX(), t.readY(), t.readZ());
    //Serial.println(pubAccel);
    //Particle.publish("A", pubAccel, 60, PRIVATE);

    //Serial.println(t.preNMEA());    // Dumps the full NMEA sentence to serial in case you're curious

    if (t.gpsFix()) // GPS requires a "fix" on the satellites to give good data, so we should only publish data if there's a fix
    {
        if (transmittingData) // Only publish if we're in transmittingData mode 1;
        {
           Particle.publish("Location", t.readLatLon(), 60, PRIVATE); // Short publish names save data!
        }
    //Serial.println(t.readLatLon()); // but always report the data over serial for local development
    }
}
}

// Allows you to remotely change whether a device is publishing to the cloud
// or is only reporting data over Serial. Saves data when using only Serial!
// Change the default at the top of the code.
int transmitMode(String command) {
    transmittingData = atoi(command);
    return 1;
}

// Actively ask for a GPS reading if you're impatient. Only publishes if there's
// a GPS fix, otherwise returns '0'
int gpsPublish(String command) {
    if (t.gpsFix()) {
        Particle.publish("Location", t.readLatLon(), 60, PRIVATE);

        // uncomment next line if you want a manual publish to reset delay counter
        // lastPublish = millis();
        return 1;
    } else {
      return 0;
    }
}

// Lets you remotely check the battery status by calling the function "batt"
// Triggers a publish with the info (so subscribe or watch the dashboard)
// and also returns a '1' if there's >10% battery left and a '0' if below
int batteryStatus(String command){
    // Publish the battery voltage and percentage of battery remaining
    // if you want to be really efficient, just report one of these
    // the String::format("%f.2") part gives us a string to publish,
    // but with only 2 decimal points to save space
    Particle.publish("Battery",
          "v:" + String::format("%.2f",fuel.getVCell()) +
          ",c:" + String::format("%.2f",fuel.getSoC()),
          60, PRIVATE);
    
    if (fuel.getSoC()>50){ return 1;}     // if there's more than 50% of the battery left, then return 1
    
    
    else { return 0;}   // if you're running out of battery, return 0

*/
//SSI Code - loop()

    //isHeating = digitalRead(B0); //Boolian for recording heatStopTime
    
    
