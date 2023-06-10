#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define SOILPOWER 4
#define SOILPIN A0

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

DHT dht( DHTPIN, DHTTYPE );


int readSoil()
{
    int return_value;
    digitalWrite(SOILPOWER, HIGH);
    delay(10); 
    return_value = analogRead(SOILPIN);
    digitalWrite(SOILPOWER, LOW);
    return return_value;
}


void setup() 
{
  Serial.begin(9600);   

  pinMode(SOILPOWER, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(SOILPOWER, LOW);

  lcd.begin(16, 2);
  dht.begin();

}

void loop() 
{
  delay(10000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int moisture = readSoil();


  Serial.print( "T = ");
  Serial.print( temperature, 1 );
  Serial.print( " deg. C, H = " );
  Serial.print( humidity, 1 );
  Serial.print( "%, M = ");
  Serial.println(moisture);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperature, 0);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("M:");
  lcd.print(map(moisture,0,900,0,100));
  lcd.print("%");
}