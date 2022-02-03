#ifndef COBRA_H_INCLUDED
#define COBRA_H_INCLUDED
#include "personagem.h"

#define ANDANDO 1
#define ATACANDO 2
#define MORRENDO 3
/*
    Classe responsável por gerenciar os inimigos-cobra das fases
*/

class Cobra {

private:
    int vida = 3; // variável que guarda a vida do inimigo-cobra
    int x, y;     // posição do inimigo-cobra no mundo
    int animacao; // guarda a animação do inimigo-cobra
    int estado;
    int direcao;
    int timerAtaque, timerAndar;

    void atacando(int direcao) {
        if(TempoDecorrido(timerAtaque) < 1) {
            if(timerAndar > 0.05) {
                switch(direcao){
                    case 0: MoveAnimacao(animacao, 5, 0); break;
                    case 1: MoveAnimacao(animacao, -5, 0);
                }
                ReiniciaTimer(timerAndar);
            }
        }else{
            estado = ANDANDO;
            ReiniciaTimer(timerAtaque);
        }
    }

public:

     static int MudaCobra(int animacao, void *param) {
        switch(GetModoAtualAnimacao(animacao)) {
        case 0: MudaModoAnimacao(animacao, 1, 0, 1); break;
        case 1: MudaModoAnimacao(animacao, 0, 0, 1); break;
        }
    }

    void CriaCobra() {
        animacao = CriaAnimacao("../imagens/spriteCobra.png", 1);
        MoveAnimacao(animacao, 700, 38);
        CarregaFramesPorLinhaAnimacao(animacao, 1, 6, 9);

        // animação andando direita
        CriaModoAnimacao(animacao, 0, 1);
        for( int i = 1; i <= 9; i++) {
            InsereFrameAnimacao(animacao, 0, i, 0.15, -1, 70, 70);
        }
        // animacao andando esquerda
        CriaModoAnimacao(animacao, 1, 1);
        for( int i = 28; i <= 36; i++) {
            InsereFrameAnimacao(animacao, 1, i, 0.15, -1, 70, 70);
        }
        // animação atacando direita
        CriaModoAnimacao(animacao, 2, 1);
        for( int i = 10; i <= 18; i++) {
            InsereFrameAnimacao(animacao, 2, i, 0.3, -1, 70, 70);
        }
        // animacao atacando esquerda
        CriaModoAnimacao(animacao, 4, 1);
        for( int i = 37; i <= 45; i++) {
            InsereFrameAnimacao(animacao, 4, i, 0.3, -1, 70, 70);
        }
        CriaModoAnimacao(animacao, 3, 0);
        // animação morrendo
        for( int i = 19; i <= 27; i++) {
            InsereFrameAnimacao(animacao, 3, i, 0.3, -1, 70, 70);
        }

        estado = ANDANDO;
        GetXYAnimacao(animacao, &x, &y);
        SetDimensoesAnimacao(animacao, 70, 70);
        MudaModoAnimacao(animacao, 0, 0, 1);

        InsereTransicaoAnimacao(animacao, 3.0, 100.0, 0, 0, 0, 0, BRANCO, 0);
        InsereTransicaoAnimacao(animacao, 3.0, -100.0, 0, 0, 0, 0, BRANCO, 0);
        DefineTipoTransicaoAnimacao(animacao, PIG_TRANSICAO_LOOP);
        InsereAcaoAnimacao(animacao, 3.0, 3.0, (MudaCobra), NULL);
        IniciaAutomacaoAnimacao(animacao);
        timerAtaque = CriaTimer();
        timerAndar = CriaTimer();
    }

    void VerificaAtaque(Personagem jogador) {
        if(estado == ANDANDO) {
            if(abs(jogador.getX() -  x)<= 150 && jogador.getY() < 43 && jogador.getY() > 34) {
                ReiniciaTimer(timerAtaque);
                estado = ATACANDO;
                if(jogador.getX() < x) {
                MudaModoAnimacao(animacao, 4, 1, 1);
                direcao == 1;
            }else if (jogador.getX() > x){
                MudaModoAnimacao(animacao, 2, 1, 1);
                direcao == 0;
            }
            }
        }else if(estado == ATACANDO) {
            atacando(direcao);
        }
    }

    int getAnimacao() {
        return animacao;
    }
    int getEstado() {
        return estado;
    }
    int getVida() {
        return vida;
    }

};

#endif // COBRA_H_INCLUDED
