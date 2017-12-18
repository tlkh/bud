#include "SSD1306.h"
#include "OLEDDisplayUi.h"

#include "images.h"

SSD1306  display(0x3c, D2, D1);
SSD1306  display2(0x3c, D4, D3);

OLEDDisplayUi ui     ( &display );

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  display->drawXbm(0, 0, 128, 64, bud_neutral);
  ui.disableIndicator();
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(0, 0, 128, 64, bud_happy);
  ui.disableIndicator();
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(0, 0, 128, 64, bud_sad);
  ui.disableIndicator();
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(0, 0, 128, 64, bud_dead);
  ui.disableIndicator();
}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};

// how many frames are there?
int frameCount = 4;

void setup() {
  Serial.begin(115200);
  Serial.println();
  ui.setTargetFPS(30);
  ui.setFrames(frames, frameCount);
  ui.setTimePerFrame(1);
  ui.setTimePerTransition(0);

  ui.init();

  display.flipScreenVertically();
}


void loop() {
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }
}
