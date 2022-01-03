#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

/*
    Classe responsável por gerenciar as informações que aparecem na tela, como a vida do personagem
*/

class Hud {
private:
    vector<int> vidas; // lista com as vidas do personagem que aparecerá na tela


public:
    //Função que cria os sprites dos corações que representam a vida do personagem
    void CriaVidas(int qtdVida) {
        // Cria um coração para cada vida do personagem
        for(int i = 0; i < qtdVida; i++) {
            int sprite = CriaSprite("..//imagens//coracao.png");
            MoveSprite(sprite, 100 + i*30, PIG_ALT_TELA-100);
            SetDimensoesSprite(sprite, 30, 30);
            vidas.push_back(sprite);  // adiciona a nova vida à lista de vidas
        }
    }

    // Função que desenha as vidas na tela
    void DesenhaVidas(int qtdVida) {
        for(int i = 0; i < qtdVida; i++) {
            DesenhaSprite(vidas[i]);
        }
    }
};

#endif // HUD_H_INCLUDED
