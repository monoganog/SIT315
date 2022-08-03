// Make an LED light up when motion is detected

// Setup of pins
const uint8_t PIR_PIN = 2;
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

// Ataching an interupt that checks for a change on our PIR pin then will call
// interrupt on a change
attachInterrupt(digitalPinToInterrupt(PIR_PIN),interrupt, CHANGE);

}
void loop()
{  


}

void interrupt(){
  Serial.print("\nInterupt called!");
  
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
}
