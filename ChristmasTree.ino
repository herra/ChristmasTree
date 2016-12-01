#include "Arduino.h"

int blueR2 = A1;
int yellowR2 = A2;
int blueR1 = A3;

int groundLevel1 = 4;
int groundLevel2 = 5;
int groundLevel3 = 6;

int whiteR3 = 3;
int redR1 = 7;
int redR2 = 8;
int greenR1 = 9;

int blueLevel = 130;
int yellowLevel = 130;
int redLevel = 130;
int whiteLevel = 150;
int greenLevel = 120;

int buzzerPin = A0;
int buzzerGround = 13;
int flagPlaySong = 1;

struct Song {
  int tempo;
  int length;
  char* notes;
  int* duration;
};
Song bgChristmasSong;

// r = Fis = 739.99 Hz
char notesName[] = { 'c', 'd', 'e', 'f', 'r', 'g', 'a', 'h', 'C', 'D', 'E', 'F' };
int tones[] = { 523, 587, 659, 698, 740, 783, 880, 987, 1046, 1174, 1318, 1396 };


void spiral(int interval);
void lightAll(int interval);
void stopAll(int interval);
void blink(int interval);
void lightRow(int interval, int row);
void playSong(Song* song);

void setup() {
  pinMode(blueR1, OUTPUT);
  pinMode(yellowR2, OUTPUT);
  pinMode(blueR2, OUTPUT);

  pinMode(groundLevel1, OUTPUT);
  pinMode(groundLevel2, OUTPUT);
  pinMode(groundLevel3, OUTPUT);
  pinMode(buzzerGround, OUTPUT);
  digitalWrite(groundLevel1, LOW);
  digitalWrite(groundLevel2, LOW);
  digitalWrite(groundLevel3, LOW);
  digitalWrite(buzzerGround, LOW);


  String notes = "gggCgfedegggCgfededdefdeefgChagefedcddefdeefgChagefedc";
  int bgChristmasSongDurations [] = {1,1,1, 2,1, 1,1,1, 3, 1,1,1, 2,1, 1,1,1, 3, 1,1,1, 2,1, 1,1,1, 3, 1,1,1, 2,1, 1,1,1, 3, 1,1,1, 2,1, 1,1,1, 3, 1,1,1, 2,1, 1,1,1, 3 };

  bgChristmasSong.length = notes.length() + 1;
  bgChristmasSong.notes = (char*)malloc(bgChristmasSong.length);
  bgChristmasSong.duration = (int*)malloc(bgChristmasSong.length * sizeof(int));
  bgChristmasSong.tempo = 265;
}

void loop() {
  
  spiral(800);
  stopAll(0);
//  if (flagPlaySong == 1) {
//    playSong(&bgChristmasSong);
//    flagPlaySong == 0;
//  }

  stopAll(2000);
  lightAll(1000);
  stopAll(2000);

  blink(400);

  stopAll(200);
  lightRow(1000, 1);
  lightRow(1000, 2);
  lightRow(1000, 3);
  stopAll(0);
  lightRow(1000, 3);
  lightRow(1000, 2);
  lightRow(1000, 1); 
  stopAll(2000);

  
}

void spiral(int interval) {
  analogWrite(redR1, redLevel);
  delay(interval);
  analogWrite(greenR1, greenLevel);
  delay(interval);
  analogWrite(blueR1, blueLevel);
  delay(interval);
  analogWrite(redR2, redLevel);
  delay(interval);
  analogWrite(blueR2, blueLevel);
  delay(interval);
  analogWrite(yellowR2, yellowLevel);
  delay(interval);
  analogWrite(whiteR3, whiteLevel);
  delay(interval);
}

void blink(int interval) {
  analogWrite(redR1, redLevel);
  delay(interval);
  analogWrite(blueR2, blueLevel);
  delay(interval);

  stopAll(interval);
  
  analogWrite(greenR1, greenLevel);
  delay(interval);
  analogWrite(redR2, redLevel);
  delay(interval);

  stopAll(interval);

  analogWrite(blueR1, blueLevel);
  delay(interval);
  analogWrite(yellowR2, yellowLevel);
  delay(interval);
  
  stopAll(interval);
  
  analogWrite(whiteR3, whiteLevel);
  delay(interval);
}

void lightRow(int interval, int row) {
  if (row == 1) {
    analogWrite(redR1, redLevel);
    analogWrite(greenR1, greenLevel);
    analogWrite(blueR1, blueLevel);
  }

  if (row == 2) {
    analogWrite(redR2, redLevel);
    analogWrite(blueR2, blueLevel);
    analogWrite(yellowR2, yellowLevel);
  }

  if (row == 3) {
    analogWrite(whiteR3, whiteLevel);
  }
  delay(interval);
}

void lightAll(int interval) {
  analogWrite(redR1, redLevel);
  analogWrite(greenR1, greenLevel);
  analogWrite(blueR1, blueLevel);
  analogWrite(redR2, redLevel);
  analogWrite(blueR2, blueLevel);
  analogWrite(yellowR2, yellowLevel);
  analogWrite(whiteR3, whiteLevel);
  delay(interval);  
}

void stopAll(int interval) {
  digitalWrite(redR1, LOW);
  digitalWrite(greenR1, LOW);
  analogWrite(blueR1, 0);
  digitalWrite(redR2, LOW);
  analogWrite(blueR2, 0);
  analogWrite(yellowR2, 0);
  digitalWrite(whiteR3, LOW);
  delay(interval);  
}

void playSong(Song* song) {  
  for (int j = 0; j < song->length - 1; j++) {
    int toneDuration = song->duration[j] * song->tempo;
    char note = song->notes[j];
    for (int i = 0; i < sizeof(tones); i++) {    
      if (note == notesName[i]) {      
        tone(buzzerPin, tones[i], toneDuration);
      }
    }
    
    delay(toneDuration);
  }
}

