#include <dht11.h>
#define DHT11PIN 8

dht11 DHT11;

// Initial Constants
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
const int RELAY_PIN = 22;  // the Arduino pin, which connects to the IN pin of relay
const int photocellPinOne = A0;

// Initial Variables
int lightOutPut = 0;
int soilMoistureValue = 0;
int soilmoisturepercent=0;

// Helper Functions
float GetTempCelsius(float Voltage)
{
  float temp = 0;
  temp = (Voltage-.05)*100;
  return temp;
}

float GetTempCelFarenheit(float Voltage)
{
  float temp = 0;
  temp = Voltage * 9/5 + 32;
  return temp;
}

float GetLightReading(int photocellPin)
{
  int photocellReading = analogRead(photocellPin);
  return photocellReading;
}

float GetHumidityReading()
{
  float humidityReading = DHT11.humidity;
  return humidityReading;
}

float GetMoisturePercentValue(int moistureSensorValue)
{
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  return soilmoisturepercent;
}

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
 
}

void loop()
{

  // Humidity Monitoring
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println(GetHumidityReading());

  // Temp Monitoring
  float displayTemp = GetTempCelFarenheit(DHT11.temperature);
  Serial.print("Temperature (F): ");
  Serial.println(displayTemp);

  
  // Moisture Monitoring
  GetMoisturePercentValue(analogRead(A1));
  soilMoistureValue = analogRead(A1);  //put Sensor insert into soil
  soilmoisturepercent = GetMoisturePercentValue(analogRead(A1));
  // TODO: Break into another function toggle relay
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

  // Light Monitoring
  int lightOutPut = GetLightReading(photocellPinOne);
  Serial.print("Light Meter: ");
  Serial.println(lightOutPut);
  Serial.println();
  
  delay(2000);

}
