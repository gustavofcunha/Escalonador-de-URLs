#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "msgassert.h"
#include "memlog.h"
#include "Celula.h"
#include "ListaEncadeada.h"
#include "FilaEncadeada.h"
#include "Escalonador.h"

//texto que sera concatenado ao nome do arquivo de 
//entrada para compor o nome do arquivo de saida
#define EXTENSAO "-out"

//comandos do escalonador
const std::string add_urls = "ADD_URLS";
const std::string escalona_tudo = "ESCALONA_TUDO";
const std::string escalona = "ESCALONA";
const std::string escalona_host = "ESCALONA_HOST";
const std::string ver_host = "VER_HOST";
const std::string lista_hosts = "LISTA_HOSTS";
const std::string limpa_host = "LIMPA_HOST";
const std::string limpa_tudo = "LIMPA_TUDO";

/**
* -Descricao: processa comandos com parametros host e quantidade e os seta por referencia
* -Entrada: buf (comando), host (referencia), quantidade(referencia)
* -Saida: N/A
*/
void processaHostQuantidade(std::string buf, std::string &host, int &quantidade){
    std::string aux;
    
    //ponteiro para o fim do comando e inicio do host
    std::size_t pos = buf.find_first_of(" ");

    //ponteiro para o fim do host e incio quantidade
    std::size_t pos2 = buf.find_last_of(" ");

    host = buf.substr(pos+1);
    //corta host para conter apenas o nome do host
    host.erase(host.find_first_of(" "));

    //identifica e seta quantidade em buf
    aux = buf.substr(pos2+1);

    //converte aux para int
    quantidade = stoi(aux);
}

/**
* -Descricao: processa comandos com parametro host
* -Entrada: buf (comando)
* -Saida: host
*/
std::string processaHost(std::string buf){
    std::string host;
    
    //ponteiro para o fim do comando e inicio do host
    std::size_t pos = buf.find(" ");
    //corta buf em host para conter apenas o nome do host
    host = buf.substr(pos+1);
    return host;
}

/**
* -Descricao: processa comandos com parametro quantidade
* -Entrada: buf (comando)
* -Saida: qtde
*/
int processaQuantidade(std::string buf){
    int qtde = -1;
    std::string aux;

    //ponteiro que encontra o fim do comando e inicio da quantidade
    std::size_t pos = buf.find_first_of(" ");
    
    //string que recebe a quantidade
    aux = buf.substr(pos+1);

    //converte aux para int
    qtde = stoi(aux);

    return qtde;
}

/**
* -Descricao: processa buf e retorna apenas o comando, sem parametros
* -Obs: como buf nao eh referencia, a alteracao nao eh feita de fato em buf
* -Entrada: buf (comando)
* -Saida: buf (encurtado)
*/
std::string splitComando(std::string buf){
    //se o comando nao tiver espaco, o proprio eh retornado
    if(buf.find_first_of(" ") == std::string::npos){
        return buf;
    }

    //caso tenha espaco, apenas o comando eh retornado
    buf.erase(buf.find_first_of(" "));
    return buf;
}

/**
* -Descricao: processa o comando e verifica se eh valido
* -Entrada: buf
* -Saida: se for valido: true
*         se nao: false
*/
bool validaComando(std::string buf){
    if(buf.find(add_urls) != std::string::npos){
        return true;
    }

    else if(buf.find(escalona_tudo) != std::string::npos){
        return true;
    }

    else if(buf.find(escalona) != std::string::npos){
        return true;
    }

    else if(buf.find(escalona_host) != std::string::npos){
        return true;
    }

    else if(buf.find(ver_host) != std::string::npos){
        return true;
    }

    else if(buf.find(lista_hosts) != std::string::npos){
        return true;
    }

    else if(buf.find(limpa_host) != std::string::npos){
        return true;
    }

    else if(buf.find(limpa_tudo) != std::string::npos){
        return true;
    }

    else{
        return false;
    }
}

