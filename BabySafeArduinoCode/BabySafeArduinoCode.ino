#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#include <dht11.h>

#define ID  "5853eba676254208c0638ff6"    // Sıcaklık
#define ID2  "5853ebc976254208c0639109"   // Nem
#define ID3  "58552e8a7625425970ecf0de"   // Gaz
#define ID4  "5855402e762542596fd9d349"   // Hareket
#define ID5  "585e557a76254273e64ce18c"   // Ses

#define TOKEN  "3kPo3rpXvaolxlLnsGBlBMTxxo2Btz"   //  Ubidots TOKEN
#define dataPIN 3 // DHT11PIN olarak Dijital 3"yi belirliyoruz.

dht11 DHT11;

int pirPin = 2;     // PIR için Digital 2 
const int gasPin = A0;    // Gaz sensö0rü için Analog A0
int SoundPin = A1;      // Ses sensörü Analog A1
const int esikSound = 55, esikGas = 150;

float oncekiTemp, oncekiGas, gasValue, gasValue2, soundValue2, t;
int oncekiPir, pirValue, oncekiSound, soundValue;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 19);

Ubidots client(TOKEN);

void setup(){

    Serial.begin(9600);
   
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      Ethernet.begin(mac, ip);
    }
    //delay(1000);
}
void loop(){    
     
    soundValue = analogRead(SoundPin);

    if(soundValue > esikSound){ 
      oncekiSound = soundValue2;   
      soundValue = 1;      
      soundValue2 = soundValue;
      if(oncekiSound != soundValue)
        client.add(ID5, soundValue);
    } else {
      oncekiSound = soundValue2;   
      soundValue = 0;      
      soundValue2 = soundValue;
      if(oncekiSound != soundValue)
        client.add(ID5, soundValue);
    }
    
    gasValue = analogRead(gasPin);
    if( gasValue > esikGas){
      oncekiGas = gasValue2;
      gasValue = 1;
      gasValue2 = gasValue;        
      if(oncekiGas != gasValue)
        client.add(ID3, gasValue);
          
    } else {        
      oncekiGas = gasValue2;
      gasValue = 0;
      gasValue2 = gasValue;        
      if(oncekiGas != gasValue)
        client.add(ID3, gasValue);
    }

    if( DHT11.read(dataPIN) == 0 ){
 
      Serial.print("Sicaklik (Celcius): ");
      Serial.println((float)DHT11.temperature, dataPIN);
    }

    oncekiPir = pirValue;
    pirValue = digitalRead(pirPin);
    if(oncekiPir != pirValue){ 
      client.add(ID4, pirValue);
    }

    oncekiTemp = t;
    t = DHT11.temperature ;

    if(oncekiTemp != t){
      client.add(ID, t);
    }

    client.sendAll();
    
}
