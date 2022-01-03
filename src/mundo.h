    #ifndef MUNDO_H_INCLUDED
    #define MUNDO_H_INCLUDED

    #include <vector>

    class Mundo {
    public:
        int qtdPisos;     //  variavel que guarda a quantiade de pisos da fase
        vector<int> plataformas;  // vetor que guarda as plataformas da fase

        // construtor da classe que recebe a quantidade de pisos
        Mundo(int pisos) {
            qtdPisos = pisos;
        }

        // Função responsável por criar as plataformas da fase
        void CriaChao() {
            //carrega a plataforma do arquivo e as posicona no mundo
            for( int i = 0; i < qtdPisos; i++) {
                int chao = CriaObjeto("..//imagens//chao.png");
                if(i == 3) {
                    MoveObjeto(chao,i*100, 180);
                }else if(i == 5) {
                    MoveObjeto(chao,i*100, 50);
                }else{
                    MoveObjeto(chao,i*100, 0);
                }
                SetDimensoesObjeto(chao, 50, 100);
                plataformas.push_back(chao);      // Adiciona a nova plataforma na lista
            }
        }

        // Função responsável por desenhar o chão na tela
        void DesenhaChao() {
            for(int i = 0; i < qtdPisos; i++) {
                DesenhaObjeto(plataformas[i]);
            }
        }

    };


    #endif // MUNDO_H_INCLUDED
