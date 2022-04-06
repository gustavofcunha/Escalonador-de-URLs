#include "FilaEncadeada.h"
#include "msgassert.h"
#include "memlog.h"
#include <iostream>

/**
* -Descricao: Construtor
* -Entrada: N/A
* -Saida: N/A
*/
FilaEncadeada::FilaEncadeada(){
    frente = new Celula<ListaEncadeada>;
    tras = frente;
}

/**
* -Descricao: Destrutor
* -Entrada: N/A
* -Saida: N/A
*/
FilaEncadeada::~FilaEncadeada(){
    if(tamanho!=0){
        Limpa();
    }
    delete frente;
}

/**
* -Descricao: retorna o tamanho da fila encadeada
* -Entrada: N/A
* -Saida: tamanho
*/
int FilaEncadeada::GetTamanho(){
    return tamanho;
}

/**
* -Descricao: retorna true se a fila encadeada 
* esta vazia e false caso contrario
* -Entrada: N/A
* -Saida: true ou false
*/
bool FilaEncadeada::Vazia(){
    return (tamanho==0);
}

/**
* -Descricao: insere lista encadeada na ultima posicao da fila encadeada
* -Entrada: lista
* -Saida: N/A
*/
void FilaEncadeada::Enfileira(ListaEncadeada lista){
    Celula<ListaEncadeada>* nova;
    nova = new Celula<ListaEncadeada>();

    //procedimentos de enfileiramento
    nova->item.host = lista.host;

    //adiciona todas a celulas de lista a nova
    Celula<std::string> *p;
    p = lista.primeiro->prox;
    while(p != nullptr){
        nova->item.InsereFinal(p->item);
        p = p->prox;
    }

    //setagem de apontadores
    tras->prox = nova;
    tras = nova;
    tamanho++;
}

/**
* -Descricao: remove a primeira lista encadeada da fila encadeada
* -Entrada: N/A
* -Saida: N/A
*/
ListaEncadeada FilaEncadeada::Desenfileira(){
    erroAssert(tamanho>0, "Fila vazia");

    Celula<ListaEncadeada>* p;
    ListaEncadeada aux;

    //procedimentos de desenfileiramento
    p = frente->prox;
    frente->prox = p->prox;
    aux = p->item;
    delete p;
    tamanho--;
    return aux;
}

/**
* -Descricao: deleta todas as celulas da fila encadeada
* com excecao da celula cabeca (frente)
* -Entrada: N/A
* -Saida: N/A
*/
void FilaEncadeada::Limpa(){
    avisoAssert(tamanho>0, "Fila ja vazia");
    
    Celula<ListaEncadeada>* p;
    //ponteiro para a primeira celula valida da fila
    p = frente->prox;

    //caminha pelas ceulas da fila enquanto as deleta
    while(p!=nullptr){
        frente->prox = p->prox;
        delete p;
        p = frente->prox;
    }

    //setagem de atributos para configuracao de lista vazia
    tamanho = 0;
    tras = frente;
}

/**
* -Descricao: verifica se host ja esta na fila
* -Entrada: host
* -Saida: true (se o host procurado estiver na fila)
*  false (se o host procurado nao estiver na lista)
*/
bool FilaEncadeada::PesquisaHost(std::string host){
    Celula<ListaEncadeada>* p;
    //ponteiro para a primeira celula valida da fila
    p = frente->prox;

    //caminha pelas ceulas da fila enquanto procura pelo host
    while(p!=nullptr){
        if(p->item.host == host){
            leMemLog((long int)(&(p->item.host)), sizeof(std::string), 1);
            return true;
        }
        p = p->prox;
    }

    return false;
}

/**
* -Descricao: gera um ponteiro p para a celula da fila que contem a lista referente a host
* -Entrada: host
* -Saida: p
* -Obs: quando esta funcao eh cha
*/
Celula<ListaEncadeada>* FilaEncadeada::GetListaHost(std::string host){
    Celula<ListaEncadeada>* p;
    //ponteiro para a primeira celula valida da fila
    p = frente->prox;

    //caminha pelas ceulas da fila enquanto procura pelo host
    while(p!=nullptr){
        if(p->item.host == host){
            leMemLog((long int)(&(p->item.host)), sizeof(std::string), 1);
            return p;
        }
        p = p->prox;
    }

    std::cout << std::endl << "Aviso: O host a seguir nao existe na fila do escalonador: "  << host << std::endl;
    return nullptr;
}