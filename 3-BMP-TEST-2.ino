#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "TCA9548.h"

#define PCA9548A_ADDR 0x70  // PCA9548A, I2C stress

Adafruit_BMP280 bmp;

float pressure0;
float pressure1;
float pressure2;
float pressure3;
float pressure4;
float pressure5;
float pressure6;
int state = 0; //decide print or not
int input = 0; //decide print or not

void setup() {
  Serial.begin(9600);
  Wire.begin();  // initialization

  selectChannel(0);
  if (!bmp.begin(0x76)) {
      Serial.println("Could not find BMP280-0, check wiring!");
      while (1);
    }
  delay(10);
  pressure0 = pressurecalibration();

  selectChannel(1);
  if (!bmp.begin(0x76)) {
      Serial.println("Could not find BMP280-1, check wiring!");
      while (1);
    }
  delay(10);
  pressure1 = pressurecalibration();

  selectChannel(2);
  if (!bmp.begin(0x76)) {
      Serial.println("Could not find BMP280-2, check wiring!");
      while (1);
    }
  delay(10);
  pressure2 = pressurecalibration();

  // selectChannel(3);
  // if (!bmp.begin(0x76)) {
  //     Serial.println("Could not find BMP280-3, check wiring!");
  //     while (1);
  //   }
  // delay(10);
  // pressure3 = pressurecalibration();

  // selectChannel(4);
  // if (!bmp.begin(0x76)) {
  //     Serial.println("Could not find BMP280-4, check wiring!");
  //     while (1);
  //   }
  // delay(10);
  // pressure4 = pressurecalibration();

  // selectChannel(5);
  // if (!bmp.begin()) {
  //     Serial.println("Could not find BMP280-5, check wiring!");
  //     while (1);
  //   }
  // delay(10);
  // pressure5 = bmp.readPressure();

  // selectChannel(6);
  // if (!bmp.begin(0x76)) {
  //     Serial.println("Could not find BMP280-6, check wiring!");
  //     while (1);
  //   }
  // delay(10);
  // pressure6 = pressurecalibration();

  Serial.println("BMP280*6 test ready");

}

void loop() {

state = 0;

  if(Serial.available()){
        //input = 1;
        input = Serial.parseInt();  
        }
        if (input>0){
          state = 1; // run   
          };
     
  if (state == 1)
  {

  selectChannel(0);
  Serial.print(bmp.readPressure()-102400);
  Serial.print(",");

  selectChannel(1);
  Serial.print(bmp.readPressure()-103200);
  Serial.print(",");

  selectChannel(2);
  Serial.println(bmp.readPressure()-100000);


  }
  delay(10);
  state = 0;
  //Serial.println(state);
  //exit(0);

}

void selectChannel(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(PCA9548A_ADDR);  // strat transmission
  Wire.write(1 << channel);  // select channel
  Wire.endTransmission();  // end
}

float pressurecalibration(){
  int N = 10;
  float pressureSum = 0.0;
  for (int i=0; i<N; i++){
    float pressure = bmp.readPressure();
    pressureSum += pressure;
    delay(10);
  }
  float pressureavg = pressureSum / N;
  return pressureavg;
}
