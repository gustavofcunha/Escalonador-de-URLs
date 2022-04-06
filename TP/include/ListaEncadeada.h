#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <string>
#include "Celula.h"

/**
* -Descricao: esta classe implementa uma lista encadeada (utiliza apontadores)
*  referente a um host que, por sua vez, possui urls contidos em strings em suas celulas
* -Obs: possui celula cabeca
*/
class ListaEncadeada {

    public:
        ListaEncadeada();
        ~ListaEncadeada();
        int GetTamanho();
        bool Vazia();
        std::string GetItem(int pos);
        void InsereInicio(std::string item);
        void InsereFinal(std::string item);
        void InsereApos(std::string item, int pos);
        std::string RemovePosicao(int pos);
        bool Pesquisa(std::string item);
        void Imprime();
        void ImprimeArquivo(std::ofstream &arquivo);
        void Limpa();

    private:
        int tamanho;
        std::string host;
        Celula <std::string>* primeiro;
        Celula <std::string>* ultimo;
        Celula <std::string>* Posiciona(int pos, bool antes);
    friend class FilaEncadeada;
    friend class Escalonador;
};

#endif