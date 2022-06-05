#define BLYNK_TEMPLATE_ID           "Change It"
#define BLYNK_DEVICE_NAME           "Chnage It"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_WROVER_BOARD
#include "BlynkEdgent.h"

#define soil 13
#define waterPump 34
WidgetLED pump(V1);

float soilLevel, soilR;
WidgetLCD vLcd(V2);
void sendSensor()
{
  readSoil();
  if(soilLevel>=80)
  {    
    digitalWrite(waterPump, LOW);
    vLcd.print(0,0,"Water Pump OFF");
    pump.off();
  }
  
 if(soilLevel<20)
  {    
    digitalWrite(waterPump, HIGH);
    vLcd.print(0,0, "Water Pump ON ");
    pump.on();
  }
}
void readSoil()
{
  soilR=analogRead(soil);  
  Serial.println(soilR);
  soilLevel=map(soilR, 0, 1024, 200,0); // adjust soil level here
  Serial.println(soilLevel);
  Blynk.virtualWrite(V0, soilLevel);
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, LOW);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  sendSensor();
}
