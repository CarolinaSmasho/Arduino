// North Light 
#define RedN 2
#define YellowN 3 
#define GreenN 4

// East Light
#define RedE 8
#define YellowE 9
#define GreenE 10

// Walk Light
#define GreenW 6
#define RedW 7

#define  ButtonN 5
#define ButtonE 11
#define ButtonW 12

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define goW 4
#define dark1 5
#define bright1 6
#define dark2 7
#define bright2 8
#define dark3 9
#define bright3 10
#define lastdark 11

int currentState=0;
int input,input1,input2,input3;

struct state{
  char out;
  int wait;
  char next[8];
};
typedef struct state Stype;
Stype FSM[]= {
                {B10001100, 5000, {goN, waitN, waitN, waitN, goN, waitN, waitN, waitN}} , //goN
                {B10010100,2000,{goW, goW, goE, goE, goE, goW, goE, goE}} , //waitN
                {B10100001,5000,{goE, waitE, goE, waitE, waitE, waitE, waitE, waitE}} , //goE
                {B10100010,2000,{goW, goW, goN, goW, goN, goW, goN, goN}} , //waitE
                
                {B01100100,5000,{dark1, dark1, dark1, dark1, dark1, dark1, dark1, dark1}} , //goW
                {B00100100,500,{bright1, bright1, bright1, bright1, bright1, bright1, bright1, bright1}} , // dark1
                {B01100100,500,{dark2, dark2, dark2, dark2, dark2, dark2, dark2, dark2}} , //bright1
                {B00100100,500,{bright2, bright2, bright2, bright2, bright2, bright2, bright2, bright2}} , // dark2
                {B01100100,500,{dark3, dark3, dark3, dark3, dark3, dark3, dark3, dark3}} , //bright2
                {B00100100,500,{bright3, bright3, bright3, bright3, bright3, bright3, bright3, bright3}} , // dark3
                {B01100100,500,{lastdark, lastdark, lastdark, lastdark, lastdark, lastdark, lastdark, lastdark}} , //bright3
                {B00100100,500,{goN, goW, goE, goE, goN, goN, goN, goN}} , // lastdark
};



void setup()
{
  pinMode(RedN, OUTPUT);
  pinMode(YellowN, OUTPUT);
  pinMode(GreenN, OUTPUT);
  pinMode(ButtonN, INPUT);
  
  pinMode(RedE, OUTPUT);
  pinMode(YellowE, OUTPUT);
  pinMode(GreenE, OUTPUT);
  pinMode(ButtonE, INPUT);

  pinMode(RedW, OUTPUT);
  pinMode(GreenW, OUTPUT);
  pinMode(ButtonW, INPUT);
}

void loop()
{
  // Show Light
  digitalWrite(RedN, FSM[currentState].out & B00100000);
  digitalWrite(YellowN, FSM[currentState].out & B00010000);
  digitalWrite(GreenN, FSM[currentState].out & B00001000);

  digitalWrite(RedE, FSM[currentState].out & B00000100);
  digitalWrite(YellowE, FSM[currentState].out & B00000010);
  digitalWrite(GreenE, FSM[currentState].out & B00000001);

  digitalWrite(RedW, FSM[currentState].out & B10000000);
  digitalWrite(GreenW, FSM[currentState].out & B01000000);

  // Delay
  delay(FSM[currentState].wait);

  // Receive Input
  input1 = digitalRead(ButtonN);
  input2 = digitalRead(ButtonE);
  input3 = digitalRead(ButtonW);
  input = input1*4 + input2*2 + input3;

  // Change Current State
  currentState = FSM[currentState].next[input];
}
