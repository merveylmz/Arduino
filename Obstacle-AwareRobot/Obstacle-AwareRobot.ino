#include <AFMotor.h>
#include <NewPing.h>

#define trigPin 12 // Trigger Pini (Ses gönderme)
#define echoPin 11 // Echo Pini (Yansıyan ses algılama)

long microsaniyeSure, cmMesafe; // Mesafe hesabında kullanılan değişkenler

AF_DCMotor Motor1(1);
AF_DCMotor Motor2(3);
AF_DCMotor Motor3(2);
AF_DCMotor Motor4(4);

long mesafeOlcumu()
{
  digitalWrite(trigPin, LOW); // Hoparlör 2ms sessiz
  delayMicroseconds(5); 
  digitalWrite(trigPin, HIGH); // Hoparlör 10ms sesli
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); // Hoparlör sessiz

  microsaniyeSure = pulseIn(echoPin, HIGH,  11600); // Mikrofonu dinle, yansıma süresini microsaniyeSure değişkenine al
  cmMesafe = microsaniyeSure/29.1/2; // microsaniyeSure'dan cm olarak mesafeyi hesapla
 
 /* Serial.print(cmMesafe); //Mesafe bilgisi
  Serial.println(" cm"); // Birim değeri */

  return cmMesafe;
}
void ileri()
{
    Serial.print("İleri");
    Motor1.setSpeed(255);
    Motor2.setSpeed(255);
    Motor3.setSpeed(255);
    Motor4.setSpeed(255);
   
    Motor1.run(FORWARD);
    Motor2.run(FORWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD);  
}
void solaDon()
{
    Motor3.setSpeed(0);   //sola don
    Motor1.setSpeed(0);
    Motor3.run(BRAKE);  
    Motor1.run(BRAKE); 

    Motor2.setSpeed(255);
    Motor4.setSpeed(255);    
    Motor2.run(FORWARD);
    Motor4.run(FORWARD);   
    delay(1750);    
}
void geri()
{
    Motor1.setSpeed(255);
    Motor2.setSpeed(255);
    Motor3.setSpeed(255);
    Motor4.setSpeed(255);
    
    Motor1.run(BACKWARD);
    Motor2.run(BACKWARD);
    Motor3.run(BACKWARD);
    Motor4.run(BACKWARD);
    delay(700);
}
void dur()
{
    Motor1.setSpeed(0);
    Motor2.setSpeed(0);
    Motor3.setSpeed(0);
    Motor4.setSpeed(0);
   
    Motor1.run(BRAKE);
    Motor2.run(BRAKE);
    Motor3.run(BRAKE);
    Motor4.run(BRAKE);  
    delay(500);    
}

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // Ses gönderme pin türünü çıkış olarak ayarla
  pinMode(echoPin, INPUT);  // Yansıyan ses algılama pin türünü giriş olarak ayarla
}
void loop()
{   
  while( mesafeOlcumu() > 10 || mesafeOlcumu() == 0 )
  { 
    ileri();
    delay(50);         
  }
  dur();
  geri();
  solaDon();
  dur(); 

}
