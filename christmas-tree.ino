#define led1Pin 8          // LED output
#define led2Pin 6// LED output
#define led3Pin 10  //LED output
#define buzzerPin 1 //speaker output
#define  C     2100
 #define  D     1870 
 #define  E     1670
 #define  f     1580    // Does not seem to like capital F
 #define  G     1400 
 // Define a special note, 'R', to represent a rest
#define R 0

 // MELODY and TIMING  =======================================
 //  melody[] is an array of notes, accompanied by beats[],
 //  which sets each note's relative length (higher #, longer note)
 int melody[] = {E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
 E, E, E,R,
 E, E, E,R,
 E, G, C, D, E, R,
 f, f, f,f, f, E, E, E,  G,G, f, D, C,R };
 int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
 // Set overall tempo
 long tempo = 10000;
 // Set length of pause between notes
 int pause = 1000;
 // Loop variable to increase Rest length
 int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
 // Initialize core variables
 int tone_ = 0;
 int beat = 0;
 long duration  = 0;
 // PLAY TONE  ==============================================
 // Pulse the speaker to play a tone for a particular duration
 
void setup() {
  // put your setup code here, to run once:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonLed1Pin, INPUT_PULLUP);
  pinMode(buttonBuzzerPin, INPUT_PULLUP);
  //pinMode(ledButtonPin, OUTPUT)
  digitalWrite (led1Pin, LOW);
  digitalWrite (led2Pin, LOW);
  digitalWrite (led3Pin, LOW);
  //digitalWrite(buttonPin, LOW);
}

void loop() {
    for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = 50;

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    digitalWrite(led1Pin, HIGH);
    delayMicroseconds(pause);
    digitalWrite(led1Pin, LOW);
    }
}
void playTone() {
   long elapsed_time = 0;
   if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
     //  played less long than 'duration', pulse speaker HIGH and LOW
     while (elapsed_time < duration) {
       digitalWrite(buzzerPin,HIGH);
       digitalWrite(led2Pin, HIGH);
       
       digitalWrite(led3Pin, HIGH);
       delayMicroseconds(tone_ / 2);
       // DOWN
       digitalWrite(buzzerPin, LOW);
       digitalWrite(led2Pin, LOW);
       digitalWrite(led3Pin, LOW);
       delayMicroseconds(tone_ / 2);
       // Keep track of how long we pulsed
       elapsed_time += (tone_);
     }
   }
   else { // Rest beat; loop times delay
     for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
       delayMicroseconds(duration); 
     } 
   }                                
}


