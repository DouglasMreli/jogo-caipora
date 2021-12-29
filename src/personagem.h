#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

class Personagem {

private:
    int vida, x, y;
    int sprite, animacao;
    bool caindo = false;
    bool subindo = false;

    int Andando() {
        switch(GetFrameAtualSprite(sprite)) {
            case 1: MudaFrameSprite(sprite, 2); break;
            case 2: MudaFrameSprite(sprite, 3); break;
            case 3: MudaFrameSprite(sprite, 4); break;
            case 4: MudaFrameSprite(sprite, 5); break;
            case 5: MudaFrameSprite(sprite, 6); break;
            case 6: MudaFrameSprite(sprite, 7); break;
            case 7: MudaFrameSprite(sprite, 8); break;
            case 8: MudaFrameSprite(sprite, 9); break;
            case 9: MudaFrameSprite(sprite, 10); break;
            case 10: MudaFrameSprite(sprite, 1); break;
            }
    }

    /* void Pulo() {
            caindo = true;
    }

    void playerCaindo(int &timer) {
        int t =TempoDecorrido(timer);
        int d = y + (5*t) - (10*t*t);
        DeslocaSprite(sprite, 0, d);
        if(d == 0) {
            caindo = false;
        }
    }*/

public:

    Personagem(int v, int x1, int y1) {
        vida = v;
        x = x1;
        y = y1;
    }

    int getSprite(){
        return sprite;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }

    void CriaFramePersonagem(char *arqPng, char *arqTxt) {
            sprite = CriaSprite(arqPng);
            MoveSprite(sprite, 50, 50);
            CarregaArquivoFramesSprite(sprite, arqTxt);

            MudaFrameSprite(sprite, 1);
            SetDimensoesSprite(sprite, 100,100);
    }

    void MovePersonagem(PIG_Teclado& meuTeclado, int& timer, int&repeticao) {
            if(TempoDecorrido(timer) > 0.03) {

                if(meuTeclado[PIG_TECLA_DIREITA] != 0) {
                    Andando();
                    SetFlipSprite(sprite, PIG_FLIP_NENHUM);
                    DeslocaSprite(sprite, +5, 0);

                }
                if(meuTeclado[PIG_TECLA_ESQUERDA] != 0) {
                    Andando();
                    SetFlipSprite(sprite, PIG_FLIP_HORIZONTAL);
                    DeslocaSprite(sprite, -5, 0);

                }
               /* if(caindo) {
                    playerCaindo(timer);
                }else {
                    if(meuTeclado[PIG_TECLA_CIMA] != 0 || meuTeclado[PIG_TECLA_BARRAESPACO] != 0) {
                        caindo = true;
                    }
                }*/
                ReiniciaTimer(timer);
            }

            GetXYSprite(sprite, &x, &y);
    }

};



#endif // PERSONAGEM_H_INCLUDED