/**
* -Descricao: processa o comando da linha e chama as respectivas funcoes
* -Entrada: buf, arquivoEntrada(referencia), arquivoSaida(referencia)
* -Saida: N/A
*/
void processaComando(std::string buf, std::ifstream &arquivoEntrada, 
                     std::ofstream &arquivoSaida, Escalonador &escalonador){
    
    //se o primeiro caractere do comando for um '\n', o '\n' sera desconsiderado
    if(buf.front() == '\n'){
        buf = buf.substr(1);
    }

    int quantidade;
    std::string host;
    std::string comando;

    //se o comando nao for valido o ignora e emite aviso
    if(!validaComando(buf)){
        std::cout << std::endl << "Aviso: O comando: '" << buf 
        << "' " << "no arquivo de entrada eh invalido e foi ignorado" <<std::endl;
        return;
    }

    //processa o comando e o separa de seus argumentos, se houverem
    //(argumentos serao processados posteriormente, separadamente)
    comando = splitComando(buf);

   //verifica qual eh o comando, processa argumentos, se houver e chama funcoes correspondentes
    if(comando == add_urls){
        quantidade = processaQuantidade(buf);

        std::cout << std::endl << add_urls << ": " 
        << std::endl << "qtde: " << quantidade << std::endl;

        escalonador.AdicionaUrls(quantidade, arquivoEntrada);
    }

    else if(comando == escalona_tudo){
        std::cout << std::endl << escalona_tudo << std::endl;
        escalonador.EscalonaTudo(arquivoSaida);
    }

    else if(comando == escalona){
        quantidade = processaQuantidade(buf);

        std::cout << std::endl << escalona << ": " 
        << std::endl << "qtde: " << quantidade << std::endl;

        escalonador.Escalona(quantidade, arquivoSaida);
    }

    else if(comando == escalona_host){
        processaHostQuantidade(buf, host, quantidade);

        std::cout << std::endl << escalona_host << ": " << std::endl 
        << "host: " << host << std::endl << "qtde: " << quantidade << std::endl;

        escalonador.EscalonaHost(host, quantidade, arquivoSaida);
    }

    else if(comando == ver_host){
        host = processaHost(buf);

        std::cout << std::endl << ver_host << ": " << std::endl 
        << "host: " << host << std::endl;

        escalonador.VerHost(host, arquivoSaida);
    }

    else if(comando == lista_hosts){
        std::cout << std::endl << lista_hosts << ": " << std::endl;
        escalonador.ListaHosts(arquivoSaida);
    }

    else if(comando == limpa_host){
        host = processaHost(buf);

        std::cout << std::endl << limpa_host << ": " << std::endl 
        << "host: " << host << std::endl;

        escalonador.LimpaHost(host);
    }

    else if(comando == limpa_tudo){
        std::cout << std::endl << limpa_tudo << ": " << std::endl;
        escalonador.LimpaTudo();
    }

    //essa excecao nunca deve ocorrer, pois ha uma funcao que verifica validade dos comandos antes
    else{
        std::cout << std::endl << "Aviso: Comando invalido no arquivo de entrada" <<std::endl;
        abort();
    }
}

/**
* -Descricao: funcao principal, declara Escalonador, 
*  abre e fecha arquivos e chama funcoes de processamento
* -Entrada: argc, argv
* -Saida: 0
*/
int main(int argc, char* argv[]){
    //declaracao do escalonador
    Escalonador escalonador;

    //variaveis auxiliares
    bool regmem = false;
    std::ifstream arquivoEntrada;
    std::ofstream arquivoSaida;
    std::string buf, nomeArquivoEntrada, nomeArquivoSaida, aux;

    //obtem o nome do arquivo de entrada pelos argumentos
    //da funcao main passados na linha de comando
    nomeArquivoEntrada = (std::string) argv[1];

    //inicia registro de acesso, se solicitado
    if(argc >= 3){
        iniciaMemLog(argv[2]);
        regmem = true;
    }

    //ativar registro de acesso ou nao, se solicitado
    if(argc == 4){
        ativaMemLog();
    }

    else{
        desativaMemLog();
    }
    
    //abertura do arquivo de entrada e assercao correspondente
    arquivoEntrada.open(nomeArquivoEntrada);
    erroAssert(arquivoEntrada.is_open(), "Nao foi possivel abrir o arquivo de entrada");

    //obtencao do nome do arquivo de saida concatenando EXTENSAO ao nome do arquivo de entrada
    std::size_t pos = nomeArquivoEntrada.find_first_of(".");
    aux = nomeArquivoEntrada;
    //extensao do arquivo (e.g.: "".txt")
    aux.erase(pos);
    aux = aux + EXTENSAO + nomeArquivoEntrada.substr(pos);
    nomeArquivoSaida = aux;

    //abertura do arquivo de saida para escrita e assercao correspondente
    arquivoSaida.open(nomeArquivoSaida);
    erroAssert(arquivoSaida.is_open(), "Nao foi possivel abrir o arquivo de saida");

    //caso registro de acesso esteja ativado, sera definida fase 0 (unica)
    if(argc == 4){
        defineFaseMemLog(0);
    }

    //processa as linhas do arquivo de entrada
    while(getline(arquivoEntrada, buf)){
        //o '\r' eh inserido no windows e fica como sobra da string no getline (delim)
        if(buf.back() == '\r'){
            buf.pop_back();
        }
        processaComando(buf, arquivoEntrada, arquivoSaida, escalonador);
    }

    //fechamento arquivo entrada
    arquivoEntrada.close();

    //fechamento arquivo saida
    arquivoSaida.close();

    // conclui registro de acesso, se incializado
    if(regmem){
        finalizaMemLog();
    }

    return 0;
}