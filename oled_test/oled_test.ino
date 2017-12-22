#include "SSD1306.h"
#include "OLEDDisplayUi.h"

#include "images.h"

SSD1306  display(0x3c, D2, D1);

OLEDDisplayUi ui     (&display);

neutral = 0;
happy = 1;
sad = 2;
dead = 3;

long last_millis();

const byte img_width = (64-img_width)/25;
const byte img_height = 60;

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  switch (state) {
  case happy:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, happy_1);
    break;
  case sad:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, sad_1);
    break;
    case dead:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, dead_1);
    break;
  default:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, neutral_1);
  }
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  switch (state) {
  case happy:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, happy_2);
    break;
  case sad:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, sad_2);
    break;
    case dead:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, dead_2);
    break;
  default:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, neutral_2);
  }
  
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  switch (state) {
  case happy:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, happy_3);
    break;
  case sad:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, sad_3);
    break;
    case dead:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, dead_3);
    break;
  default:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, neutral_3);
  }
  
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  switch (state) {
  case happy:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, happy_4);
    break;
  case sad:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, sad_4);
    break;
    case dead:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, dead_4);
    break;
  default:
    display->drawXbm((128-img_width)/2, (64-img_width)/2, img_width, img_height, neutral_4);
  }
  
}

FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};
int frameCount = 4;

void setup() {
  Serial.begin(115200);
  Serial.println();
  ui.setTargetFPS(30);
  ui.setFrames(frames, frameCount);
  ui.setTimePerFrame(2000);
  ui.setTimePerTransition(0);

  state = 0;

  ui.init();

  display.flipScreenVertically();
}

void loop() {
  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    if ( (millis() - last_millis) > 3000 ){
      if (state < 3) {
        state++;
      } else {
        state = 0
      }
    }
    delay(remainingTimeBudget/2);
  }
  last_millis = millis()
}
