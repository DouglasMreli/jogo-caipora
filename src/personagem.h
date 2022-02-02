#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define V_0 600
#define GRAV -800

#define LARG_PERS 100
#define ALT_PERS  70
class Personagem {

private:
    int vida = 10;    // pontos de vida do personagem
    int x, y;            // posição da personagem no mapa
    int salto, yAnterior, xAnterior;  // variáveis auxiliares para as funções de movimentação
    int animacao;  // variável que contem as animações do personagem
    int timerTeclado, timerPulo, timerDano; // variáveis reservadas para os timers
    bool parado, andando, pulando, caindo; // variaveis para os estados do personagem
    int plataformaAtual;  // variável que guarda a plataforma em que o personagem está
                                    //(recebe -1 quando em nenhuma)


    //Essa função muda a animação do personagem de acordo com o estado dele
    void mudaAnimacao() {

         if(andando == true && GetModoAtualAnimacao(animacao) != 0) {
                MudaModoAnimacao(animacao, 0, 0, 1);
        }
        if(parado == true && GetModoAtualAnimacao(animacao) != 2) {
                MudaModoAnimacao(animacao, 1, 0, 1);
        }

    }

    //Essa função calcula o deslocamento do personagem quando estiver pulando;
    int pulo() {
        int py = y;
        float tempo = TempoDecorrido(timerPulo);
        if (tempo > 0.4) {                           // O personagem sobre por 0.6 segundos
                salto = y;                              // quando atinge esse tempo, o timer reinicia e personagem
                ReiniciaTimer(timerPulo);    // passa a cair
                caindo = true;
                pulando = false;
        }else{
            py = salto +( V_0*tempo) + (GRAV*tempo*tempo);   //formula de subida do personagem
        }

        return py;
    }

    //Função que calcula o deslocamento do personagem enquanto caindo
    int queda() {
        int py;
        float tempo = TempoDecorrido(timerPulo);
        py = salto + (GRAV*tempo*tempo);
        return py;
    }

    /*  Função que verifica as colisões do personagem com as plataformas
        Recebe uma lista de plataformas como parâmetro
        */
    int VerificaColisao(vector<int> plataformas) {
        // verifica se o personagem permance em cima da mesma plataforma
        if(plataformaAtual != -1) {
            if(TestaColisaoAnimacaoObjeto(animacao, plataformas[plataformaAtual]))
                return plataformaAtual;
        }

        int alturaPlat, larguraPlat, xPlat, yPlat; // variaveis que recebem os atributos da plataforma
        //for para percorrer todas as plataformas
        for(int i = 0; i < plataformas.size(); i++) {
            if(TestaColisaoAnimacaoObjeto(animacao, plataformas[i])) {
                /*Se uma colisão for detectada, a posição do personagem será
                    atualizada e o estado mudará
                    */

                GetXYObjeto(plataformas[i], &xPlat, &yPlat);
                GetDimensoesObjeto(plataformas[i], &alturaPlat, &larguraPlat);

                 if(x + LARG_PERS > xPlat && xAnterior < x) {
                    x = xPlat - larguraPlat + LARG_PERS;
                }else if(x < xPlat + larguraPlat && xAnterior > x) {
                    x = xPlat + larguraPlat - LARG_PERS;
                }

                if(caindo && yAnterior >= yPlat + alturaPlat-ALT_PERS) {
                    y = yPlat+alturaPlat-ALT_PERS;
                    caindo = false;
                    parado = true;
                    return i;
                }


                if(y+ALT_PERS > yPlat &&  yAnterior < y) {
                    pulando = false;
                    caindo = true;
                    ReiniciaTimer(timerPulo);
                    return -1;
                }

            }

        }

        return -1;
    }

public:
    //construtor da classe
    Personagem(int x1, int y1) {
        x = x1;
        y = y1;
    }

