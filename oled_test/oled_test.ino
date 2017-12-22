#include "SSD1306.h"
#include "OLEDDisplayUi.h"

#include "images.h"

SSD1306  display(0x3c, D2, D1);

OLEDDisplayUi ui     (&display);

byte bud_state = 0;

unsigned long last_millis = 0;

const byte img_width = 105;
const byte img_height = 60;

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, happy_1);
  }
  if (bud_state == 2) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, sad_1);
  }
  if (bud_state == 3) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, dead_1);
  }
  if (bud_state == 0) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, neutral_1);
  }
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, happy_2);
  }
  if (bud_state == 2) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, sad_2);
  }
  if (bud_state == 3) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, dead_2);
  }
  if (bud_state == 0) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, neutral_2);
  }
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, happy_3);
  }
  if (bud_state == 2) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, sad_3);
  }
  if (bud_state == 3) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, dead_3);
  }
  if (bud_state == 0) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, neutral_3);
  }
  
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, happy_4);
  }
  if (bud_state == 2) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, sad_4);
  }
  if (bud_state == 3) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, dead_4);
  }
  if (bud_state == 0) {
    display->drawXbm((128-img_width)/2, (64-img_height)/2, img_width, img_height, neutral_4);
  }
}

FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};
int frameCount = 4;

void setup() {
  Serial.begin(115200);
  Serial.println();
  ui.setTargetFPS(30);
  ui.setFrames(frames, frameCount);
  ui.setTimePerFrame(333);
  ui.setTimePerTransition(0);

  bud_state = 0;

  ui.init();

  display.flipScreenVertically();
  last_millis = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  int remainingTimeBudget = ui.update();
  
  if (remainingTimeBudget > 0) {
    Serial.println(currentMillis - last_millis);
    if ( (currentMillis - last_millis) > 5000 ){
      Serial.println(bud_state);
      if (bud_state < 3) {
        bud_state = bud_state + 1;
      } else {
        bud_state = 0;
      }
      last_millis = millis();
    }
    delay(remainingTimeBudget/2);
  }
}
