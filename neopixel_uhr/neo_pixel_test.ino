
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define Neopix_PIN 6
#define AnzahlLEDs 60
#define rot 1
#define green 2
#define white 3
#define blau 4
int sekunde = 0;
int minute = 0;
int stunde = 0;
int pos_LED = 1;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(AnzahlLEDs, Neopix_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();

  pos_LED = -1;
  for (int i = 1; i < 13; i++) {
    Lampensteuerung(pos_LED + (5 * i), blau);
  }
  for (int i = 1; i < 5; i++) {
    Lampensteuerung(pos_LED + (15 * i), green);
  }

  strip.show(); // Initialize all pixels to 'off'
  // strip.clear();
  strip.setBrightness(50);
  Serial.begin(9600);
}

void loop() {

  for (int i = 0; i < 60; i++) {

    Lampensteuerung(i, rot);
     ziffernblatt_erhalten(i);
     delay(1000);
 
  }
  strip.clear();
  ziffernblatt();


}
void ziffernblatt() {
  pos_LED = -1;
  for (int i = 1; i < 13; i++) {
    Lampensteuerung(pos_LED + (5 * i), blau);
  }
  for (int i = 1; i < 5; i++) {
    Lampensteuerung(pos_LED + (15 * i), green);
  }
}

void ziffernblatt_erhalten (int i) {
  pos_LED = -1;
  switch (i) {
    case 5:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 10:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 15:
      Lampensteuerung(pos_LED+i, green);
      break;
    case 20:
      Lampensteuerung(pos_LED+i, blau);
      break;
     case 25:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 30:
      Lampensteuerung(pos_LED+i, green);
      break;
    case 35:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 40:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 45:
      Lampensteuerung(pos_LED+i, green);
      break;
    case 50:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 55:
      Lampensteuerung(pos_LED+i, blau);
      break;
    case 60:
      Lampensteuerung(pos_LED+i, green);
      break;
   default: break;
  }
}


void Lampensteuerung(int position, int Farbe)
{
  uint32_t c;
  int intensi = 50;
  switch (Farbe)
  {
    case rot:
      {
        Serial.println("rot");
        //    c= strip.Color(255, 0, 0);
        //    strip.setPixelColor(0, (strip.Color(255, 0, 0)), intensi); // Red
        //   strip.setPixelColor(0, c); // Red

        strip.setPixelColor(position, 105, 0, 105, intensi); // Red
        break;
      }
    case green:
      {
        Serial.println("green");
        strip.setPixelColor(position, 255, 165, 0, intensi); // green
        break;
      }
    case white:
      {
        Serial.println("white");
        strip.setPixelColor(position, 120, 120, 120, intensi); // weiss

        break;
      }
    case blau:
      {
        Serial.println("blau");
        strip.setPixelColor(position, 0, 0, 120, intensi); // blau

        break;

      }

    default:
      {
        Serial.println("break");
        strip.setPixelColor(2, (strip.Color(255, 0, 0), intensi)); // Red

        break;
      }
  }
  strip.show();
}
