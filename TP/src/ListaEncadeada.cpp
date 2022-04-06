#include "ListaEncadeada.h"
#include "msgassert.h"
#include "memlog.h"
#include <iostream>
#include <fstream>

//ATENCAO: A POSICAO PASSADA COMO PARAMETRO COMECA A CONTAR A PARTIR DE 1 E NAO CONSIDERA A CELULA CABECA

/**
* -Descricao: Construtor
* -Entrada: _host
* -Saida: N/A
*/
ListaEncadeada::ListaEncadeada(){
    tamanho = 0;
    primeiro = new Celula<std::string>;
    ultimo = primeiro;
}

/**
* -Descricao: Destrutor
* -Entrada: N/A
* -Saida: N/A
*/
ListaEncadeada::~ListaEncadeada(){
    if(tamanho!=0){
        Limpa();
    }
}

/**
* -Descricao: retorna o tamanho da lista encadeada
* -Entrada: N/A
* -Saida: tamanho
*/
int ListaEncadeada::GetTamanho(){
    return tamanho;
}

/**
* -Descricao: retorna true se a lista encadeada 
* esta vazia e false caso contrario
* -Entrada: N/A
* -Saida: true ou false
*/
bool ListaEncadeada::Vazia(){
    return (tamanho==0);
}

/**
* -Descricao: posiciona um ponteiro em pos
* tambem posiciona uma celula antes, caso antes = true 
* -Entrada: pos, antes
* -Saida: ponteiro para celula em pos
*/
Celula <std::string>* ListaEncadeada::Posiciona(int pos, bool antes){
    //verifica se a posicao pos eh valida
    erroAssert(pos>0 && pos<=tamanho, "Posicao invalida");
    
    Celula <std::string>* p; 
    int i;
    
    //faz p apontar para a celula em pos-1
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->prox;
    }
    
    //faz p apontar para a celula em pos, caso antes == false
    if(!antes){
        p = p->prox;
    }

    return p;
}

/**
* -Descricao: retorna item na posicao pos
* -Entrada: pos
* -Saida: item na posicao pos
*/
std::string ListaEncadeada::GetItem(int pos){
    //verifica se a posicao pos eh valida
    erroAssert(pos>0 && pos<=tamanho, "Posicao invalida");

    //apontador que recebe a celula na posicao pos
    Celula<std::string>* p;
    p = Posiciona(pos,false);

    return p->item;
}

/**
* -Descricao: insere item no inicio da ListaEncadeada
* -Entrada: item
* -Saida: N/A
*/
void ListaEncadeada::InsereInicio(std::string item){
    //criacao da nova celula
    Celula<std::string> *nova;
    nova = new Celula<std::string>();

    //insercao da nova celula no inicio
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    escreveMemLog((long int)(&(nova)), sizeof(Celula<std::string>*), 0);

    //se o nova for o ultimo elemento inserido, 
    //o atrubuto ultimo apontara para nova
    if(nova->prox == nullptr){
        ultimo = nova;
    }
}

/**
* -Descricao: insere item no final da ListaEncadeada
* -Entrada: item
* -Saida: N/A
*/
void ListaEncadeada::InsereFinal(std::string item){
    //criacao da nova celula
    Celula<std::string> *nova;
    nova = new Celula<std::string>();

    //insercao da nova celula no final e setagem de apontadores
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
    escreveMemLog((long int)(&(nova)), sizeof(Celula<std::string>*), 0);
}

/**
* -Descricao: insere item na posicao pos+1
* -Entrada: item, pos
* -Saida: N/A
*/
void ListaEncadeada::InsereApos(std::string item, int pos){
    //verifica se a posicao pos eh valida, se a lista nao estiver vazia
    erroAssert(pos>0 && pos<=tamanho+1, "Posicao invalida");
    
    Celula<std::string> *p, *nova;

    //ponteiro para a celula na posicao pos
    p = Posiciona(pos,false);
    
    //procedimentos de insercao em pos+1
    nova = new Celula<std::string>();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    
    tamanho++;

    escreveMemLog((long int)(&(nova)), sizeof(Celula<std::string>*), 0);
    
    //se o nova for o ultimo elemento inserido, 
    //o atrubuto ultimo apontara para nova
    if(nova->prox == nullptr){
        ultimo = nova;
    }
}

