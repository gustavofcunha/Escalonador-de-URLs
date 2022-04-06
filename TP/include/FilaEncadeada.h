#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

#include "ListaEncadeada.h"

/**
* -Descricao: esta classe implementa uma fila de listas
* encadeadas utilizando implementação com apontadores
* -Obs: possui celula cabeca
*/
class FilaEncadeada {

    public:
        FilaEncadeada();
        ~FilaEncadeada();
        int GetTamanho();
        bool Vazia();
        void Enfileira(ListaEncadeada lista);
        ListaEncadeada Desenfileira();
        void Limpa();
        bool PesquisaHost(std::string host);
        Celula<ListaEncadeada>* GetListaHost(std::string host);


    private:
        int tamanho;
        Celula <ListaEncadeada>* frente;
        Celula <ListaEncadeada>* tras;
    friend class Escalonador;
};

#endif