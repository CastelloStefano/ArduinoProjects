/********************************
* name:I2C LCD1602
* function:You should now see your I2C LCD1602 display the flowing characters: "SunFounder" and "hello, world".
********************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com
/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>


dht DHT;

#define DHT11_PIN 7
int i;

/**********************************************************/
LiquidCrystal_I2C lcd(0x3F,16,2); // set the LCD address to 0x3f for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
  Serial.begin(9600);
  lcd.init(); //initialize the lcd
  //lcd.begin(16,2);
  lcd.backlight(); //open the backlight 
  lcd.setCursor(0,0);
  pinMode(12, INPUT); // wata
  lcd.print("Ciao!");
  lcd.noBacklight();
  //i = 0;
}
/*********************************************************/
void loop() 
{
  //int value = analogRead(0); // get adc 0 value
  int motion = digitalRead(12);
  //i++;
  if(motion==HIGH){
    lcd.backlight();
  }else{
    lcd.noBacklight();
  }
  int chk = DHT.read11(DHT11_PIN);
  delay(600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Umid: ");
  lcd.print(DHT.humidity);
  lcd.print(" %  ");
  //lcd.print(value);
  //delay(100);
  //digitalWrite(12,HIGH);
   //wait for 2ms 
  //delay(300);
  //digitalWrite(12,LOW);
 
  delay(600); //wait for 2ms
}
/************************************************************/
