#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "FilaEncadeada.h"

/**
* -Descricao: Esta classe implementa um escalonador,
* que possui uma fila de listas. Cada lista possui um 
* host certo numero de urls.
*/

class Escalonador{

    public:
        Escalonador();
        void AdicionaUrls(int quantidade, std::ifstream &arquivoEntrada);
        void EscalonaTudo(std::ofstream &arquivoSaida);
        void Escalona(int quantidade, std::ofstream &arquivoSaida);
        void EscalonaHost(std::string host, int quantidade, std::ofstream &arquivoSaida);
        void VerHost(std::string host, std::ofstream &arquivoSaida);
        void ListaHosts(std::ofstream &arquivoSaida);
        void LimpaHost(std::string host);
        void LimpaTudo();
        void InsereUrl(ListaEncadeada &lista, std::string url);
        void ImprimeTudo();
        
    private:
        FilaEncadeada *fila;
};


#endif