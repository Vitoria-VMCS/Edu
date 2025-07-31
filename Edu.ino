#include "edu.h"

void setup() { init_edu(9600); }
void loop() {
    int   d_frente = dist_frente();
    float d_esq    = dist_esq();
    float d_dir    = dist_dir();

    Serial.print(d_frente); Serial.print(", ");
    Serial.print(d_esq);    Serial.print(", ");
    Serial.print(d_dir);    Serial.print("");
    Serial.println("");

    delay(40);
}
