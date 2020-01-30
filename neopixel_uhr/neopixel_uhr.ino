#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int LichtSensorPIN = A2;
int AuswahlPIN = 10;
#define Neopix_PIN 6
#define AnzahlLEDs 60
#define rot 1
#define green 2
#define white 3
#define blau 4
#define orange 5
int sekunde = 0;
int minuten = 0;
int stunde = 0;
int Helligkeit = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:

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

  pinMode(AuswahlPIN, INPUT);

  strip.begin();

  for (int i = 1; i < 13; i++) {
    Lampensteuerung((5 * i), blau);
  }
  for (int i = 1; i < 5; i++) {
    Lampensteuerung((15 * i), green);
  }

  strip.show(); // Initialize all pixels to 'off'
  // strip.clear();
  strip.setBrightness(40);
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    //    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //  rtc.adjust(DateTime(2020, 1, 28, 13,44 , 40));
  }
}

void loop() {

  uint8_t minuteb;
  uint8_t sekundeb;
  uint8_t stundeb;

  if (digitalRead(AuswahlPIN)) {

    for (int i = 0; i < 60; i++) {

      DateTime now2 = rtc.now();
      //   sekundeb = now2.second();
      i = now2.second();
      //   Lampensteuerung(sekundeb, orange);
      Lampensteuerung(i, orange);
      ziffernblatt_erhalten(i);
      delay(100);

      Helligkeit = analogRead(LichtSensorPIN);
      //   Serial.print("Helligkeit vorher: ");
      //   Serial.print(Helligkeit, DEC);
      Helligkeit = map (Helligkeit, 1, 1000, 150, 15);
      //   Serial.print("Helligkeit nachher: ");
      //   Serial.println(Helligkeit, DEC);

      strip.setBrightness(Helligkeit);

      int rawValue = analogRead(LichtSensorPIN);
      float voltage = rawValue * (5.0 / 1023) * 1000;

      float resitance = 10000 * ( voltage / ( 5000.0 - voltage) );

      // ... und hier auf die serielle Schnittstelle ausgegeben
      /*      Serial.print("Spannungswert:"); Serial.print(voltage); Serial.print("mV");
            Serial.print(", Widerstandswert:"); Serial.print(resitance); Serial.println("Ohm");
            Serial.println("---------------------------------------");

            Serial.print("Temperature: ");
            Serial.print(rtc.getTemperature());
            Serial.println(" C");



        //      Serial.print(jetzt.year(), DEC);
            Serial.print(now2.year(), DEC);
            Serial.print('/');
            Serial.print(now2.month(), DEC);
            Serial.print('/');
            Serial.print(now2.day(), DEC);
            Serial.print(" (");
            Serial.print(daysOfTheWeek[now2.dayOfTheWeek()]);
            Serial.print(") ");
            Serial.print(now2.hour(), DEC);
            Serial.print(':');
            Serial.print(now2.minute(), DEC);
            Serial.print(':');
            Serial.print(now2.second(), DEC);
            Serial.println();
      */
      minuteb = now2.minute();
      Lampensteuerung(minuteb, rot);
      stundeb = now2.hour();
      stundeb %= 12;
      stundeb *= 5;
      stundeb += (minuteb / 12);

      Lampensteuerung(stundeb, white);
      //    Serial.print("minuteb:"); Serial.println(minuteb);
      delay (2 );
    }
    strip.clear();
    ziffernblatt();

    Lampensteuerung(minuteb, rot);
    delay (20);
  } // endif AuswahlPIN
  else {
    // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    // Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
  }


}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void ziffernblatt() {

  for (int i = 1; i < 13; i++) {
    Lampensteuerung((5 * i), blau);
  }
  for (int i = 1; i < 5; i++) {
    Lampensteuerung((15 * i), green);
  }
}

void ziffernblatt_erhalten (int i) {

  switch (i) {
    case 5:
      Lampensteuerung(i, blau);
      break;
    case 10:
      Lampensteuerung(i, blau);
      break;
    case 15:
      Lampensteuerung(i, green);
      break;
    case 20:
      Lampensteuerung(i, blau);
      break;
    case 25:
      Lampensteuerung(i, blau);
      break;
    case 30:
      Lampensteuerung(i, green);
      break;
    case 35:
      Lampensteuerung(i, blau);
      break;
    case 40:
      Lampensteuerung(i, blau);
      break;
    case 45:
      Lampensteuerung(i, green);
      break;
    case 50:
      Lampensteuerung(i, blau);
      break;
    case 55:
      Lampensteuerung(i, blau);
      break;
    case 60:
      Lampensteuerung(i, green);
      break;
    default: break;
  }
}


void Lampensteuerung(int position, int Farbe)
{
  int LedOffset = -1;
  int intensi = 50;
  position = position + LedOffset;

  switch (Farbe)
  {
    case rot:
      {
        //      Serial.println("rot");
        //    c= strip.Color(255, 0, 0);
        //    strip.setPixelColor(0, (strip.Color(255, 0, 0)), intensi); // Red
        //   strip.setPixelColor(0, c); // Red

        strip.setPixelColor(position, 255, 0, 0, intensi); // Red
        break;
      }
    case green:
      {
        //    Serial.println("green");
        strip.setPixelColor(position, 124, 255, 0, intensi); // green
        break;
      }
    case orange:
      {
        //  Serial.println("orange");
        strip.setPixelColor(position, 255, 110, 0, intensi);
        break;
      }
    case white:
      {
        //   Serial.println("white");
        strip.setPixelColor(position, 200, 200, 200, intensi); // weiss

        break;
      }
    case blau:
      {
        //   Serial.println("blau");
        strip.setPixelColor(position, 0, 0, 255, intensi); // blau

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
