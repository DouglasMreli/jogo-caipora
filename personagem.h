#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

class Personagem {
public:
    int vida, x, y;
    int sprite;
    bool caindo = false;

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

    void MovePersonagem(PIG_Teclado& meuTeclado, int& timer, int&repeticao) {
            if(TempoDecorrido(timer) > 0.05) {

                if(meuTeclado[PIG_TECLA_DIREITA] != 0) {
                    SetFlipSprite(sprite, PIG_FLIP_NENHUM);
                    DeslocaSprite(sprite, +5, 0);

                }
                if(meuTeclado[PIG_TECLA_ESQUERDA] != 0) {

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
    }

};



#endif // PERSONAGEM_H_INCLUDED
