#include "pitches.h"

int sensorPin = 13;
int speakerPin = 8;
bool  playedFirstHalf= false;
int timer = 0;

int firstHalf[] = {NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_A4};
int secondHalf[] = {NOTE_D4, NOTE_E4, NOTE_D4, NOTE_CS4, NOTE_A3};
int firstDuration[] = {8,8,8,4,4};
int secondDuration[] = {4,8,8,4,4};

void setup() 
{
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{ 
  if(digitalRead(sensorPin) == HIGH && 
     timer >= 5)
     {
       Serial.println("Someone's here!");
       timer = 0;
       if(!playedFirstHalf)
       {
         pony(firstHalf, firstDuration);
         playedFirstHalf = true;
         Serial.println("Playing first part");
       }
       else
       {
         pony(secondHalf, secondDuration);
         playedFirstHalf = false;
         Serial.println("Playing second part");
       }
       delay(1000);
     }
  else
  {
    timer++;
    delay(1000);
  }
}

void pony(int melody[], int noteDurations[])
{
  for (int thisNote = 0; thisNote < 5; thisNote++) 
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
   } 
}
