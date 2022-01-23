#include <dht11.h>
#define DHT11PIN 8

dht11 DHT11;

// Initial Variables and Constants
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
const int RELAY_PIN = 22;  // the Arduino pin, which connects to the IN pin of relay

int lightOutPut = 0;
int soilMoistureValue = 0;
int soilmoisturepercent=0;



void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
 
}

void loop()
{
  
  const int photocellPin = A0;
  lightOutPut = analogRead(photocellPin);
  
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  int fTemp = (float)DHT11.temperature * 9/5 + 32;
  Serial.print("Temperature (F): ");
  Serial.println(fTemp);
  Serial.print("Light Meter: ");
  Serial.println(lightOutPut);
  
  
  soilMoistureValue = analogRead(A1);  //put Sensor insert into soil
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if(soilmoisturepercent >= 100)
  {
    Serial.print("Soil Moisture: ");
    Serial.println("100 %");
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
  }
  else if(soilmoisturepercent <=0)
  {
    Serial.print("Soil Moisture: ");
    Serial.println("0 %");
  }
  else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
  {
    digitalWrite(RELAY_PIN, LOW);
    delay(500);
    Serial.print("Soil Moisture: ");
    Serial.print(soilmoisturepercent);
    Serial.println("%");
    
  }
  
  delay(2000);

}
