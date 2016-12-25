//...http://www.hobbyist.co.nz/?q=documentations/wiring-up-dht11-temp-humidity-sensor-to-your-arduino
#include<dht.h>
#define dht_apin A0
dht DHT;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   delay(100);
   Serial.println("DHT_11 temperature and Humidity sensor:\n");
   delay(1000);  

}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_apin);
  Serial.print("Current Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("% Temperature: ");
  Serial.print(DHT.temperature);
  Serial.print("'C\n");
  delay(2000);

}
