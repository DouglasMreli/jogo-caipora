#include "PIG.h"
#include "personagem.h"

PIG_Evento evento;          //evento ser tratado a cada passada do loop principal
PIG_Teclado meuTeclado;     //vari�vel como mapeamento do teclado


int main( int argc, char* args[] ){

    //criando o jogo (aplica��o)
    CriaJogo("Meu Jogo");

    //associando o teclado (basta uma �nica vez) com a vari�vel meuTeclado
    meuTeclado = GetTeclado();
    PIG_Cor cor;
    cor.r = 255;
    cor.b=0;
    cor.g = 0;
    cor.a = 180;


    DefineFundo("..//imagens//florestaFundo.png");

    Personagem player(100, 100, 50);
    player.CriaFramePersonagem("..//imagens//sprite andando.png", "..//imagens//spritePersonagem.txt");
    MoveSprite(player.getSprite(), player.getX(), player.getY());

    int timer = CriaTimer();
    double t;
    int repeticao;
    //loop principal do jogo
    while(JogoRodando()) {

        //pega um evento que tenha ocorrido desde a �ltima passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        player.MovePersonagem(meuTeclado, timer, repeticao);


        //ser� feita a prepara��o do frame que ser� exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        DesenhaSprite(player.getSprite());
        EscreveDoubleEsquerda(GetFPS(), 1, 0, PIG_ALT_TELA - 100, {255,0,255,255});
        EscreveInteiroCentralizado(player.getX(), 100, 300);
        EscreveInteiroCentralizado(player.getY(), 100, 350);
        //o frame totalmente pronto ser� mostrado na tela
        EncerraDesenho();
    }

    //o jogo ser� encerrado
    FinalizaJogo();

    return 0;
}
