// SWiM: Lab03
#include <LiquidCrystal.h>
#include <string.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

byte customChar[8] = {
  0b00000100,
  0b00001010,
  0b00000100,
  0b00011111,
  0b00000100,
  0b00000100,
  0b00001010,
  0b00010001
};

int pos[2] = {0, 0};

const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;

void setup() {
  Serial.begin(115200);
  Serial.println("Arduino ready!");

  LCD.begin(LCD_WIDTH, LCD_HEIGHT);
  LCD.createChar(1, customChar);
  LCD.clear();

  LCD.setCursor(pos[1], pos[0]);
  LCD.write("\1");
  LCD.setCursor(pos[1], pos[0]);
}

void moveCharacter() {
  LCD.write(" ");
  LCD.setCursor(pos[1], pos[0]);
  LCD.write("\1");
  LCD.setCursor(pos[1], pos[0]);
}

const int MAX_COMMAND_LENGTH = 10;
char readCommand[MAX_COMMAND_LENGTH+1] = {0};
int readCommandLength = 0;
bool newCommandRead = false;

void readSerial() {
  if(newCommandRead) {
    newCommandRead = false;
    readCommandLength = 0;
  }
  if(Serial.available()) {
    char c = Serial.read();
    readCommand[readCommandLength] = c;
    if(c == '\n') {
      readCommand[readCommandLength] = '\0';
      newCommandRead = true;
      return;
    }
    readCommandLength++;
    if(readCommandLength >= MAX_COMMAND_LENGTH) {
      readCommandLength = MAX_COMMAND_LENGTH - 1;
    }
  }
}

void interpretCommand() {
  if(!newCommandRead) {
    return;
  }

  if(strcmp(readCommand, "up") == 0) {
    pos[0]--;
    if(pos[0] < 0) {
      pos[0] = 0;
    }
    moveCharacter();
  } else if(strcmp(readCommand, "down") == 0) {
    pos[0]++;
    if(pos[0] >= LCD_HEIGHT) {
      pos[0] = LCD_HEIGHT-1;
    }
    moveCharacter();
  } else if(strcmp(readCommand, "left") == 0) {
    pos[1]--;
    if(pos[1] < 0) {
      pos[1] = 0;
    }
    moveCharacter();
  } else if(strcmp(readCommand, "right") == 0) {
    pos[1]++;
    if(pos[1] >= LCD_WIDTH) {
      pos[1] = LCD_WIDTH-1;
    }
    moveCharacter();
  }
}

void loop() {
  readSerial();
  interpretCommand();
}

