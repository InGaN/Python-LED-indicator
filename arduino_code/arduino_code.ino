#include <Adafruit_NeoPixel.h>

char buffer [32];
boolean read_ready = false;
int counter = 0;
int red_value, green_value, blue_value;
int blink_speed = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);

void setup() {                
  Serial.begin(9600);
  pinMode(13, OUTPUT);     
  digitalWrite(13, LOW);
  strip.begin();
  strip.show();
}

void ParseLine() {
  char *key, *value, *i;    
  key = strtok_r(buffer, "=", &i); 
  value = strtok_r(NULL, "=", &i);    
  
  switch(*key) {
    case 'r':
      if(atoi(value) < 256 && atoi(value) > -1) {
        red_value = atoi(value);
      }  
      break;
    case 'g':
      if(atoi(value) < 256 && atoi(value) > -1) {
        green_value = atoi(value);
      }  
      break;
    case 'b':
      if(atoi(value) < 256 && atoi(value) > -1) {
        blue_value = atoi(value);
      }  
      break;
    case 'a':
      if(atoi(value) < 1001 && atoi(value) > -1) {
        blink_speed = atoi(value);
      }  
      break;       
  }
  
  read_ready = false;
}

void loop() {  
  strip.setPixelColor(0, red_value, green_value, blue_value); 
  strip.show();   
  
//  if(blink_speed > 0) {
//    delay(blink_speed);
//    digitalWrite(13, LOW);    
//    delay(blink_speed);
//  }
  
  if(read_ready) {
    ParseLine();
  }
  else {
    while (Serial.available()) {
      char c = Serial.read();
      buffer[counter++] = c;
      if ((c == '\n') || (counter == sizeof(buffer)-1))
      {
          buffer[counter] = '\0';
          counter = 0;
          read_ready = true;
      }
    }
  }
}
