#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define V_0 600
#define GRAV -800

class Personagem {

private:
    int vida = 10;
    int x, y;
    int salto, yAnterior, xAnterior;
    int animacao;
    int timerTeclado, timerPulo, timerDano;
    bool parado, andando, pulando, caindo;
    int plataformaAtual;


    void mudaAnimacao() {

         if(andando == true && GetModoAtualAnimacao(animacao) != 0) {
                MudaModoAnimacao(animacao, 0, 0, 1);
        }
        if(parado == true && GetModoAtualAnimacao(animacao) != 2) {
                MudaModoAnimacao(animacao, 1, 0, 1);
        }

    }

    int pulo() {
        int py = y;
        float tempo = TempoDecorrido(timerPulo);
        if (tempo > 0.6) {
                salto = y;
                ReiniciaTimer(timerPulo);
                caindo = true;
                pulando = false;
        }else{
            py = salto +( V_0*tempo) + (GRAV*tempo*tempo);
        }

        return py;
    }

    int queda() {
        int py;
        float tempo = TempoDecorrido(timerPulo);
        py = salto + (GRAV*tempo*tempo);
        return py;
    }

    int VerificaColisao(vector<int> plataformas) {
        if(plataformaAtual != -1) {
            if(TestaColisaoAnimacaoObjeto(animacao, plataformas[plataformaAtual]))
                return plataformaAtual;
        }

        int alturaPlat, larguraPlat, xPlat, yPlat;

        for(int i = 0; i < plataformas.size(); i++) {
            if(TestaColisaoAnimacaoObjeto(animacao, plataformas[i])) {

                GetDimensoesObjeto(plataformas[i], &xPlat, &yPlat);
                GetDimensoesObjeto(plataformas[i], &alturaPlat, &larguraPlat);
                /*if(caindo && yAnterior >= y+alturaPlat) {
                    y = y+alturaPlat;
                    caindo = false;
                    parado = true;
                    return i;
                }*/
                caindo = false;
                parado = true;
                return i;
            }
        }

        return -1;
    }

public:

    Personagem(int x1, int y1) {
        x = x1;
        y = y1;
    }

    int getAnimacao(){
        return animacao;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    int getVida() {
        return vida;
    }
    void SetTimerTeclado(int t) {
        timerTeclado = t;
    }

    void SetTimerPulo(int t) {
        timerPulo = t;
    }

    void CriaPersonagem(char *arqPng, char *arqTxt) {
            animacao = CriaAnimacao(arqPng);
            MoveAnimacao(animacao, 0, 100);
            CarregaFramesPorLinhaAnimacao(animacao, 1, 2, 5);

            CriaModoAnimacao(animacao, 0, 1);
            for( int i = 1; i <= 10; i++) {
                InsereFrameAnimacao(animacao, 0, i, 0.1, -1, 100, 100);
            }

            CriaModoAnimacao(animacao, 1, 0);
            InsereFrameAnimacao(animacao, 1, 2, 0.1, -1, 100, 100);

            SetDimensoesAnimacao(animacao, 100,100);

            plataformaAtual = 0;
            parado = true;
            andando = false;
            pulando = false;
            caindo = false;

            timerPulo = CriaTimer();
            timerDano = CriaTimer();
    }

    void MovePersonagem(PIG_Teclado& meuTeclado, vector<int>& plat) {
            GetXYAnimacao(animacao, &xAnterior, &yAnterior);
            if(TempoDecorrido(timerTeclado) > 0.03) {

                if(meuTeclado[PIG_TECLA_DIREITA] != 0) {
                    andando = true;
                    parado = false;
                    SetFlipAnimacao(animacao, PIG_FLIP_NENHUM);

                    DeslocaAnimacao(animacao, +5, 0);
                    DeslocaCamera(+5, 0);

                }else if(meuTeclado[PIG_TECLA_ESQUERDA] != 0) {
                    andando = true;
                    parado = false;
                    SetFlipAnimacao(animacao, PIG_FLIP_HORIZONTAL);

                    DeslocaAnimacao(animacao, -5, 0);
                    DeslocaCamera(-5, 0);

                }else {
                    andando = false;
                    parado = true;
                }

                GetXYAnimacao(animacao, &x, &y);

                if(!pulando && !caindo) {
                    if(meuTeclado[PIG_TECLA_CIMA] != 0 || meuTeclado[PIG_TECLA_BARRAESPACO] != 0) {
                        ReiniciaTimer(timerPulo);
                        pulando = true;
                        parado = false;
                        andando = false;
                        salto = y++;
                    }
                }

                if(pulando) {
                    y = pulo();
                    MoveAnimacao(animacao, x, y);
                }else if(caindo) {
                    y = queda();
                    MoveAnimacao(animacao, x, y);
                }


                mudaAnimacao();
                plataformaAtual = VerificaColisao(plat);

                if(plataformaAtual == -1) {
                    if(!pulando && !caindo) {
                        salto = y;
                        ReiniciaTimer(timerPulo);
                        caindo = true;
                    }
                }

                yAnterior = y;
                ReiniciaTimer(timerTeclado);
            }
    }

    void VerificaDano() {
        if(TempoDecorrido(timerDano) > 0.5) {
            if(y < 0) {
                EscreverCentralizada("DANO", 300, 300, VERMELHO);
                vida = vida - 1;
            }
             ReiniciaTimer(timerDano);
        }
    }

};




#endif // PERSONAGEM_H_INCLUDED
