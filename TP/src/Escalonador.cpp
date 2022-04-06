#include "Escalonador.h"
#include <iostream>
#include <string>
#include <fstream>
#include "msgassert.h"


/**
* -Descricao: construtor do escalonador, que declara uma FilaEncadeada
* -Entrada: N/A
* -Saida: N/A
*/
Escalonador::Escalonador(){
    fila = new FilaEncadeada();
}

/**
* -Descricao: verifica se a url eh valida de acordo com condicoes estabelecidas
* -Condicoes para validade: protocolo ser http, 
                            nao possuir extensoes .jpg, .gif, .mp3, .avi, .doc e .pdf
* -Entrada: url
* -Saida: true, se atender a todos os criterios
*         false, se for invalida
*/
bool validaUrl(std::string url){

    //verificacao para evitar urls vazias
    if(url == ""){
        return false;
    }

    //caso a URL tenha "#", todo caractere apos nao sera considerado na validacao
    if(url.find("#") != std::string::npos){
        url = url.erase(url.find("#"));
    }

    if(url.find("http") == std::string::npos){
        return false;
    }

    else if(url.find(".jpg") != std::string::npos){
        return false;
    }

    else if(url.find(".pdf") != std::string::npos){
        return false;
    }

    else if(url.find(".gif") != std::string::npos){
        return false;
    }

    else if(url.find(".mp3") != std::string::npos){
        return false;
    }

    else if(url.find(".avi") != std::string::npos){
        return false;
    }

    else if(url.find(".doc") != std::string::npos){
        return false;
    }

    else{
        return true;
    }
}

/**
* -Descricao: identifica o host de uma URL
* -Entrada: url
* -Saida: host
*/
std::string identificaHost(std::string url){
    std::string host;

    //ponteiro para a posicao apos "//"
    std::size_t pos = url.find_first_of("//");

    //caso url tenha "www.", esses caracteres 
    //nao serao considerados no host
    if(url.find("www.") != std::string::npos){
        std::size_t pos2 = url.find_first_of("www.");
        host = url.substr(pos2+4);
    }

    else{
        host = url.substr(pos+2);
    }

    //caso url tenha subdiretorios, 
    //estes serao desconsiderados no host
    if(host.find("/") != std::string::npos){
        host.erase(host.find_first_of("/"));
    }

    return host;
}

/**
* -Descricao: remove "www", "/" no final e tudo apos "#" na URL
* -Entrada: url
* -Saida: aux3 (chamada url refinada)
*/
std::string refinaUrl(std::string url){
    std::string aux1, aux2, aux3;

    //caso a URL termine com "/", o caractere final sera desconsiderado
    if(url[url.size()-1] == '/'){
        url.pop_back();
    }

    aux3 = url;

    //caso a URL tenha "www"
    if(url.find("www.") != std::string::npos){
        //apontador para "www"
        std::size_t pos = url.find_first_of("www.");
        //parte inicial, antes do "www"
        aux1 = url;
        aux1.erase(pos);
        //parte final, depois do "www"
        aux2 = url.substr(pos+4);
        //concatencao final sem o "www"
        aux3 = aux1 + aux2;
    }

    //caso a URL tenha "#", todo caractere apos sera descartado
    if(aux3.find("#") != std::string::npos){
        aux3 = aux3.erase(aux3.find("#"));
    }

    return aux3;
}

/**
* -Descricao: calcula a profundidade da url de acordo com o numero de "/"
* -Entrada: url
* -Saida: cont(profundidade)
*/
int calculaProfundidade(std::string url){
    int cont = 0;
    std::string aux;
    
    //caso a URL termine com "/", o caractere final sera 
    //desconsiderado no calculo da profundidade
    if(url.back() == '/'){
        url.pop_back();
    }

    //gera nova url que desconsidera o protocolo, 
    //apenas para contabilizar profundidade
    std::size_t pos = url.find_first_of("//");
    aux = url.substr(pos+2);

    //conta numero de "/"
    for(int i=0; i<(int)aux.size(); i++){
        if(aux[i] == '/'){
            cont ++;
        }
    }

    return cont;
}

