// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void temp_setup(void)
{
  Serial.println("Dallas Temperature IC Control Setup");
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);//don't need external pullup resister
    // Start up the library
  sensors.begin();
  int dcnt = sensors.getDS18Count();
  uint8_t address;
  if (dcnt > 0){
    Serial.printf("found %d devices\n",dcnt);
    for(int i = 0;i < dcnt;i++){
      sensors.getAddress(&address, (uint8_t)i);
      Serial.printf("Device %d @ address = 0x%x with resolution of %d bits \n",i, address,sensors.getResolution());
    }
  }else{
    Serial.println("no devices found");
  }
   
}

/*
 * Main function, get and show the temperature
 */
void temp_test_loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  delay(1500);
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempFByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}

float get_temp(){
  sensors.requestTemperatures(); // Send the command to get temperatures
  delay(1000);
  float deg_f = sensors.getTempFByIndex(0);
  return deg_f; 
}
