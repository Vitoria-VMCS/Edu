#include "edu.h"
#include "SumoIR.h"

#define PINO_IR 15
SumoIR IR;

enum simbolo {
    NADA,
    FRENTE,
    ESQ,
    DIR,
    FRENTE_ESQ,
    FRENTE_DIR,
};
enum estado {
    G_DIR = 0,
    RETO,
    G_ESQ,
    G_FRENTE_ESQ,
    G_FRENTE_DIR,
};

enum estado estado_atual = G_DIR;

void setup() { 
    init_edu(9600);    
    IR.begin(PINO_IR);
    IR.setLed(2,HIGH,180);
}

void loop() {  
    IR.update();

    if (IR.prepare()) { /* robô em preparação */
        mover(0,0);
        Serial.println("Preparar");

    } else if (IR.start()) {
        Serial.println("-> sumo start");

    }  else if (IR.on()) {
        enum simbolo simb;

        //lê sensores e retorna o símbolo adequado
        if      (dist_frente_esq() && dist_frente_dir())   simb = FRENTE;
        else if (dist_esq() )   simb = ESQ;
        else if (dist_dir() )   simb = DIR;
        else if (dist_frente_esq()) simb = FRENTE_ESQ;
        else if (dist_frente_dir()) simb = FRENTE_DIR;                    
        else simb = NADA;
        Serial.print(simb);

        
        //Atualiza o estado da máquina
        //empurra_giro = false;
        estado_atual = prox_estado(estado_atual, simb);

        // Executa ação de acordo com o estado
        switch (estado_atual) {
            case G_DIR: {
                Serial.println(" GIRANDO PRA DIREITA");
                mover(500,-500);
            } break;
            case RETO: {
                Serial.println("EMPURRANDO");
                mover(1023,1023);
            } break;
            case G_ESQ: {
                Serial.println("GIRANDO PRA ESQUERDA");
                mover(-500,500);
            } break;
            case G_FRENTE_ESQ: {
                Serial.println("GIRANDO LEVE PARA ESQUERDA");
                mover(-200, 200);
            } break;
            case G_FRENTE_DIR: {
                Serial.println("GIRANDO LEVE PARA DIREITA");
                mover(200, -200);
            } break;
        }

    } else if (IR.stop()){
        Serial.println("-> sumo stop");
        mover(0,0);
    }
}


    // Define os próximos estados com base no estado atual e símbolo lido
   estado prox_estado(estado e, simbolo s) {
        switch (e) {
            case G_DIR:
                switch (s) {
                    case FRENTE: return RETO;
                    case ESQ:    return G_ESQ;
                    case FRENTE_ESQ: return G_FRENTE_ESQ;
                    case FRENTE_DIR: return G_FRENTE_DIR;
                    case DIR: return G_DIR;
                    default:     return G_DIR;
                }

            case RETO:
                switch (s) {
                    case FRENTE: return RETO;
                    case ESQ:    return G_ESQ;
                    case DIR:    return G_DIR;
                    case FRENTE_ESQ: return G_FRENTE_ESQ;
                    case FRENTE_DIR: return G_FRENTE_DIR;
                    default:     return G_DIR;
                }

            case G_ESQ:
                switch (s) {
                    case FRENTE: return RETO;
                    case DIR:    return G_DIR;
                    case FRENTE_ESQ: return G_FRENTE_ESQ;
                    case FRENTE_DIR: return G_FRENTE_DIR;
                    case ESQ: return G_ESQ;
                    default:     return G_ESQ;
                }
            case G_FRENTE_ESQ:
                switch(s){
                    case FRENTE: return RETO;
                    case ESQ:    return G_ESQ;
                    case DIR:    return G_DIR;
                    case FRENTE_ESQ: return G_FRENTE_ESQ;
                    case FRENTE_DIR: return G_FRENTE_DIR;
                    default:     return G_DIR;
                }
            case G_FRENTE_DIR:
            switch(s){
                 case FRENTE: return RETO;
                    case ESQ:    return G_ESQ;
                    case DIR:    return G_DIR;
                    case FRENTE_ESQ: return G_FRENTE_ESQ;
                    case FRENTE_DIR: return G_FRENTE_DIR;
                    default:     return G_DIR;
            }
        }

        return G_ESQ; // valor padrão de segurança
    }
   

