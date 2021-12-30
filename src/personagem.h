#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define V_0 500
#define GRAV -800/5

class Personagem {

private:
    int vida = 5;
    int x, y;
    int objeto, animacao;
    int timerTeclado, timerPulo;
    bool parado, andando, pulando, caindo;

    int Andando() {
        switch(GetFrameAtualObjeto(objeto)) {
            case 1: MudaFrameObjeto(objeto, 2); break;
            case 2: MudaFrameObjeto(objeto, 3); break;
            case 3: MudaFrameObjeto(objeto, 4); break;
            case 4: MudaFrameObjeto(objeto, 5); break;
            case 5: MudaFrameObjeto(objeto, 6); break;
            case 6: MudaFrameObjeto(objeto, 7); break;
            case 7: MudaFrameObjeto(objeto, 8); break;
            case 8: MudaFrameObjeto(objeto, 9); break;
            case 9: MudaFrameObjeto(objeto, 10); break;
            case 10: MudaFrameObjeto(objeto, 1); break;
            }
    }

    void Pulo() {
            caindo = true;
    }

    void playerCaindo() {
        int t =TempoDecorrido(timerPulo);
        if(t > 0.05) {
            int d = y + (0.1*t) - (0.1*t*t);
            DeslocaObjeto(objeto, 0, d);
            if(d == 50) {
                caindo = false;
            }
        }
    }

public:

    Personagem(int x1, int y1) {
        x = x1;
        y = y1;
    }

    int getObjeto(){
        return objeto;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }

    void SetTimerTeclado(int t) {
        timerTeclado = t;
    }

    void SetTimerPulo(int t) {
        timerPulo = t;
    }

    void CriaPersonagem(char *arqPng, char *arqTxt) {
            objeto = CriaObjeto(arqPng);
            MoveObjeto(objeto, 350, 50);
            CarregaArquivoFramesObjeto(objeto, arqTxt);

            MudaFrameObjeto(objeto, 1);
            SetDimensoesObjeto(objeto, 100,100);
            parado = true;
            andando = false;
            pulando = false;
            caindo = false;

    }

    void MovePersonagem(PIG_Teclado& meuTeclado, int objeto2, int xB, int yB) {
            if(TempoDecorrido(timerTeclado) > 0.03) {

                if(meuTeclado[PIG_TECLA_DIREITA] != 0) {
                    Andando();
                    SetFlipObjeto(objeto, PIG_FLIP_NENHUM);
                    if(xB > x || !TestaColisaoObjetos(objeto,objeto2)) {
                        DeslocaObjeto(objeto, +5, 0);
                        DeslocaCamera(+5, 0);
                    }
                }
                if(meuTeclado[PIG_TECLA_ESQUERDA] != 0) {
                    Andando();
                    SetFlipObjeto(objeto, PIG_FLIP_HORIZONTAL);
                    if(xB < x || !TestaColisaoObjetos(objeto,objeto2)) {
                        DeslocaObjeto(objeto, -5, 0);
                        DeslocaCamera(-5, 0);
                    }
                }

                if(caindo) {
                    playerCaindo();
                }else {
                    if(meuTeclado[PIG_TECLA_CIMA] != 0 || meuTeclado[PIG_TECLA_BARRAESPACO] != 0) {
                        timerPulo = CriaTimer();
                        caindo = true;
                    }
                }
                ReiniciaTimer(timerTeclado);
            }

            GetXYObjeto(objeto, &x, &y);
    }

};



#endif // PERSONAGEM_H_INCLUDED
