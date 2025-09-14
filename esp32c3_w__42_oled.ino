#include <U8g2lib.h>
#include <Wire.h>
#include <temp.h>
//#include "esp32_bluetooth.h"


// select board ESP32C3 DEV BOARD

// there is no 72x40 constructor in u8g2 hence the 72x40 screen is mapped in the middle of the 132x64 pixel buffer of the SSD1306 controller
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);
int width = 72;
int height = 40;
int xOffset = 30; // = (132-w)/2
int yOffset = 12; // = (64-h)/2

void setup(void)
{
  delay(3000);
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup  Started! ");
  Serial.printf("setup  Started! \n");
  //      btsetup();
  u8g2.begin();
  u8g2.setContrast(255); // set contrast to maximum 
  u8g2.setBusClock(400000); //400kHz I2C 
//  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFont(u8g2_font_ncenB12_tr); // font
  temp_setup();
  pinMode(8, OUTPUT);
}

void loop(void)
{
  int bresult = 0;
  static int counter =0;
  static bool led = false;
  led = !led;
  digitalWrite(8, led);
  
  
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.drawFrame(xOffset+0, yOffset+0, width, height); //draw a frame around the border
  u8g2.setCursor(xOffset+3, yOffset+12);
  //    u8g2.printf("%dx%d", width, height);
  u8g2.printf("%d", counter++);
  u8g2.setCursor(xOffset+3, yOffset+24);
  float t = get_temp();
  u8g2.printf("%0.1f F", t);
  Serial.printf("counter = %d,temp = %0.1f F\n",counter - 1,t);

  //  if(bresult = bt_get()){
  //   u8g2.printf("%d", bresult);
  //  }
  u8g2.sendBuffer(); // transfer internal memory to the display
  //delay(1000);
}