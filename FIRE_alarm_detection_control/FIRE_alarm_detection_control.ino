#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define relayPin 10
#define smokeA0 9

// Initialize DHT
DHT dht = DHT(DHTPIN, DHTTYPE);

// Init value for smoke sensor
int value = 0;
int prev_value = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.println("Gas sensor is warming up...");
  delay(10000);
  Serial.println("Temperature sensor ready...");
  
  dht.begin();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = digitalRead(smokeA0);

  if (!value) {
//  Open the relay connected to AC
    digitalWrite(relayPin, HIGH);
    
//  Sound the alarm, trigger relay to SIREN
//  Whenever smoke is detected, sound the alarm then wait check the temperature
    while(true) {
      float temp = dht.readTemperature();
      Serial.println(temp);

      if (temp >= 40) {
        Serial.println("Send message to bfp...");
        break;
      }
//      if button is pressed
//        reset arduino      
      delay(100);  
    }
    
    delay(200);
  }

//  if (prev_value != value) {
//    digitalWrite(relayPin, LOW);    
//    prev_value = value;
//    delay(200);
//  }

  Serial.print("Sensor value: ");
  Serial.println(value);
  
  delay(1000);
}
