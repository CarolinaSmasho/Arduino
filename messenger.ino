#include <SoftwareSerial.h>
String input = "";
SoftwareSerial mySerial(10,11);
void setup() {
    Serial.begin(4800);
    mySerial.begin(4800);
}

void loop() {
  if (mySerial.available()) { // รับ
    Serial.print((char)mySerial.read());
  }

  // ส่ง
  while(Serial.available()){
    char inChar = (char)Serial.read();
    input+=inChar;
    if(inChar=='\n'){
      mySerial.print("Him : ");
      mySerial.println(input);
      Serial.print("Me : ");
      Serial.println(input);
      input = "";

    }

  }

}
