// #define led1 14
// #define led2 2
// #define led3 3
// #define led4 4
// #define led5 5
// #define led6 6

// #define button1 8
// #define button2 9
// #define button3 10
// #define button4 11
// #define button5 12
// #define button6 13

#define led1 8
#define led2 9
#define led3 10
#define led4 11
#define led5 12
#define led6 13

#define button1 2
#define button2 3
#define button3 4
#define button4 5
#define button5 6
#define button6 7

#define startPin 22
#define nextPin 23
#define finishPin 24

bool ledState1 = 0;
bool ledState2 = 0;
bool ledState3 = 0;
bool ledState4 = 0;
bool ledState5 = 0;
bool ledState6 = 0;


bool buttonState1;
bool buttonState2;
bool buttonState3;
bool buttonState4;
bool buttonState5;
bool buttonState6;

bool nextState;
bool wrongState = 0;
unsigned long startTime;
unsigned long finishTime;
const int playingTime = 1;  //minute

int shoot;
int goal;
int wrong;
bool pressed = 0;
bool buttonState = 0;
bool playGame;
int randomLed;
int oldRandomLed;
const int blinkingTime = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);

  pinMode(startPin, INPUT_PULLUP);
  pinMode(nextPin, INPUT_PULLUP);
  pinMode(finishPin, INPUT_PULLUP);
  randomSeed(analogRead(A3));
}

void loop() {
  if (keyPress() == 0 && playGame == 0) {
    startTime = millis();
    //ledOnAll();
    blinkAll(500);
  } else if (keyPress() == 1 && playGame == 0) {
    //ledOffAll();
    //blinkAll(200);
    //delay(1000);
    startTime = millis();
    playGame = 1;
    shoot = 0;
    goal = 0;
    wrong = 0;
  }
  if (playGame == 1) {
    pickNewLed();
  }
  finishTime = millis();
}

void pickNewLed() {
  ledStateAll();
  buttonStateAll();
  if (buttonState1 == 1 && buttonState2 == 1 && buttonState3 == 1 && buttonState4 == 1 && buttonState5 == 1 && buttonState6 == 1 && buttonState == 0 && playGame == 1) {
    buttonState = 1;
    randomLed = random(1, 6);
    while (randomLed == oldRandomLed) {
      randomLed = random(1, 6);
    }
    oldRandomLed = randomLed;
    ledOn(randomLed);
    shoot++;
    Serial.println("random");
  }

  if (ledState1 == 1 && buttonState1 == 0 || ledState2 == 1 && buttonState2 == 0 || ledState3 == 1 && buttonState3 == 0 || /*   */
      ledState4 == 1 && buttonState4 == 0 || ledState5 == 1 && buttonState5 == 0 || ledState6 == 1 && buttonState6 == 0) {
    ledOffAll();
    goal++;
    buttonState = 0;
    Serial.println("goalllllllllll");
  }
  if ((ledState1 == 1 && buttonState2 == 0) || (ledState1 == 1 && buttonState3 == 0) || (ledState1 == 1 && buttonState4 == 0) || (ledState1 == 1 && buttonState5 == 0) || (ledState1 == 1 && buttonState6 == 0) || /*   */
      (ledState2 == 1 && buttonState1 == 0) || (ledState2 == 1 && buttonState3 == 0) || (ledState2 == 1 && buttonState4 == 0) || (ledState2 == 1 && buttonState5 == 0) || (ledState2 == 1 && buttonState6 == 0) || /*   */
      (ledState3 == 1 && buttonState1 == 0) || (ledState3 == 1 && buttonState2 == 0) || (ledState3 == 1 && buttonState4 == 0) || (ledState3 == 1 && buttonState5 == 0) || (ledState3 == 1 && buttonState6 == 0) || /*   */
      (ledState4 == 1 && buttonState1 == 0) || (ledState4 == 1 && buttonState2 == 0) || (ledState4 == 1 && buttonState3 == 0) || (ledState4 == 1 && buttonState5 == 0) || (ledState4 == 1 && buttonState6 == 0) || /*   */
      (ledState5 == 1 && buttonState1 == 0) || (ledState5 == 1 && buttonState2 == 0) || (ledState5 == 1 && buttonState3 == 0) || (ledState5 == 1 && buttonState4 == 0) || (ledState5 == 1 && buttonState6 == 0) || /*   */
      (ledState6 == 1 && buttonState1 == 0) || (ledState6 == 1 && buttonState2 == 0) || (ledState6 == 1 && buttonState3 == 0) || (ledState6 == 1 && buttonState4 == 0) || (ledState6 == 1 && buttonState5 == 0)) {
    //ledOffAll();
    wrongState = 1;
    //buttonState = 0;
    //Serial.println("wrongPressed");
    ledOffAll();
    buttonState = 0;
  }
  //Serial.println(flag);
  //Serial.println("gggggggggg");
  if (wrongState == 1) {
    wrongState = 0;
    wrong++;
    Serial.println("wrong");
  }
  //Serial.println((finishTime - startTime) / 1000);
  if (((finishTime - startTime) / 1000) > 10) {
    ledOffAll();
    float total = wrong + goal;
    float accuracy = (goal / total) * 100;
    float goalHelp = goal;
    float reactionTime = 60 / (total);
    float score;
    Serial.print(goal);
    Serial.print("\t");
    Serial.print(wrong);
    Serial.print("\t");
    Serial.print(accuracy);
    Serial.print("\t");
    Serial.println(reactionTime, 3);
    // Serial.print("\t");
    // Serial.println(reactionTime, 3);
    playGame = 0;
    buttonState = 0;
    boomerang(20);
    boomerang(20);
    pressed = 0;
  }
  //delay(5);
}
void nothing() {}
boolean keyPress() {
  buttonStateAll();
  if (buttonState1 == 0 || buttonState2 == 0 || buttonState3 == 0 || buttonState4 == 0 || buttonState5 == 0 || buttonState6 == 0) {
    pressed = 1;
  }
  return pressed;
}

