#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ---------- DISPLAY SETTINGS ----------
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 48
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TCA9548A_ADDR 0x70  // I2C address of multiplexer

// ---------- DFPLAYER SETTINGS ----------
#define DF_RX 16   // TinyPICO RX (to DFPlayer TX)
#define DF_TX 17   // TinyPICO TX (to DFPlayer RX)
HardwareSerial dfSerial(2);  
DFRobotDFPlayerMini dfPlayer;

// ---------- BUTTON SETTINGS ----------
#define COL1_PIN 34   // ADC input for column 1
#define COL2_PIN 35   // ADC input for column 2

int thresholds[6] = {400, 750, 1000, 1300, 1700, 2100}; 
// Adjust after calibration

// ---------- SYMBOL PLACEHOLDER ----------
const uint8_t symbol0[384] PROGMEM = { /* 64x48 bitmap data */ };
const uint8_t symbol1[384] PROGMEM = { /* another symbol */ };
// … up to symbol11
const uint8_t* symbols[12] = {
  symbol0, symbol1, /* … */ 
};

// ---------- HELPERS ----------
void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

int readButtonColumn(int analogPin) {
  int val = analogRead(analogPin);
  if (val < thresholds[0]) return 1;
  else if (val < thresholds[1]) return 2;
  else if (val < thresholds[2]) return 3;
  else if (val < thresholds[3]) return 4;
  else if (val < thresholds[4]) return 5;
  else if (val < thresholds[5]) return 6;
  return 0; // no button
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // DFPlayer
  dfSerial.begin(9600, SERIAL_8N1, DF_RX, DF_TX);
  if (!dfPlayer.begin(dfSerial)) {
    Serial.println("DFPlayer not found!");
    while(true);
  }
  dfPlayer.volume(20);

  // Test all displays
  for (int i=0; i<12; i++) {
    tcaSelect(i);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.printf("Display %d not found!\n", i);
    } else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.printf("Disp %d OK", i);
      display.display();
    }
  }
}

// ---------- LOOP ----------
void loop() {
  int button1 = readButtonColumn(COL1_PIN); // buttons 1–6
  int button2 = readButtonColumn(COL2_PIN); // buttons 7–12

  int pressed = 0;
  if (button1 > 0) pressed = button1;        // 1–6
  if (button2 > 0) pressed = button2 + 6;    // 7–12

  if (pressed > 0) {
    Serial.printf("Button %d pressed\n", pressed);

    // Show symbol
    int displayNum = pressed - 1;
    tcaSelect(displayNum);
    display.clearDisplay();
    display.drawBitmap(0, 0, symbols[displayNum], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();

    // Play sound
    dfPlayer.play(pressed); // plays 001.mp3–012.mp3
    delay(500); // debounce
  }
}
