/*How to use rain sensor.
  created by SriTu Tech team.
  Read the code below and use it for any of your creation
*/

#define Buzzerpin 2
void setup() {
  Serial.begin(9600);//enable serial monitor
  pinMode(4, OUTPUT);//define LED pin
}

void loop() {
  int value = analogRead(A3);//read value
  Serial.print("Value : ");
  Serial.println(value);

  if (value < 300) {//check condition
    digitalWrite(4, HIGH);
    digitalWrite(Buzzerpin,HIGH);
    Serial.print("Heavy rain  LED on ");
  } else {
    digitalWrite(4, LOW);
    digitalWrite(Buzzerpin,LOW);
  }
}
