#include <vector>

#include "PIG.h"
#include "personagem.h"
#include "mundo.h"
#include "hud.h"


PIG_Evento evento;          //evento ser tratado a cada passada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado


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
    player.CriaPersonagem("..//imagens//sprite_andando.png", "..//imagens//spritePersonagem.txt");
    player.SetTimerTeclado(CriaTimer());

    Mundo mundo(20);
    mundo.CriaChao();

    Hud hud;
    hud.CriaVidas(player.getVida());
    int xChao, yChao;

    int gameOver = CriaSprite("..//imagens//gameover.png", 0);
    MoveSprite(gameOver, 200, 150);
    SetDimensoesSprite(gameOver, 400,400);
    //loop principal do jogo
    while(JogoRodando()) {

        PreparaCameraMovel();
        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        if(player.getVida() >= 0) {
            player.MovePersonagem(meuTeclado, mundo.plataformas);
            player.VerificaDano();
        }


        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        DesenhaAnimacao(player.getAnimacao());
        mundo.DesenhaChao();

        PreparaCameraFixa();

        hud.DesenhaVidas(player.getVida());
        EscreveDoubleDireita(GetFPS(), 1, PIG_LARG_TELA-100, PIG_ALT_TELA - 100, {255,0,255,255});
        EscreveInteiroCentralizado(player.getX(), 100, 300);
        EscreveInteiroCentralizado(player.getY(), 100, 350);
        EscreveInteiroCentralizado(player.getVida(), 100, 400, VERMELHO);

        if(player.getVida() <= 0) {
            DesenhaSprite(gameOver);
        }

        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
