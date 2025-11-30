// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4
#define LED1 5
#define LED2 6
#define LED3 9
#define LED4 10
#define LED5 11
#define BRIGHTNESS 200
#define DIMMER_STEPS 5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {

  // Encoder Pins
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  
  //LED-MOFET Pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}

void loop() {

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter += DIMMER_STEPS;
      
    } else {
      // Encoder is rotating CW so increment
      counter -= DIMMER_STEPS;
      
    }

    if(counter < 0){
      counter = 0;
    }
    if(counter > BRIGHTNESS){
    counter = BRIGHTNESS;
    }
    
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  analogWrite(LED1, counter);
  analogWrite(LED2, counter);
  analogWrite(LED3, counter);
  analogWrite(LED4, counter);
  analogWrite(LED5, counter);
  Serial.println(counter);
  // Put in a slight delay to help debounce the reading
  delay(1);
}