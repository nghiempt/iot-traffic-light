#include "TimerOne.h"

//a,b,c,d,e,f,g 
byte value[10][7] = {
{ 0, 0, 0, 0, 0, 0, 1 }, //0
{ 1, 0, 0, 1, 1, 1, 1 }, //1
{ 0, 0, 1, 0, 0, 1, 0 }, //2
{ 0, 0, 0, 0, 1, 1, 0 }, //3
{ 1, 0, 0, 1, 1, 0, 0 }, //4
{ 0, 1, 0, 0, 1, 0, 0 }, //5
{ 0, 1, 0, 0, 0, 0, 0 }, //6
{ 0, 0, 0, 1, 1, 1, 1 }, //7
{ 0, 0, 0, 0, 0, 0, 0 }, //8
{ 0, 0, 0, 0, 1, 0, 0 }  //9  
};

byte pin[8] = { 2, 3, 4, 5, 6, 7, 8, 9}; //{a,b,c,d,e,f,g,dp} 
byte digitPin[2] = { A0, A1 }; //segment 

int count = 1;
int red = 20;
int yellow = 6;
int green = 25;

void setup() {
    for (int i = 0; i < 7; i++) {
        pinMode(pin[i], OUTPUT);
    }
    pinMode(digitPin[0], OUTPUT);
    pinMode(digitPin[1], OUTPUT);
    digitalWrite(digitPin[0], LOW);
    digitalWrite(digitPin[1], LOW);
    
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    
    Timer1.initialize(1000000);
    Timer1.attachInterrupt(callback);
}

void callback() {
    count++;
}

void loop() { 
    if (count <= red) {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,HIGH);
        display(red-count+1);
    } else if (count > red && count <= (red + yellow)) {
        digitalWrite(13,LOW);
        digitalWrite(12,HIGH);
        digitalWrite(11,LOW);
        display(yellow-(count - red)+1);
    } else if (count > (red + yellow) && count <= (red + yellow + green)) {
        digitalWrite(13,HIGH);
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        display(green-(count - (red + yellow))+1);
    } else {
        count = 1;
    }
}

void display(int timeDisplay) {
  int unit = timeDisplay % 10;            // unit
  int dozen = (timeDisplay % 100) / 10;    // dozen
    for (int i = 0; i < 100; i++) {
        output(1, unit, 1);
        output(0, dozen, 1);
        delay(2);
    }
}

void clear(){
    for (int i = 0; i < 8; i++) {
        digitalWrite(pin[i], HIGH);
    }
}

void output(int d, int Number, int dp){
    clear();
    digitalWrite(digitPin[d], HIGH);
    for (int i = 0; i < 7; i++) {
        digitalWrite(pin[i], value[Number][i]);
    }
    digitalWrite(pin[7], dp);
    delayMicroseconds(1000);
    digitalWrite(digitPin[d], LOW);
}
