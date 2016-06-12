#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define PIN_IR 3
#define PIN_DETECT 2

#define NUMPIXELS      240
#define PIXEL_PIN      6

IRsend irsend;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(PIN_DETECT, INPUT);
  irsend.enableIROut(38);
  irsend.mark(0);

  pixels.begin();

  Serial.begin(9600);
}

void loop() {
  bool irstatus = !digitalRead(PIN_DETECT);

  if (!irstatus) {
    enablePixels();
  } else {
    disablePixels();
  }

  Serial.println(irstatus);
}


void enablePixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 140, 0));
  }
  pixels.show();
}

void disablePixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