/**
* -Descricao: remove item na posicao pos
* -Entrada: pos
* -Saida: item removido
*/
std::string ListaEncadeada::RemovePosicao(int pos){
    //verifica se a posicao pos eh valida
    erroAssert(pos>0 && pos<=tamanho, "Posicao invalida");
    //verifica se a lista esta vazia
    erroAssert(tamanho>0, "Lista vazia");
    
    std::string aux;
    Celula<std::string> *p, *q;
    
    //ponteiro para a posicao pos-1
    p = Posiciona(pos, true);

    //procedimentos de remocao
    q = p->prox;
    p->prox = q->prox;

    tamanho--;

    aux = q->item;
    delete q;

    //se o elemento removido era o ultimo da lista, 
    //o elemento anterior passa a ser o ultimo
    if(p->prox == nullptr){
        ultimo = p;
    }
    
    return aux;
}

/**
* -Descricao: verifica se um item esta na lista encadeada
* -Entrada: item
* -Saida: o proprio item, se ele estiver na lista ou
* string "0", caso contrario
*/
bool ListaEncadeada::Pesquisa(std::string _item){
    //verifica se a lista esta vazia
    erroAssert(tamanho>0, "Lista vazia");

    Celula<std::string> *p;
    p = primeiro->prox;

    //procura pelo item enquanto navega pelas celulas da lista
    //o loop eh interrompido, caso _item seja encontrado 
    //e true eh retornado
    while(p != nullptr){
        leMemLog((long int)(&(p->item)), sizeof(std::string), 0);
        if(p->item == _item){
            return true;
        }
        p = p->prox;
    }

    return false;
}

/**
* -Descricao: imprime todos os itens da lista encadeada 
* -Entrada: N/A
* -Saida: impressao em stdout
*/
void ListaEncadeada::Imprime(){
    //verifica se a lista esta vazia
    if(tamanho<=0){
        std::cout << std::endl << "Aviso: Lista vazia, impressao abortada" << std::endl;
        return;
    }

    Celula<std::string> *p;
    //ponteiro para a primeira celula valida da lista
    p = primeiro->prox;

    //imprime cada item enquanto navega pelas celulas da lista
    while(p != nullptr){
        leMemLog((long int)(&(p->item)), sizeof(std::string), 0);
        std::cout << p->item << std::endl;
        p = p->prox;
    }
}

/**
* -Descricao: imprime TODOS os itens da lista encadeada em arquivo
* -Entrada: N/A
* -Saida: impressao em arquivo
*/
void ListaEncadeada::ImprimeArquivo(std::ofstream &arquivo){
    if(tamanho<=0){
        std::cout << std::endl << "Aviso: Lista vazia, impressao em arquivo abortada" << std::endl;
        return;
    }

    Celula<std::string> *p;
    //ponteiro para a primeira celula valida da lista
    p = primeiro->prox;

    int cont = 0;

    //imprime cada item enquanto navega pelas celulas da lista
    while(p != nullptr && cont<tamanho){
        leMemLog((long int)(&(p->item)), sizeof(std::string), 0);
        arquivo << p->item << std::endl;
        p = p->prox;
        cont++;
    }
}

/**
* -Descricao: deleta todas as celulas da lista encadeada
* com excecao da celula cabeca (primeiro)
* -Entrada: N/A
* -Saida: N/A
*/
void ListaEncadeada::Limpa(){
    //verifica se a lista esta vazia
    avisoAssert(tamanho>0, "Lista ja vazia");
    
    Celula<std::string> *p;
    //ponteiro para a primeira celula valida da lista
    p = primeiro->prox;
    
    //caminha pelas celulas da lista, deletando-as
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }

    //setagem de atributos para configuracao de lista vazia
    ultimo = primeiro;
    tamanho = 0;
}