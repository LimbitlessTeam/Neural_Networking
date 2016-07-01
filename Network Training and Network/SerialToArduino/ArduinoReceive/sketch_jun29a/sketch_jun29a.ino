char val;
#define LEDPIN 13


void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if(Serial.available())
  {
    val = Serial.read();
  }

  if(val == '1')
  {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

delay(10);
}
