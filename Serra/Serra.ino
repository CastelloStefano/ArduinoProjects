#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <dht.h>
#include <SPI.h>
#include <RFID.h>
Servo lock;
dht DHT;
#define DHT11_PIN 7 // pin 7 per umidità e temperatura
#define MSen 12 // pin 12 per il seonsore di movimento
#define MSen1 100 // pin ?? per il seonsore igrometro terra
#define Relay 5 // pin 5 per il relay
#define Motore 3 // pin 3 per la ventola
/*  Modulo tessera
PINOUT:
RC522 MODULE    Uno/Nano    
SDA             D10
SCK             D13
MOSI            D11
MISO            D12
IRQ             N/A
GND             GND
RST             D9
3.3V            3.3V
*/
#define SDA_DIO 10  // 53 per Arduino Mega
#define RESET_DIO 9
#define delayRead 1000 // Time of delay 
 
/* istanza della libreria RFID*/
RFID RC522(SDA_DIO, RESET_DIO); 
bool locked;
long Stetime = 0;
long ore = 0;
/**********************************************************/
LiquidCrystal_I2C lcd(0x3F,16,2); // indirizzo LCD A4 A5

void setup() {
  Serial.begin(9600);
  lcd.init(); //initialize the lcd
  pinMode(MSen, INPUT); // motion sensor
  pinMode(Relay, INPUT); // motion sensor
  pinMode(Motore, OUTPUT); // ventola 

  LcdTest();
  MotoreTest(50,150,0);

  
}

void loop() {
  if(locked)lcd.noBacklight(); // associare ad un bottone no alla tessera
  else lcd.backlight();
  // 1 Aquisizione dati
  int motion = digitalRead(MSen);
  int chk = DHT.read11(DHT11_PIN);
  int temp = DHT.temperature;
  int humidity = DHT.humidity;
  delay(5000);
  Stetime++;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Umid: ");
  lcd.print(DHT.humidity);
  lcd.print(" %");
  
  // 2 Comandi
  if(humidity>70)
  if(humidity>75)analogWrite(Motore,180);
  else analogWrite(Motore,100);
  else analogWrite(Motore,0);

  if(temp>35)openWindow();
  else closeWindow();


  /* IF umidità terreno 
   *  bagna piante 
   */
  // if(Stetime> oddio int ci fregherà tutti

  if(Stetime>720){
    Stetime=0;
    ore++;
  }
  if(ore>8){
    ore = 0;
    analogWrite(Relay,HIGH);
    delay(180000); // sono 3 min vero?
    analogWrite(Relay,LOW);
    
  }
/*
 * Così però abbiamo 5 sec o più ed il dispositivo si frizza,
 * ottimo per il risparmio batteria ed uso sporadico 
 * dell'entrata tramite chiave magentica
 * nel caso si volgia l'opposto sostituire i delay con un contatore
 * in modo da controllare lo stato del lettore carte ad ogni ciclo di
 * clock
 */

if (RC522.isCard())
  {
    // Viene letto il suo codice 
    RC522.readCardSerial();
    String codiceLetto ="";
    Serial.println("Codice delle tessera letto:");
    // Viene caricato il codice della tessera, all'interno di una Stringa
    for(byte i = 0; i <= 4; i++)
    {
      codiceLetto+= String (RC522.serNum[i],HEX);
      codiceLetto.toUpperCase();
    }
    if(codiceLetto.equals(""))
    if(locked) lock.write(10);
    else lock.write(150);
    locked = !locked;
    delay(2000);

    // accendere e spegnere l'lcd da qui
  }
}

void openWindow(){
  // serve una carrucola
  // poi attacchiamo il motore potente
}

void closeWindow(){
  // serve una carrucola
}

void LcdTest(){
   lcd.backlight(); //open the backlight 
  lcd.setCursor(0,0);
  lcd.print("Lcd ON!");
  delay(1000);
  lcd.noBacklight();
  lcd.clear();
}

void MotoreTest(int a, int b, int c){
  analogWrite(Motore,a);
  delay(1000);
  analogWrite(Motore,b);
  delay(1000);
  analogWrite(Motore,c);
  delay(1000);
}

void LockTest(){
  lock.write(20);
  delay(500);
  lock.write(150);
}
