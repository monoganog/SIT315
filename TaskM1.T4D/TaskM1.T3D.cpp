// Make an LED light up when motion is detected

// Setup of pins
const uint8_t PIR_PIN = 2;
const uint8_t IRS_PIN = 3;
const uint8_t LED_PIN = 12;

const uint8_t LED2_PIN = PB5;

const uint8_t PIEZO_PIN = 9;

// Counter value
const uint16_t tl_load = 0;
const uint16_t tl_comp = 31250;

bool alarmArmed = false;


// bool to store alarm state
bool alarmActivated = false;

//Setup to be Ran once to initialise the Button and LED
void setup()
{
  // Set the LED2 to be an Output
  DDRB |= (1 << LED2_PIN);
  
  // Reset timer control registry
  TCCR1A = 0;
   
  // Set the prescaler to 256 by setting the binary value to 100
  TCCR1B |= (1<<CS12);
  TCCR1B &= ~(1<<CS11);
  TCCR1B &= ~(1<<CS10);
  
  // Reset Timer1 and then set the compare value for the timer
  TCNT1 = tl_load;
  OCR1A = tl_comp;
  
  // Enable timer1 compare interupt
  TIMSK1 = (1<<OCIE1A);
  
  // Enable global interrupts
  sei();
  
  
  PCICR |= B00000100;
  
  PCMSK2 |= B00110000;
  
  
    
  // Setting button pins
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
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

// Timer interupt function to blink an LED
ISR(TIMER1_COMPA_vect){
  // Reset timer
  TCNT1 = tl_load;
  
  if(alarmArmed)
  {
  	// Blink LED
  	PORTB ^= (1 << LED2_PIN);
  	Serial.println("Waiting for movement");
  }
  else{
    // Make sure alarm is off
    PORTB &= ~(1 << LED2_PIN);
  }
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


// PCINT interupt function to read button input
ISR(PCINT2_vect)
{
  if(digitalRead(5))
  {
    Serial.println("Alarm is now ARMED... Dont move!");
    alarmArmed = true;
  }
}

// Method for the motion sensor interupt
void motionInterrupt(){
  
  Serial.println("Motion Interupt called");
  
  // read pin result
  int PIRReadResult = digitalRead(PIR_PIN);
  // if the was motion detected and also alarm isnt currently activated
  if(PIRReadResult == HIGH && alarmActivated==false && alarmArmed)
  {
    
    // turning on alarm and LED
    Serial.println("Activating Alarm");
    alarmActivated = true;
    digitalWrite(LED_PIN,HIGH);
  }
}

// Method for the infrared sensor interupt
void infraredInterrupt()
{  
  // If alarm is active then turn it off
  if(alarmActivated)
  {
    Serial.println("Disabling Alarm");
    alarmActivated = false;
    
    // Turn off LED
  	digitalWrite(LED_PIN,LOW);
  }
  
  if(alarmArmed)
  {
    // Un arm Alarm
    alarmArmed = false;
    Serial.println("Un Arming Alarm");
  }
}