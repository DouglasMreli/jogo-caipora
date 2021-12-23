#include "PIG.h"

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


    int personagem = CriaSprite("..//imagens//sprite andando.png");
    MoveSprite(personagem, 50, 50);
    CriaFrameSprite(personagem, 1, 0, 0, 572 , 572);
    CarregaArquivoFramesSprite(personagem, "..//imagens//spritePersonagem.png");
    MudaFrameSprite(personagem, 1);
    SetDimensoesSprite(personagem, 100,100);

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e tudo deve ser atualizado

        //será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada
         DesenhaSprite(personagem);
         MoveSprite(personagem, 100, 50);
         MudaFrameSprite(personagem, 2);
        DesenhaSprite(personagem);
        MoveSprite(personagem, 200, 50);
        MudaFrameSprite(personagem, 3);
        DesenhaSprite(personagem);

        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}