/**
* -Descricao: insere url em lista conforme sua profundidade
* -Entrada: lista (referencia), url
* -Saida: N/A
*/
void Escalonador::InsereUrl(ListaEncadeada &lista, std::string url){
    int profundidade = 0;
    bool inserido = false;
    profundidade = calculaProfundidade(url);

    //ponteiro para a primeira celula valida da lista
    Celula <std::string>* q;
    q = lista.primeiro->prox;

    //se a lista nao estiver vazia, a insercao se dara conforme a profundidade da url
    if(lista.GetTamanho()>0){
        //se a url ja estiver na lista, nao havera insercao
        if(lista.Pesquisa(url)){
            std::cout << std::endl << "Aviso: a URL '" << url << "' ja esta listada" << std::endl;
            return;
        }

        //laco que navega por todas as posicoes validas da lista
        for(int i = 1; i<=lista.GetTamanho(); i++){
            //se a profundidade da url nova for maior que a profundidade da url avaliada
            if(profundidade>=calculaProfundidade(q->item)){
                //e se a profundidade na nova url for menor que a proxima url na lista 
                //url sera adicionada ali no meio
                if(q->prox != nullptr && profundidade<calculaProfundidade(q->prox->item)){
                    lista.InsereApos(url, i);
                    inserido = true;
                    break;
                }
                //se a proxima celula da lista for nula, isto e, se essa for 
                //a ultima celula da lista, a url sera adicionada ao final da lista
                //OBS: insereApos trata da devida setagem dos apontadores da lista
                else if(q->prox == nullptr){
                    lista.InsereApos(url, i);
                    inserido = true;
                    break;
                }
            }
            q = q->prox;
        }

        //se a profundidade da url for menor que a de todas as URLs da lista
        if(!inserido){
            lista.InsereInicio(url);
        }
    }

    //se a lista estiver vazia, a url sera inserida na primeira posicao
    else{
        lista.InsereInicio(url);
    }
}

/**
* -Descricao: inclui quantidade urls obtidas de arquivoEntrada 
*  na fila do escalonador de acordo com seu host e profundidade
* -Entrada: quantidade, arquivoEntrada
* -Saida: N/A
*/
void Escalonador::AdicionaUrls(int quantidade, std::ifstream &arquivoEntrada){
    int cont = 0;
    int profundidade;
    std::string aux, host, refinada;

    //processamento das URLs conforme quantidade solicitada
    for(cont=0; cont<quantidade; cont++){
        //parametro '\r' no getline, para que o '\r' seja desconsiderado 
        //o '\r' eh inserido no windows e fica como sobra da string no getline (delim)
        getline(arquivoEntrada, aux);
        //o '\r' eh inserido no windows e fica como sobra da string no getline (delim)
        if(aux.back() == '\r'){
            aux.pop_back();
        }

        //caso o primeiro caractere da string seja um '\n', o '\n' sera desconsiderado
        if(aux.front() == '\n'){
           aux = aux.substr(1);
        }

        //verificacao se o url tem formato valido
        if(!validaUrl(aux)){
            std::cout << std::endl 
            << "Aviso: a URL '" << aux << "' nao segue o formato esperado e foi ignorada" 
            << std::endl;

            std::cout << std::endl 
            << "========================================================================" 
            << std::endl;
            continue;
        }

        //procedimeto de identificacao da host na url
        host = identificaHost(aux);

        //URL eh refinada para que se desconsidere o "www", 
        //a "/" no final e tudo apos o caractere "#", caso haja
        refinada = refinaUrl(aux);
        
        //impressoes para acompanhamento no terminal
        std::cout << std::endl << "URL original: " << aux <<std::endl;
        std::cout << std::endl << "URL refinada: " << refinada <<std::endl;
        std::cout << std::endl << "host: " << host << std::endl;
        profundidade = calculaProfundidade(aux);
        std::cout << std::endl << "profundidade: " << profundidade << std::endl;
        std::cout << std::endl << "==============================" << std::endl;

        
        //se o host ja estiver na fila
        if(fila->PesquisaHost(host)){
            //ponteiro para a ListaEncadeada (item de Celula) de urls do host
            Celula<ListaEncadeada>* p = fila->GetListaHost(host);

            //insere refinada na lista
            InsereUrl(p->item, refinada);
        }

        //se o host nao estiver na fila
        else{
            //cria nova lista referente a host
            ListaEncadeada nova_lista;
            nova_lista.host = host;

            //insere refinada na lista
            InsereUrl(nova_lista, refinada);

            //enfileira a nova lista
            fila->Enfileira(nova_lista);
        }
    }
}

