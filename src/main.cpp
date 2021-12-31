#include "PIG.h"
#include "personagem.h"
#include "mundo.h"
#include <vector>

PIG_Evento evento;          //evento ser tratado a cada passada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado

void DesenhaCoracoes(vector<int> c) {
    for(int i = 0; i < c.size(); i++) {
        DesenhaObjeto(c[i]);
    }
}

int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Meu Jogo");

    //associando o teclado (basta uma única vez) com a variável meuTeclado
    meuTeclado = GetTeclado();
    PIG_Cor cor;
    cor.r = 255;
    cor.b=0;
    cor.g = 0;
    cor.a = 180;

    //SetModoJanela(PIG_JANELA_TELACHEIA_DISPLAY);
    DefineFundo("..//imagens//florestaFundo.png");

    Personagem player(100, 50);
    player.CriaPersonagem("..//imagens//sprite andando.png", "..//imagens//spritePersonagem.txt");
    player.SetTimerTeclado(CriaTimer());

    Mundo mundo(20);
    mundo.CriaChao();

    vector<int> coracoes;

    for(int i = 0; i < player.getVida(); i++) {
        int coracao = CriaObjeto("..//imagens//coracao.png");
        MoveObjeto(coracao, 100 + i*30, PIG_ALT_TELA-100);
        SetDimensoesObjeto(coracao, 30, 30);
        coracoes.push_back(coracao);
    }

    int xChao, yChao;
    //loop principal do jogo
    while(JogoRodando()) {

        PreparaCameraMovel();
        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        player.MovePersonagem(meuTeclado, mundo.plataformas[1], xChao, yChao);

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        DesenhaObjeto(player.getObjeto());
        mundo.DesenhaChao();

        PreparaCameraFixa();

       //DesenhaCoracoes(coracoes);
        EscreveDoubleDireita(GetFPS(), 1, PIG_LARG_TELA-100, PIG_ALT_TELA - 100, {255,0,255,255});
        EscreveInteiroCentralizado(player.getX(), 100, 300);
        EscreveInteiroCentralizado(player.getY(), 100, 350);

        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
