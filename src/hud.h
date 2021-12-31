#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED


class Hud {
private:
    vector<int> vidas;


public:
    void CriaVidas(int qtdVida) {
        for(int i = 0; i < qtdVida; i++) {
            int sprite = CriaSprite("..//imagens//coracao.png");
            MoveSprite(sprite, 100 + i*30, PIG_ALT_TELA-100);
            SetDimensoesSprite(sprite, 30, 30);
            vidas.push_back(sprite);
        }
    }

    void DesenhaVidas(int qtdVida) {
        for(int i = 0; i < qtdVida; i++) {
            DesenhaSprite(vidas[i]);
        }
    }
};

#endif // HUD_H_INCLUDED
