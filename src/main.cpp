#include <vector>

#include "PIG.h"
#include "cobra.h"
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


    //Criação do personagem
    Personagem player(100, 50);
    player.CriaPersonagem("..//imagens//sprite_andando.png", "..//imagens//spritePersonagem.txt");
    player.SetTimerTeclado(CriaTimer());

    //Criação do mundo
    Mundo mundo(20);
    mundo.CriaChao();

    // Criação da cobra
    Cobra cobra;
    cobra.CriaCobra();

    //Criação do HUD
    Hud hud;
    hud.CriaVidas(player.getVida());
    int xChao, yChao;

    //Sprite para o GameOver
    int gameOver = CriaSprite("..//imagens//gameover.png", 0);
    MoveSprite(gameOver, 200, 150);
    SetDimensoesSprite(gameOver, 400,400);

    //loop principal do jogo
    while(JogoRodando()) {

        PreparaCameraMovel();
        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        /*  Somente são executadas as funções relacionadas ao personagem
        se o mesmo tiver vidas sobrando
            */
        if(player.getVida() > 0) {
            player.MovePersonagem(meuTeclado, mundo.plataformas);
            player.VerificaDano(0);
        }

        if(cobra.getVida() > 0) {
            cobra.VerificaAtaque(player);
            if(cobra.getEstado() == 1)
                TrataAutomacaoAnimacao(cobra.getAnimacao());
        }

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        mundo.DesenhaChao();
        DesenhaAnimacao(cobra.getAnimacao());
        DesenhaAnimacao(player.getAnimacao());

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
