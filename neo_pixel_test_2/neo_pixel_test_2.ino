
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int LichtSensorPIN = A2;
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
