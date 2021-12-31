#ifndef MUNDO_H_INCLUDED
#define MUNDO_H_INCLUDED

#include <vector>

class Mundo {
public:
    int qtdPisos;
    vector<int> plataformas;

    Mundo(int pisos) {
        qtdPisos = pisos;
    }

    void CriaChao() {
        for( int i = 0; i < qtdPisos; i++) {
            int chao = CriaObjeto("..//imagens//chao.png");
            MoveObjeto(chao,i*100, 0);
            SetDimensoesObjeto(chao, 50, 100);
            plataformas.push_back(chao);
        }
    }

    void DesenhaChao() {
        for(int i = 0; i < qtdPisos; i++) {
            DesenhaObjeto(plataformas[i]);
        }
    }

};


#endif // MUNDO_H_INCLUDED
