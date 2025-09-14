#include "BluetoothSerial.h"

/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void btsetup() {
  // Serial.begin(115200);
  /* If no name is given, default 'ESP32' is applied */
  /* If you want to give your own name to ESP32 Bluetooth device, then */
  /* specify the name as an argument SerialBT.begin("myESP32Bluetooth"); */
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void get_bt_data() {
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
  // delay(1);
}

int bt_get(){
  if (SerialBT.available()){
    // Serial.write(SerialBT.read());
    return SerialBT.read();//0;//SerialBT.read();
  }else{
    return 0;
  }
}

void bt_send(char * data){
  uint8_t udata[125];
  if(strlen(data)){
    for(int i=0;i<strlen(data);i++){
      udata[i] = data[i]; 
      SerialBT.write(udata[i]);
    }
    SerialBT.write(13);
  }
}