#include "arduino_secrets.h"
// Including Libraries
#include <BH1750FVI.h>
#include "thingProperties.h"
// Create a instance from library BH1750FVI
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void setup() 
{
  Serial.begin(115200);
  // To begin our Instance 'LightSensor'
  LightSensor.begin();  

    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500)

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  // To make our Inbuilt Led on and off
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  ArduinoCloud.update();
  
  // Fetch data from the sensor and transfering it to the variable 'intensity'
  uint16_t lux = LightSensor.GetLightIntensity();
  intensity = lux;
}
/*
  Since LedState is READ_WRITE variable, onLedStateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  digitalWrite(LED_BUILTIN, led);
}