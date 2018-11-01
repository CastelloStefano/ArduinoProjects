#include <Servo.h> // include la Libreria Servo.h
 
Servo myservo;  // crea l’oggetto di tipo Servo, myservo sarà l’oggetto su cui opererai 
               
 
int pos = 0;    // inizializza una variabile di tipo intero pos il cui valore sarà la posizione da impartire al servo
 
void setup() 
{ 
  myservo.attach(6);
  delay(15);   // lega l’oggetto myservo al pin a cui abbiamo collegato il nostro servo, in questo caso il pin 8
} 
 
 
void loop() 
{                           
    myservo.write(3);               
    delay(15);   
}
