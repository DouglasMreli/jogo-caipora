#ifndef COBRA_H_INCLUDED
#define COBRA_H_INCLUDED


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

public:

     static int MudaCobra(int animacao, void *param) {
        switch(GetModoAtualAnimacao(animacao)) {
        case 0: MudaModoAnimacao(animacao, 1, 0, 1); break;
        case 1: MudaModoAnimacao(animacao, 0, 0, 1); break;
        }
    }

    void CriaCobra() {
        animacao = CriaAnimacao("../imagens/spriteCobra.png", 1);
        MoveAnimacao(animacao, 100, 30);
        CarregaFramesPorLinhaAnimacao(animacao, 1, 6, 9);

        // animação andando direita
        CriaModoAnimacao(animacao, 0, 1);
        for( int i = 1; i <= 9; i++) {
            InsereFrameAnimacao(animacao, 0, i, 0.3, -1, 100, 100);
        }
        // animacao andando esquerda
        CriaModoAnimacao(animacao, 1, 0);
        for( int i = 28; i <= 36; i++) {
            InsereFrameAnimacao(animacao, 0, i, 0.3, -1, 100, 100);
        }
        // animação atacando
        CriaModoAnimacao(animacao, 2, 1);
        for( int i = 10; i <= 18; i++) {
            InsereFrameAnimacao(animacao, 1, i, 0.3-1, 100, 100);
        }
        CriaModoAnimacao(animacao, 3, 0);
        // animação morrendo
        for( int i = 19; i <= 27; i++) {
            InsereFrameAnimacao(animacao, 2, i, 0.3, -1, 100, 100);
        }

        estado = ANDANDO;
        GetXYAnimacao(animacao, &x, &y);
        SetDimensoesAnimacao(animacao, 100, 100);
        MudaModoAnimacao(animacao, 0, 0, 1);

        InsereTransicaoAnimacao(animacao, 2.5, 50.0, 0, 0, 0, 0, BRANCO, 0);
        InsereTransicaoAnimacao(animacao, 2.5, -50.0, 0, 0, 0, 0, BRANCO, 0);
        DefineTipoTransicaoAnimacao(animacao, PIG_TRANSICAO_LOOP);
        InsereAcaoAnimacao(animacao, 2.5, 2.5, (MudaCobra), NULL);
        IniciaAutomacaoAnimacao(animacao);
    }


    int getAnimacao() {
        return animacao;
    }

};

#endif // COBRA_H_INCLUDED
