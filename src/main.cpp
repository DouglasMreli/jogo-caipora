#include "PIG.h"
#include "personagem.h"

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


    DefineFundo("..//imagens//florestaFundo.png");

    Personagem player(100, 100, 50);
    player.CriaFramePersonagem("..//imagens//sprite andando.png", "..//imagens//spritePersonagem.txt");
    MoveSprite(player.getSprite(), player.getX(), player.getY());

    int timer = CriaTimer();
    double t;
    int repeticao;
    //loop principal do jogo
    while(JogoRodando()) {

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        player.MovePersonagem(meuTeclado, timer, repeticao);


        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        DesenhaSprite(player.getSprite());
        EscreveDoubleEsquerda(GetFPS(), 1, 0, PIG_ALT_TELA - 100, {255,0,255,255});
        EscreveInteiroCentralizado(player.getX(), 100, 300);
        EscreveInteiroCentralizado(player.getY(), 100, 350);
        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
