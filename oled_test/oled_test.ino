#include "SSD1306.h"
#include "OLEDDisplayUi.h"

#include "images.h"

SSD1306  display(0x3c, D2, D1);

OLEDDisplayUi ui     (&display);

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  display->drawXbm(26, 10, 75, 43, bud_neutral);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 50, "yes no maybe so");
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  display->drawXbm(26, 10, 75, 43, bud_happy);
  display->drawString(64, 50, "nothing to complain about");
  
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  display->drawXbm(26, 10, 75, 43, bud_sad);
  display->drawString(64, 50, "keep ignoring me fine");
  
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  display->drawXbm(26, 10, 75, 43, bud_dead);
  display->drawString(64, 50, "goodbye my 'friend'");
  
}

FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};

// how many frames are there?
int frameCount = 4;

void setup() {
  Serial.begin(115200);
  Serial.println();
  ui.setTargetFPS(30);
  ui.setFrames(frames, frameCount);
  ui.setTimePerFrame(2000);
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