/**
* -Descricao: Escalona todas as URLs seguindo as regras estabelecidas  
*  previamente em sua inserçao na fila 
*  (imprime em arquivoSaida e remove da respectiva ListaEncadeada)
* -Obs: nao remove os hosts da fila, estes conservam sua posicao 
*  mesmo que a sua lista de urls fique vazia
* -Entrada: arquivoSaida
* -Saida: impressao em arquivo
*/
void Escalonador::EscalonaTudo(std::ofstream &arquivoSaida){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, escalonamento abortado" << std::endl;
        return;
    }
    
    Celula<ListaEncadeada>* r;

    //ponteiro para primeiro item valido da fila
    r = fila->frente->prox;

    //navega por todas as celulas da fila (item tipo ListaEncadeada),
    //imprime seus itens no arquivo e remove as urls das listas impressas
    while(r!=nullptr){
        r->item.ImprimeArquivo(arquivoSaida);
        r->item.Limpa(); 
        r = r->prox;
    }
}

/**
* -Descricao: Escalona quantidade URLs seguindo as regras estabelecidas  
*  previamente em sua inserçao na fila 
*  (imprime em arquivoSaida e remove da respectiva ListaEncadeada)
* -Obs: nao remove os hosts da fila, estes conservam sua posicao 
*  mesmo que a sua lista de urls fique vazia
* -Entrada: quantidade, arquivoSaida
* -Saida: impressao em arquivoSaida
*/
void Escalonador::Escalona(int quantidade, std::ofstream &arquivoSaida){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, escalonamento abortado" << std::endl;
        return;
    }

    //contador principal
    int cont = 0;

    //contador auxiliar para quando a lista 
    //possui mais urls que a quantidade a escalonar
    int cont2 = 0;

    //armazena a posicao atual do elemento da lista
    int pos = 0;

    //ponteiro para celula da fila (item eh uma ListaEncadeada)
    Celula<ListaEncadeada>* p;

    //ponteiro para celula da ListaEncadeada (item eh uma string - URL)
    Celula<std::string> *q;

    //ponteiro para primeiro item valido item da fila
    p = fila->frente->prox;

    //navega por todas as celulas da fila (item tipo ListaEncadeada),
    //imprime seus itens no arquivo e remove as urls das listas impressas
    //conforme quantidade
    while(p!=nullptr && cont<quantidade){
        //se a lista tem mais URLs que a quantidade restante a escalonar,
        //escalona apenas essa quantidade
        if(p->item.GetTamanho()>quantidade-cont){
            //a posicao a ser removida sera sempre a primeira
            pos = 1;
            //q eh o primeiro item valido da lista
            q = p->item.primeiro->prox;
            cont2 = 0;

            //navega pela lista, escalonando seus elementos
            while(cont2<quantidade-cont){
                arquivoSaida << q->item << std::endl;
                p->item.RemovePosicao(pos);
                q = q->prox;
                cont2++;
            }
        }

        //se a lista tem menos ou o mesmo numero de urls que quantidade, escalona todas as suas urls
        else{
            cont = cont + p->item.GetTamanho();
            p->item.ImprimeArquivo(arquivoSaida);
            p->item.Limpa();
        }

        p = p->prox;
    }
}

/**
* -Descricao: escalona quantidade urls da lista de urls de host
* -Entrada: host, quantidade
* -Saida: impressao em arquivo
*/
void Escalonador::EscalonaHost(std::string host, int quantidade, std::ofstream &arquivoSaida){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, escalonamento abortado" << std::endl;
        return;
    }

    //contador principal
    int cont = 0;

    //armazena a posicao atual do elemento da lista
    int pos = 0;

    //ponteiro para celula da fila (item eh uma ListaEncadeada)
    Celula<ListaEncadeada>* p;

    //ponteiro para celula da ListaEncadeada (item eh uma string - url)
    Celula<std::string> *q;

    //obtem ponteiro para a celula em que esta a ListaEncadeada 
    //correspondente a host. p->item eh a ListaEncadeada
    //Obs: caso nao haja, o proprio metodo lanca uma excecao
    p = fila->GetListaHost(host);
    //se o host nao esta na fila do escalonador, aborta a operacao 
    //a funcao GetListaHost lancara excecao
    if(p == nullptr){
        return;
    }

    //se a lista tem mais urls que quantidade, apenas quantidade urls serao escalonadas
    if(p->item.GetTamanho()>quantidade){
        //q eh o primeiro elemento valido da lista, cujo item eh uma url
        q = p->item.primeiro->prox;

        //a posicao a ser removida sera sempre a primeira
        pos = 1;
        cont = 0;

        //navega pela lista, escalonando urls
        while(cont<quantidade){
            arquivoSaida << q->item << std::endl;
            p->item.RemovePosicao(pos);
            q = q->prox;
            cont++;
        }
    }

    //se a lista tem quantidade elementos ou menos, todas as suas urls serao escalonadas
    else{
        p->item.ImprimeArquivo(arquivoSaida);
        p->item.Limpa();
    }
}