    int getAnimacao(){
        return animacao;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    int getVida() {
        return vida;
    }
    void SetTimerTeclado(int t) {
        timerTeclado = t;
    }

    void SetTimerPulo(int t) {
        timerPulo = t;
    }

    //Função responsável por criar os sprites e setar as configurações do personagem
    void CriaPersonagem(char *arqPng, char *arqTxt) {
            //funções que carrega a animação do personagem
            animacao = CriaAnimacao(arqPng);
            MoveAnimacao(animacao, x, y);
            CarregaFramesPorLinhaAnimacao(animacao, 1, 2, 5);

            CriaModoAnimacao(animacao, 0, 1);
            for( int i = 1; i <= 10; i++) {
                InsereFrameAnimacao(animacao, 0, i, 0.1, -1, 100, 100);
            }

            CriaModoAnimacao(animacao, 1, 0);
            InsereFrameAnimacao(animacao, 1, 2, 0.1, -1, 100, 100);

            SetDimensoesAnimacao(animacao, 100,100);

            GetXYAnimacao(animacao, &x, &y);
            yAnterior = y;
            xAnterior = x;

            //setando o estado do personagem
            plataformaAtual = 0;
            parado = true;
            andando = false;
            pulando = false;
            caindo = false;

            //Configurando a colisão do personagem
            int xs[4] = {15, 15, 80, 80};
            int ys[4] = {6, 70, 6, 70};

            DefineAreaColisaoAnimacao(animacao, xs, ys, 4);
            DefineTipoColisaoAnimacao(animacao, PIG_COLISAO_POLIGONO);

            // iniciando os timers de pulo
            timerPulo = CriaTimer();
            timerDano = CriaTimer();
    }

    /*Função responsável pela movimentação do personagem, mudando os
        estados e atualizando as posições */
    void MovePersonagem(PIG_Teclado& meuTeclado, vector<int>& plat) {

            GetXYAnimacao(animacao, &xAnterior, &yAnterior); // guardando a posiçao nas variaveis auxiliar

            if(TempoDecorrido(timerTeclado) > 0.03) {

                if(meuTeclado[PIG_TECLA_DIREITA] != 0) { // andando para a direita
                    andando = true;
                    parado = false;
                    SetFlipAnimacao(animacao, PIG_FLIP_NENHUM); // flipando a imagem para o lado direito

                    DeslocaAnimacao(animacao, +5, 0);
                    DeslocaCamera(+5, 0); // movendo a câmera para acompanhar o personagem

                }else if(meuTeclado[PIG_TECLA_ESQUERDA] != 0) { // andando para a esquerda
                    andando = true;
                    parado = false;
                    SetFlipAnimacao(animacao, PIG_FLIP_HORIZONTAL); // flipando o personagem para a esquerda

                    DeslocaAnimacao(animacao, -5, 0);
                    DeslocaCamera(-5, 0);// movendo a câmera para acompanhar o personagem

                }else { // mudando o estado do personagem para parado, caso não tenha tecla pressionada
                    andando = false;
                    parado = true;
                }

                GetXYAnimacao(animacao, &x, &y); // guardando a nova posição do personagem nas variáveis

                if(!pulando && !caindo) {
                        /* Se o personagem não estiver caindo e o pulo não tiver sido acionado
                            seu estado mudara e o timer do pulo vai recomeçar
                        */
                    if(meuTeclado[PIG_TECLA_CIMA] != 0 || meuTeclado[PIG_TECLA_BARRAESPACO] != 0) {
                        ReiniciaTimer(timerPulo);
                        pulando = true;
                        parado = false;
                        andando = false;
                        salto = y++; // salto recebe y+1 para marcar a posição inicial do pulo
                    }
                }

                if(pulando) { // se o estado do personagem pulando for verdadeiro, sua posição será atualizada
                    y = pulo();
                    MoveAnimacao(animacao, x, y);
                }else if(caindo) { // se o estado do personagem caindo for verdadeiro, sua posição será atualizada
                    y = queda();
                    MoveAnimacao(animacao, x, y);
                }


                mudaAnimacao();
                plataformaAtual = VerificaColisao(plat); // verifica se não ouve colisão e guarda a plataforma
                                                                            // em que se encontra o personagem
                if(plataformaAtual == -1) {
                        /*se o personagem não estiver em nenhuma plataforma e
                            e já não estiver caindo ou pulando, significa que ele deve começar a cair
                            */
                    if(!pulando && !caindo) {
                        salto = y;
                        ReiniciaTimer(timerPulo);
                        caindo = true;
                    }
                }else{
                   // MoveAnimacao(animacao, x, y);  trecho comentado por mal funcionamento
                }

                yAnterior = y;
                xAnterior = x;
                ReiniciaTimer(timerTeclado);
            }
    }

    // Função responsável por verificar se o personagem está sofrendo dano
    void VerificaDano() {
        // O personagem pode receber dano a cada 0.5 segundos
        if(TempoDecorrido(timerDano) > 0.5) {
            //Se a posição do personagem for negativa no eixo y, ele perde dano
            if(y < 0) {
                vida = vida - 1;
            }
             ReiniciaTimer(timerDano);
        }
    }

};




#endif // PERSONAGEM_H_INCLUDED
