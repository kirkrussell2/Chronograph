#include <Servo.h>
#include <LiquidCrystal.h>
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorAvg1 = 0;
int sensorAvg2 = 0;
int sensorAvg = 0;
long timet;
long gate2;
long gate1;
int pos = 0;

Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Object Speed: ");
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(6, OUTPUT);
  myservo.attach(13);
  Serial.begin(115200);
}


void loop()
{
  analogWrite(9,LOW);
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  sensorValue3 = analogRead(A2);
  sensorValue4 = analogRead(A3);
  sensorAvg1 = (sensorValue1+sensorValue2)/2;
  sensorAvg2 = (sensorValue3+sensorValue4)/2;
  sensorAvg = (sensorAvg1+sensorAvg2)/2;
  Serial.println(sensorAvg1);
  if (sensorAvg2 < 750)
   {   
    gate1 = millis();
    if (sensorAvg1 < 200)
      {    
      timet = millis() - gate1;
      lcd.setCursor(0, 1);
      lcd.print(.5/(gate1/1000UL));
      //delay(1000);
      lcd.print(" ");
      //activate buzzer to alert user it triggered
      digitalWrite(6,HIGH);
      delay(1000);
      //reset buzzer to off to not annoy the user
      digitalWrite(6,LOW);
      //if the object speed is less than 10 m/s set flag to pos 60
      if (timet <= 10)
      {
        myservo.write(60);
        delay(700);
        myservo.write(0);
      }
      //if the object speed is less than 10 m/s set flag to pos 120
      if (timet <= 12 && timet > 10)
      {
        myservo.write(120);
        delay(700);
        myservo.write(0);
      }
      //if the object speed is less than 10 m/s set flag to pos 180
      if (timet > 12)
      {
        myservo.write(180);
        delay(700);
        myservo.write(0);
      }
      }
    }
}
