#ifndef CELULA_H
#define CELULA_H

/**
* -Descricao: Esta classe implementa celulas que serao usadas em listas
* e filas. Possui itens do tipo T.
*/
template <class T> class Celula {
    public:
        //construtor simples
        Celula(){
            prox = nullptr;
        }
    
    private:
        T item;
        Celula* prox;

    friend class ListaEncadeada;
    friend class FilaEncadeada;
    friend class Escalonador;
};

#endif