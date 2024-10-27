int pin[]= {2,3,4,5,6,9,10,11};
#define addbtt 13 //left
#define guessbtt 12 //right
int index =0;
int randomnum=0;
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

int Sym[] ={B00111111, //0
            B00110001, //Up
            B00111000};//Down

int now1, last1, buttonstate1;
long timer1;
int now2, last2, buttonstate2;
long timer2;



void setup(){
  Serial.begin(9600);
  for (int i=0; i<8; i++) {
    pinMode(pin[i], OUTPUT);
  }

}

void loop(){
  // 7 segment ----------------------------------------------------------------------------
  if (index >= 10) {
    index = 0;
  }
  if (Serial.available()) {
    int input = Serial.read()-'0';
    if (input < 10 && input >= 0) {
      index = input;
    }
  }
  for(int i = 0 ; i<8; i++){
    int bitset = bitRead(NO[index], i);
    digitalWrite(pin[i], !bitset);

  }
  
  //handle button----------------------------------------------------------------------------
  now1 = digitalRead(addbtt);
  if (now1 != last1) {
    timer1 = millis();
  }
  if(millis()- timer1 > 50){
    if (digitalRead(addbtt)!= buttonstate1) {
      buttonstate1 = digitalRead(addbtt);
      if (buttonstate1 == HIGH) {
        handle_add_button();
      }
    }
  }
  last1 = now1;
  now2 = digitalRead(guessbtt);
  if (now2 != last2) {
    timer2 = millis();
  }
  if(millis()- timer2 > 50){
    if (digitalRead(guessbtt)!= buttonstate2) {
      buttonstate2 = digitalRead(guessbtt);
      if (buttonstate2 == HIGH) {
        handle_guess_button();
      }
    }
  }
  last2 = now2;

  // random ----------------------------------------------------------------------------
  if(randomnum == 0){
    randomSeed(analogRead(A0));
    randomnum = random(10);
    Serial.print("random number is: ");
    Serial.println(randomnum);
  }
}

void handle_add_button(){
  index++;
}


void handle_guess_button(){
  if (index == randomnum) {
    randomnum=0;
    index = 0;
    Serial.println("Correct");
    for(int i =0; i<8; i++){
      int bitset = bitRead(Sym[0], i);
      digitalWrite(pin[i],!bitset);
    }
    delay(2000);
  }

  else if (index > randomnum){
    Serial.println("Too much");
    for(int i =0; i<8; i++){
      int bitset = bitRead(Sym[2], i);
      digitalWrite(pin[i],!bitset);
    }
    delay(2000);
  }

  else if (index < randomnum){
    Serial.println("Too few");
    for(int i =0; i<8; i++){
      int bitset = bitRead(Sym[1], i);
      digitalWrite(pin[i],!bitset);
    }
    delay(2000);
  }
}
