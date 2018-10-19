
#include "DHT.h"
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Temp/Humidity Sensor
#define DHTPIN 17     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);



// Relay
#define BULB 18
#define FAN 19

void setup() {
  Serial.begin(9600); 
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Smart Incubator");
  delay(1000);
 
  dht.begin();
  
  // Setup relay
  pinMode(BULB, OUTPUT);
  pinMode(FAN, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Fahrenheit
  float temp = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    lcd.setCursor(0,0);
  lcd.print("Humi: "); 
  lcd.print(humidity);
  lcd.print(" %      ");
  lcd.setCursor(0,1);
  lcd.print("Temp: "); 
  lcd.print(temp);
  lcd.print(" F      ");
  
  if ((temp < 99) || (humidity>60))
  {
    digitalWrite(BULB, LOW);
    digitalWrite(FAN, LOW);
  

  } 
  else if ((temp > 108)|| (humidity<50 ))
  {
    digitalWrite(BULB, HIGH);
    digitalWrite(FAN, HIGH);
     
}

  


}
