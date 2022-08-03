// Make an LED light up when motion is detected

// Setup of pins
const uint8_t MOTIONSENSOR_PIN = 12;
const uint8_t LED_PIN = 13;

bool motionDetected = false;

//Setup to be Ran once to initialise the Button and LED
void setup()
{
// initialise PIR sensor as an input with the internal pull-up resistor enabled
pinMode(PIR_PIN, INPUT_PULLUP);
//Setting the PinMode of the LED pin to be output
pinMode(LED_PIN, OUTPUT);
//Begin serial on port 9600
Serial.begin(9600);
}
void loop()
{  
  // Read the state of the PIR Sensor
  int PIRReadResult = digitalRead(PIR_PIN);
  if(PIRReadResult == HIGH)
  {
    // Motion detected
    Serial.print("\nMotion detected! \nLighting up LED");
    digitalWrite(LED_PIN,HIGH);
    
  }else{
    // No motion detected
    Serial.print("\nNo motion detected! \nTurning off LED");
   digitalWrite(LED_PIN, LOW);
  }
  // Wait 50 milliseconds before looping again
  delay(50); 
}