#ifndef ledFX_H
#define ledFX_H
#include "edu.h"
#include <Adafruit_NeoPixel.h>

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define PIN 2 //pino do anel de leds
#define NUMPIXELS 8 // quantidade de leds do anel
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // necessario

bool leitura[4] = {0};
void leituraSensores() {
  leitura[0] = dist_esq();
  leitura[1] = dist_frente_esq();
  leitura[2] = dist_frente_dir();
  leitura[3] = dist_dir();
}

void ledBlink(int r, int g, int b, int time) {    // pisca todas os leds em um intervalo de tempo
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();   
  }
  pixels.clear();
  delay(time);
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();    
  }
  delay(time);
}
/*----------------------------------------------------------------------------------------*/
void ledLight (int r, int g, int b) {   // luz contínua
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
  }
}
/*----------------------------------------------------------------------------------------*/
void ledCircle(int r, int g, int b, int time) {   // luzes "andam" em círculo numa certa velocidade dependendo do tempo
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
    delay(time);
    pixels.clear(); 
  }
}
/*----------------------------------------------------------------------------------------*/
void ledCircleBlink(int r, int g, int b, int time) {  // luzes "andam" em círculo e piscam no final numa certa velocidade dependendo do tempo
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
  }
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(time);
    pixels.clear();
  }
}


void setDefaultColor(uint8_t r, uint8_t g, uint8_t b) {
  for (uint8_t i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
}

  

void ledDetection() {
  setDefaultColor(3, 5, 3); // Define a cor padrão azul para todos os LEDs
  leituraSensores();

  auto azul    = pixels.Color(0,   0,   150);
  auto amarelo = pixels.Color(150, 150, 0);
  auto branco  = pixels.Color(150, 150, 150);
  auto roxo    = pixels.Color(150, 150, 0);

  if (leitura[0]) {
    Serial.println("ESQUERDA LATERAL DETECTADO");
    pixels.setPixelColor(LED6, azul);
  } if (leitura[1]) {
    Serial.println("ESQUERDA FRONTAL DETECTADO");
    pixels.setPixelColor(LED5, azul);
  } if (leitura[2]) {
    Serial.println("DIREITA FRONTAL DETECTADO");
    pixels.setPixelColor(LED4, azul);
  } if (leitura[3]) {
    Serial.println("DIREITA LATERAL DETECTADO");
    pixels.setPixelColor(LED3, azul);
  } else {
    Serial.println("PROCURANDO OBJETO");
  }
  
  pixels.show();
  //!! delay(10);
}



#endif
