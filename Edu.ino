#include "edu.h"

enum simbolo {
    NADA,
    FRENTE,
    ESQ,
    DIR,
};
enum estado {
    G_DIR = 0,
    RETO,
    G_ESQ,
};

enum estado estado_atual = G_DIR;

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

void loop() {  
    enum simbolo simb;

    //lê sensores e retorna o símbolo adequado
     if     (dist_frente()   <20)  simb = FRENTE;
    else if (distancia(s_esq)   <20)  simb = ESQ;
    else if (distancia(s_dir)   <20)  simb = DIR;
    else                              simb = NADA;
    Serial.print(simb);

      
    //Atualiza o estado da máquina
     estado_atual = prox_estado(estado_atual, simb);

    // Executa ação de acordo com o estado
    switch (estado_atual) {
      case G_DIR: {
          Serial.println(" GIRANDO PRA DIREITA");
          mover(100,-100);
      } break;
      case RETO: {
          Serial.println("EMPURRANDO");
          mover(150,150);
      } break;
      case G_ESQ: {
          Serial.println("GIRANDO PRA ESQUERDA");
          mover(-100,100);
      } break;
    }

    delay(100);
}


// Define os próximos estados com base no estado atual e símbolo lido
estado prox_estado(estado e, simbolo s) {
    switch (e) {
        case G_DIR:
            switch (s) {
                case FRENTE: return RETO;
                case ESQ:    return G_ESQ;
                default:     return G_DIR;
            }

        case RETO:
            switch (s) {
                case FRENTE: return RETO;
                case ESQ:    return G_ESQ;
                case DIR:    return G_DIR;
                default:     return G_DIR;
            }

        case G_ESQ:
            switch (s) {
                case FRENTE: return RETO;
                case DIR:    return G_DIR;
                default:     return G_ESQ;
            }
    }

    return G_ESQ; // valor padrão de segurança
}
