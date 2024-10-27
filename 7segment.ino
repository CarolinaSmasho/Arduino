int NO1 = B00000110;
int NO[] = {B00111111, //0
            B00000110, //1
            B01011011,
            B01001111,
            B01100110,
            B01101101,
            B01111101, //6
            B00000111, 
            B01111111,
            B01101111};
int pin[]= {2,3,4,5,6,9,10,11};
int index= 0;

int reading,lastread,buttonstate=0;
int reading2,lastread2,buttonstate2=0;
long lasttime, lasttime2;

void setup(){
  Serial.begin(9600);
  for(int i = 0 ; i<8; i++)
  pinMode(pin[i], OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

}

void loop(){
  for(int i = 0 ; i<8; i++){
    int bitset = bitRead(NO[index], i);
    digitalWrite(pin[i],!bitset);
  }

  //check ปุ่มกด
  reading = digitalRead(12);
  if(reading!= lastread){
    lasttime =millis();
  }
  if(millis()- lasttime > 100){
    if (reading!= buttonstate){
      buttonstate=reading;
      if(buttonstate == HIGH){
        index++;
      }
    }
  }
  lastread = reading;

  //check ปุ่มกด2
  reading2 = digitalRead(13);
  if(reading2!= lastread2){
    lasttime2 =millis();
  }
  if(millis()- lasttime2 > 100){
    if (reading2!= buttonstate2){
      buttonstate2=reading2;
      if(buttonstate2 == HIGH){
        index--;
      }
    }
  }
  lastread2 = reading2;

  if (Serial.available()) {
    int input = Serial.read() - '0';
    if (input >= 0 && input <= 9) {
      index = input;
    }
  }
}


