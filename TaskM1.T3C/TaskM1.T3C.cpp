// Make an LED light up when motion is detected

// Setup of pins
const uint8_t PIR_PIN = 2;
const uint8_t IRS_PIN = 3;
const uint8_t LED_PIN = 13;
const uint8_t PIEZO_PIN = 9;

// bool to store alarm state
bool alarmActivated = false;

//Setup to be Ran once to initialise the Button and LED
void setup()
{
  // Set Piezo as an output
  pinMode(PIEZO_PIN, OUTPUT);
  
  // initialise Infrared sensor as an input with the internal pull-up resistor enabled
  pinMode(IRS_PIN, INPUT_PULLUP);
  // initialise PIR sensor as an input with the internal pull-up resistor enabled
  pinMode(PIR_PIN, INPUT_PULLUP);
  //Setting the PinMode of the LED pin to be output
  pinMode(LED_PIN, OUTPUT);
  // Set Piezo as an output
  pinMode(PIEZO_PIN, OUTPUT);
  
  //Begin serial on port 9600
  Serial.begin(9600);
  
  // Setup of interupts
  attachInterrupt(digitalPinToInterrupt(PIR_PIN),motionInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(IRS_PIN),infraredInterrupt, CHANGE);
  
}
void loop()
{  
  if(alarmActivated)
  {
    // Sound the alarm!
  	tone(PIEZO_PIN, 3000, 50); // Send 100 Hz sound signal
  	delay(200);       
  }
}

// Method for the motion sensor interupt
void motionInterrupt(){
  
  Serial.println("Motion Interupt called!");
  
  // read pin result
  int PIRReadResult = digitalRead(PIR_PIN);
  // if the was motion detected and also alarm isnt currently activated
  if(PIRReadResult == HIGH && alarmActivated==false)
  {
    
    // turning on alarm and LED
    Serial.println("Activating Alarm");
    alarmActivated = true;
    digitalWrite(LED_PIN,HIGH);
  }
}

// Method for the infrared sensor interupt
void infraredInterrupt(){
  
  // Turn off LED
  digitalWrite(LED_PIN,LOW);
    
  // If alarm is active then turn it off
  if(alarmActivated)
  {
    Serial.println("Disabling Alarm");
    alarmActivated = false;
  }
}