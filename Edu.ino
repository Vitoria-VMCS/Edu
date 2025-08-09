#include "edu.h"
#include "SumoIR.h"
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

SumoIR IR;
void setup() { 
    init_edu(9600);
    
    Serial.begin(115200);
    IR.begin(A0);

    IR.setLed(2,HIGH,180);
}

void loop() {  
    IR.update();
    if (IR.on()) {
        enum simbolo simb;

        //lê sensores e retorna o símbolo adequado
        if      (dist_frente()   <35)  simb = FRENTE;
        else if (dist_esq()  <35)  simb = ESQ;
        else if (dist_dir()   <35)  simb = DIR;
        else                              simb = NADA;
        Serial.print(simb);

        
        //Atualiza o estado da máquina
        estado_atual = prox_estado(estado_atual, simb);

        // Executa ação de acordo com o estado
        switch (estado_atual) {
        case G_DIR: {
            Serial.println(" GIRANDO PRA DIREITA");
            mover(150,-150);
        } break;
        case RETO: {
            Serial.println("EMPURRANDO");
            mover(255,255);
        } break;
        case G_ESQ: {
            Serial.println("GIRANDO PRA ESQUERDA");
            mover(-150,150);
        } break;
        }

        delay(100);
    
    }else{
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
