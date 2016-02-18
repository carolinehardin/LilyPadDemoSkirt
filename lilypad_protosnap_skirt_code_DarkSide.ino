
#include "pitchesVader.h"
/* ProtoSnap Skirt Code
  by: Caroline D Hardin
  date: 1/1/2016
  license: Creative Commons Attribution-Share-alike v3.0 CC BY-SA 3.0
  http://creativecommons.org/licenses/by-sa/3.0/

  During testing there are 3 values you can adjust to make it easier on you:
  howBrightTheLights, darknessThreshold, BPM
  
*/

/* Pin Definitions */
// LEDs: white LEDs are connected to 5, 6, A2
  // note that A2 as a LilyPad Arduino analog pin won't fade, it can only do on or off
int ledPins[] = {5,6,A2};
int redLED = 11;
int blueLED = 10;
int greenLED = 9;
int colorLEDpins[] = {redLED, blueLED, greenLED};
int ledCount = sizeof(ledPins)/sizeof(int); //currently is 3

//MUSIC pins
int buzzerP = A3;
#define BPM 150   // Higher is faster. Imperial March plays at 150 

//LIGHT SENSOR
int lightSensorPin = A4;
int howBrightTheLights = 255; //set to lower while testing, 255 while showing 
int lightLevel;
int ambientLight;
float darknessThreshold = .7; //it's dark if it's 70% of ambient. Set lower for less sensitivity, higher for more
int twinklePin = 0; //Which pin in the LED array is currently twinkling
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int buttonPin = A5;

void setup()
{
  Serial.begin(9600);  // We'll output some information over serial for testing

  //Send power to the button pin. It'll connect to the buzzer when pressed
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  
  //initialize the light sensor 
  pinMode(lightSensorPin, INPUT);

  //find ambient light level by taking 50 samples and getting the average
  int totalLightSample = 0;
  for (int i=0; i<50; i++){
    totalLightSample = totalLightSample + analogRead(lightSensorPin);
  }
  ambientLight = totalLightSample / 50;
  Serial.println(ambientLight);
 
  //initialize the buzzer 
  pinMode(buzzerP, OUTPUT); 

  //test the buzzer
  for(int r=0;r<3;r++)
  { 
    for(int c=1000;c>340;c--)
    {
      tone(buzzerP, c);
    }
    for(int d=340;d<1000;d++)
    {
      tone(buzzerP, d);
    }
  }
  
  //turn off the buzzer
  noTone(buzzerP);

  
  //STARTUP LED SEQUENCE
  for(int i=0; i<ledCount; i++)    	  // blink the white LEDs (first 3 LEDs in ledPins array)
  {                         	
    pinMode(ledPins[i], OUTPUT); // set pin as output
    digitalWrite(ledPins[i], HIGH); // turn LED on
    delay(250);                	 // wait for a quarter second
    digitalWrite(ledPins[i], LOW); // turn LED off
  }	
  
    //RGB needs to be set as output
    pinMode(redLED, OUTPUT);   // set the pin as an output 
    pinMode(blueLED, OUTPUT);   // set the pin as an output 
    pinMode(greenLED, OUTPUT);   // set the pin as an output 
    
    //RGB needs to be set HIGH to turn it off
    digitalWrite(redLED, HIGH); // turn the RGB LED off
    digitalWrite(blueLED, HIGH); // turn the RGB LED off
    digitalWrite(greenLED, HIGH); // turn the RGB LED off
     
    digitalWrite(redLED, LOW); // turn RGB LED on
    delay(250);  // wait a quarter second
    digitalWrite(redLED, HIGH); // turn the RGB LED off
    
    digitalWrite(blueLED, LOW); // turn RGB LED on
    delay(250);  // wait a quarter second
    digitalWrite(blueLED, HIGH); // turn the RGB LED off
    
    digitalWrite(greenLED, LOW); // turn RGB LED on
    delay(250);  // wait a quarter second
    digitalWrite(greenLED, HIGH); // turn the RGB LED off
    
}