void ledOn(int randomLed) {
  if (randomLed == 1) {
    digitalWrite(led1, HIGH);
  } else if (randomLed == 2) {
    digitalWrite(led2, HIGH);
  } else if (randomLed == 3) {
    digitalWrite(led3, HIGH);
  } else if (randomLed == 4) {
    digitalWrite(led4, HIGH);
  } else if (randomLed == 5) {
    digitalWrite(led5, HIGH);
  } else if (randomLed == 6) {
    digitalWrite(led6, HIGH);
  }
}

void ledOff(int randomLed) {
  if (randomLed == 1) {
    digitalWrite(led1, LOW);
  } else if (randomLed == 2) {
    digitalWrite(led2, LOW);
  } else if (randomLed == 3) {
    digitalWrite(led3, LOW);
  } else if (randomLed == 4) {
    digitalWrite(led4, LOW);
  } else if (randomLed == 5) {
    digitalWrite(led5, LOW);
  } else if (randomLed == 6) {
    digitalWrite(led6, LOW);
  }
}

void ledOnAll() {
  ledOn(1);
  ledOn(2);
  ledOn(3);
  ledOn(4);
  ledOn(5);
  ledOn(6);
}

void ledOffAll() {
  ledOff(1);
  ledOff(2);
  ledOff(3);
  ledOff(4);
  ledOff(5);
  ledOff(6);
}

void blinkAll(int blinkTime) {
  ledOnAll();
  delay(blinkTime);
  ledOffAll();
  delay(blinkTime);
}

void blink(int randomLed, int blinkTime) {
  ledOn(randomLed);
  delay(blinkTime);
  ledOff(randomLed);
  delay(blinkTime);
}

void spin(int speed) {
  blink(1, speed);
  blink(2, speed);
  blink(3, speed);
  blink(4, speed);
  blink(5, speed);
  blink(5, speed);
}

void boomerang(int speed) {
  blink(1, speed);
  blink(2, speed);
  blink(3, speed);
  blink(4, speed);
  blink(5, speed);
  blink(6, speed);
  blink(5, speed);
  blink(4, speed);
  blink(3, speed);
  blink(2, speed);
  blink(1, speed);
}

void ledStateAll() {
  ledState1 = digitalRead(led1);
  ledState2 = digitalRead(led2);
  ledState3 = digitalRead(led3);
  ledState4 = digitalRead(led4);
  ledState5 = digitalRead(led5);
  ledState6 = digitalRead(led6);
}

void buttonStateAll() {
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  buttonState4 = digitalRead(button4);
  buttonState5 = digitalRead(button5);
  buttonState6 = digitalRead(button6);
}