/**
* -Descricao: imprime todas as urls do host em arquivoSaida
* -Entrada: host, arquivoSaida
* -Saida: impressao em arquivoSaida
*/
void Escalonador::VerHost(std::string host, std::ofstream &arquivoSaida){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, comando VER_HOST abortado" << std::endl;
        return;
    }

    //ponteiro para celula da fila (item eh uma ListaEncadeada)
    Celula<ListaEncadeada>* p;

    //ponteiro para celula da ListaEncadeada (item eh uma string - url)
    Celula<std::string> *q;

    //obtem ponteiro para a celula em que esta a ListaEncadeada 
    //correspondente a host. p->item eh a ListaEncadeada
    //Obs: caso nao haja, o proprio metodo lanca uma excecao
    p = fila->GetListaHost(host);
    //se o host nao esta na fila do escalonador, aborta a operacao 
    //a funcao GetListaHost lancara excecao
    if(p == nullptr){
        return;
    }

    //q eh o primeiro elemento valido da lista, cujo item eh uma url
    q = p->item.primeiro->prox;
    if(q == nullptr){
        std::cout << std::endl << "Aviso: Lista do host '" << host <<  "' vazia, comando VER_HOST abortado" << std::endl;
        return;
    }

    //navega pelas celulas da lista, imprimindo seus itens em arquivoSaida
    while(q != nullptr){
        arquivoSaida << q->item << std::endl;
        q = q->prox;
    }

}

/**
* -Descricao: imprime em arquivo saida todos os hosts  
*  da fila do escalonador na ordem em que foram conhecidos
* -Entrada: arquivoSaida
* -Saida: impressao em arquivoSaida
*/
void Escalonador::ListaHosts(std::ofstream &arquivoSaida){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, listagem de hosts abortada" << std::endl;
        return;
    }

    //ponteiro para celula da fila (item eh uma ListaEncadeada)
    Celula<ListaEncadeada>* p;

    //p eh o primeiro elemento valido da fila
    p = fila->frente->prox;

    //navega pelas celulas da fila, imprimindo seus hosts
    while(p != nullptr){
        arquivoSaida << p->item.host << std::endl;
        p = p->prox;
    }

}

/**
* -Descricao: remove todas as urls da lista de host
* -Entrada: host
* -Saida: N/A
*/
void Escalonador::LimpaHost(std::string host){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, limpeza de hosts abortada" << std::endl;
        return;
    }

    //ponteiro para celula da fila (item eh uma ListaEncadeada)
    Celula<ListaEncadeada>* p;

    //obtem ponteiro para a celula em que esta a ListaEncadeada 
    //correspondente a host. p->item eh a ListaEncadeada
    //Obs: caso nao haja, o proprio metodo lanca uma excecao
    p = fila->GetListaHost(host);
    //se o host nao esta na fila do escalonador, aborta a operacao 
    //a funcao GetListaHost lancara excecao
    if(p == nullptr){
        return;
    }

    //remove todos os itens da lista
    p->item.Limpa();
}

/**
* -Descricao: remove todas as celulas da fila do escalonador
*  logo, remove todos os hosts e urls
* -Entrada: host
* -Saida: N/A
*/
void Escalonador::LimpaTudo(){
    fila->Limpa();
}


/**
* -Descricao: imprime todas as urls na fila do escalonador
* -Entrada: N/A
* -Saida: impressao em stdout
*/
void Escalonador::ImprimeTudo(){
    //verifica se a fila esta vazia
    if(fila->GetTamanho()<=0){
        std::cout << std::endl << "Aviso: Fila vazia, impressao de tudo abortada" << std::endl;
        return;
    }

    Celula<ListaEncadeada>* r;

    //ponteiro para primeiro item da fila
    r = fila->frente->prox;

    //navega por todas as celulas da fila e as imprime
    std::cout << std::endl;
    while(r!=nullptr){
        r->item.Imprime();
        r = r->prox;
    }

    std::cout << std::endl;
}