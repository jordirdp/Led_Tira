/* Project: Arduino controla tiras LED */
/* Author: Jordi Rodriguez */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Definir PIN de conexión y nº de leds en cada tira
#define LED_PIN    6
#define LED_COUNT 200

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}


void loop() {

  // Relleno progresivo (azul, rojo, verde)
  colorWipe(strip.Color(255,   0,   0), 50);
  colorWipe(strip.Color(  0, 255,   0), 50);
  colorWipe(strip.Color(  0,   0, 255), 50);

  // Marquesina de teatro (azul, rojo, verde)
  theaterChase(strip.Color(127, 127, 127), 50);
  theaterChase(strip.Color(127,   0,   0), 50);
  theaterChase(strip.Color(  0, 127,   0), 50);
  theaterChase(strip.Color(  0,   0, 127), 50); 

  // Arcoiris
  rainbow(10);

  // Marquesina de teatro con arcoiris
  theaterChaseRainbow(50);
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}


void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {
    for(int b=0; b<3; b++) {
      strip.clear();
            for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
    }
  }
}


void rainbow(int wait) {
  // Rueda de color de 0 a 65536
  int numero = 5;       // nº repeticiones
  int velocidad = 255;  // velocidad
  int fragmentacion = 1;// repeticiones internas en la tira
  int brillo = 255;     // brillo
  for(long firstPixelHue = 0; firstPixelHue < numero*65536; firstPixelHue += velocidad) {
    strip.rainbow(firstPixelHue,fragmentacion, brillo);
     
    strip.show();
    delay(wait);
  }
}


void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;                            // empieza en azul
  for(int a=0; a<30; a++) {                         // Repite 30 veces
    for(int b=0; b<3; b++) {
      strip.clear();
      for(int c=b; c<strip.numPixels(); c += 3) {   // cuenta desde "b" hasta el final de la tira en incrementos de 3
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
      firstPixelHue += 65536 / 90;                  // Un ciclo cada 90 frames
    }
  }
}
