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

    //SetModoJanela(PIG_JANELA_TELACHEIA_DISPLAY);
    DefineFundo("..//imagens//florestaFundo.png");

    Personagem player(100, 50);
    player.CriaPersonagem("..//imagens//sprite andando.png", "..//imagens//spritePersonagem.txt");
    player.SetTimerTeclado(CriaTimer());

    int chao = CriaObjeto("..//imagens//chao.png");
    MoveObjeto(chao,500, 0);
    SetDimensoesObjeto(chao, 50,100);
    int xChao, yChao;
    //loop principal do jogo
    while(JogoRodando()) {

        PreparaCameraMovel();
        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        player.MovePersonagem(meuTeclado, chao, xChao, yChao);

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        DesenhaObjeto(player.getObjeto());
        DesenhaObjeto(chao);

        PreparaCameraFixa();

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
