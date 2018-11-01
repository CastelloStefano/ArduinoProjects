int relayPin = 3; 

void setup()
{
pinMode(relayPin, OUTPUT);
digitalWrite(relayPin, LOW);
}
void loop()
{
  
// turn the relay on (HIGH is the voltage level)

digitalWrite(relayPin, HIGH);
// wait for a second
delay (5000);
// turn the relay off by making the voltage LOW
digitalWrite(relayPin, LOW);
// wait for a second
delay (5000); }
