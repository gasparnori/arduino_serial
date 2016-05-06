//input button
int btn = 2;

//LED that indicates the state of our system: Slowly blinking when waiting for the button, permanently ON when communicating
int blinkingled = 9;

//this is the LED that we are going to toggle from the computer
int mainled = 8;

//a variable to define the current state of the system
int systemstate = 0;

void setup() {
  //defining pin modes
  pinMode(btn, INPUT);
  pinMode(blinkingled, OUTPUT);
  pinMode(mainled, OUTPUT);

  //attaching an interrupt to the input pin: the btn_ISR function will be called each time when the button is LOW
  attachInterrupt(digitalPinToInterrupt(btn), btn_ISR, LOW);

  //defining default values for the outputs
  digitalWrite(blinkingled, LOW);
  digitalWrite(mainled, LOW);

  // starting serial communication with the baud rate 9600 bits/second
  Serial.begin(9600);
  Serial.println("hello!");
}
void loop() {
  //waiting for the button to be pushed: slow blinking
  if (systemstate == 0) {
    digitalWrite(blinkingled, HIGH);
    delay(500);
    digitalWrite(blinkingled, LOW);
    delay(500);
  }
  //sending out the message on the Serial line
  if (systemstate == 1) {
    digitalWrite(blinkingled, HIGH);
    Serial.println("ON or OFF?");
    systemstate = 2;
  }
  //receiving the answer
  if (systemstate == 2) {
    //waiting until the answer is available
    while (!Serial.available()) {};
    //reading the answer to a string
    String a= Serial.readString();
    
    if (a=="off\r\n") {
      digitalWrite(mainled, LOW);
    };
    if (a=="on\r\n") {
      digitalWrite(mainled, HIGH);
    };
    
    //restarting again
    systemstate = 0;
  }
}

void btn_ISR() {
  //only reacts if the system is in state 0
  if (systemstate == 0) {
    systemstate = 1;
  }
}
