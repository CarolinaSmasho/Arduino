int butt[] = {4,5,6,9,10};

void setup(){
  for (int i = 0; i<4; i++) {
   pinMode(i, INPUT);
  }
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  while(digitalRead(butt[4])== HIGH){
    tone(3, 261);
  }

  while(digitalRead(butt[3])== HIGH){
    tone(3, 294);
  }

  while(digitalRead(butt[2])== HIGH){
    tone(3, 330);
  }
  while(digitalRead(butt[1])== HIGH){
    tone(3, 349);
  }
  while(digitalRead(butt[0])== HIGH){
    tone(3, 392);
  }

  noTone(3);
}
