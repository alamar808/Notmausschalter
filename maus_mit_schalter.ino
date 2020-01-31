/*
  Der Not(ma)us-Schalter

  Ein Buzzer, welcher auf Druck diverse Jingles abspielt

  Schaltkreis:
  Verstärkerboard mit 8ohm Lautsprecher und Input an Digital Pin 9
  Button mit 10 kOhm Pulldown-Widerstand an Ditial Pin 2
  
Unter Verwendung von:

https://github.com/TMRh20/TMRpcm

*/

#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#define CHIP_SELECT_PIN  4
#define SPEAKER_PIN      9
#define buttonPin        2
int buttonState = 0; 
TMRpcm tmrpcm;
boolean goodToGo = false;

String wavs[] = {"maus.wav", "fail.wav", "drama.wav", "niete.wav", "mario.wav", "fail.wav", "duell.wav", "sesam.wav","drama.wav", "homer.wav", "prank.wav", "neindochoh.wav","mario.wav", "niete.wav", "fail.wav", "neindochoh.wav", "drama.wav", "mario.wav", "mario.wav",  "fail.wav", "niete.wav"};
uint8_t num_wavs = 21;
uint8_t wav_now = 0;

void setup( ) {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  tmrpcm.speakerPin = SPEAKER_PIN;
  tmrpcm.volume(6);
  randomSeed(analogRead(0)); 
  Serial.begin( 9600 );
  wav_now = random(0,21);
  Serial.println("num_wavs = " + num_wavs);
  if ( !SD.begin( CHIP_SELECT_PIN ) )
    Serial.println( "SD fail" );
}

void maus() {
    if (!tmrpcm.isPlaying()) {
      Serial.println("playing");
      tmrpcm.play( wavs[wav_now % num_wavs].c_str() );
      Serial.println(wavs[wav_now % num_wavs]);
      wav_now = random(0,21);
      delay( 5 );
      Serial.println("done");
    } else {
      Serial.println("gimme a moment");
    }
// }
}

void loop( ) {
 // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

 // check if the pushbutton is pressed. If it is, the buttonState is HIGH and the melody will be played:
  if (buttonState == HIGH) {
    Serial.println("HIGH");
    maus();
  } else {
    delay( 5 );
}
}