void loop()
{
  //check the light levels
  lightLevel = analogRead(lightSensorPin);
  Serial.print("  Light=");
  Serial.println(lightLevel); 
  
    //if it's darker than the threshold
    if(lightLevel < (ambientLight * darknessThreshold)){
     
      //turn on all leds
      for(int i=0;i<ledCount;i++)
      {
        digitalWrite(ledPins[i], HIGH);  
      }

     //play the Imperial March
     playSong();
     
     //turn the leds off 
      for(int i=0;i<ledCount;i++)
      {
        digitalWrite(ledPins[i], LOW);
      } 
     
    
    }
    else{
    //twinkle while you wait

      //pick a random led to affect
      twinklePin = rand()%ledCount;
  
     //for 10 times adjust the light level
      for (int j=0; j< 10; j++){
        
        //set the brightness
        brightness = brightness + fadeAmount;
        if (brightness == 0 || brightness == howBrightTheLights) {
          fadeAmount = -fadeAmount ;
        }
       
        //twinkle!
        analogWrite(ledPins[twinklePin], brightness); 
        delay(50);
        
      }

      //randomly turn on one of the RGB colors
      twinklePin = rand()%ledCount;
      digitalWrite(colorLEDpins[twinklePin], LOW);

      delay(50);
      
      //randomly turn off one of the colors
      twinklePin = rand()%ledCount;
      digitalWrite(colorLEDpins[twinklePin], HIGH);
    }
 
 }
  
void playSong(){
 //tone(pin, note, duration)
    tone(buzzerP,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzzerP,LA3,Q);
    delay(1+Q);
    tone(buzzerP,LA3,Q);
    delay(1+Q);
    tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    
    tone(buzzerP,LA3,Q);
    delay(1+Q);
    tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,LA3,H);
    delay(1+H);
    
    tone(buzzerP,E4,Q); 
    delay(1+Q); 
    tone(buzzerP,E4,Q);
    delay(1+Q);
    tone(buzzerP,E4,Q);
    delay(1+Q);
    tone(buzzerP,F4,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    
    tone(buzzerP,Ab3,Q);
    delay(1+Q);
    tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,LA3,H);
    delay(1+H);
    
    tone(buzzerP,LA4,Q);
    delay(1+Q);
    tone(buzzerP,LA3,E+S);
    delay(1+E+S);
    tone(buzzerP,LA3,S);
    delay(1+S);
    tone(buzzerP,LA4,Q);
    delay(1+Q);
    tone(buzzerP,Ab4,E+S);
    delay(1+E+S);
    tone(buzzerP,G4,S);
    delay(1+S);
    
    tone(buzzerP,Gb4,S);
    delay(1+S);
    tone(buzzerP,E4,S);
    delay(1+S);
    tone(buzzerP,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(buzzerP,Bb3,E);
    delay(1+E);
    tone(buzzerP,Eb4,Q);
    delay(1+Q);
    tone(buzzerP,D4,E+S);
    delay(1+E+S);
    tone(buzzerP,Db4,S);
    delay(1+S);
    
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,B3,S);
    delay(1+S);
    tone(buzzerP,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(buzzerP,F3,E);
    delay(1+E);
    tone(buzzerP,Ab3,Q);
    delay(1+Q);
    tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,LA3,S);
    delay(1+S);
    
    tone(buzzerP,C4,Q);
    delay(1+Q);
     tone(buzzerP,LA3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,E4,H);
    delay(1+H);
    
     tone(buzzerP,LA4,Q);
    delay(1+Q);
    tone(buzzerP,LA3,E+S);
    delay(1+E+S);
    tone(buzzerP,LA3,S);
    delay(1+S);
    tone(buzzerP,LA4,Q);
    delay(1+Q);
    tone(buzzerP,Ab4,E+S);
    delay(1+E+S);
    tone(buzzerP,G4,S);
    delay(1+S);
    
    tone(buzzerP,Gb4,S);
    delay(1+S);
    tone(buzzerP,E4,S);
    delay(1+S);
    tone(buzzerP,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(buzzerP,Bb3,E);
    delay(1+E);
    tone(buzzerP,Eb4,Q);
    delay(1+Q);
    tone(buzzerP,D4,E+S);
    delay(1+E+S);
    tone(buzzerP,Db4,S);
    delay(1+S);
    
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,B3,S);
    delay(1+S);
    tone(buzzerP,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(buzzerP,F3,E);
    delay(1+E);
    tone(buzzerP,Ab3,Q);
    delay(1+Q);
    tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    
    tone(buzzerP,LA3,Q);
    delay(1+Q);
     tone(buzzerP,F3,E+S);
    delay(1+E+S);
    tone(buzzerP,C4,S);
    delay(1+S);
    tone(buzzerP,LA3,H);
    delay(1+H);
    
    delay(2*H);

    noTone(buzzerP);
 
 }
