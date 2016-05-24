#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#define TRIGGER_PIN   12 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      11 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE  250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define NUMPIXELS      119
#define PIXEL_PIN      6

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pixels.begin();
}

void loop() {
  delay(50);

  unsigned long uS = sonar.ping_median();
  unsigned long cm = sonar.convert_cm(uS);

  Serial.print("Ping: ");
  Serial.print(cm); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  if (cm != 0) {
    enablePixels();
  } else {
    disablePixels();
  }
}

void enablePixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 64));
  }
  pixels.show();
}

void disablePixels() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}


