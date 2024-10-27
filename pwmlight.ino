void setup(){
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(A0));
  analogWrite(3, analogRead(A0));
}
