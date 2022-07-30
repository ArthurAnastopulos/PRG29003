//Projeto 02 - Estatísticas sobre atores e filmes.
//Nome: Arthur Anastopulos dos Santos
//Data de entrega: 19/09/2019

//Bibliotecas utilizadas no projeto.
#include <iostream>
#include <prglib.h>
#include <string>
#include "projeto2.h"

using namespace std;

//Função para digitar a escolha do usuário.
string escolha_info(string & escolha) {
    cout << "Digite:  ";

    while(true){
        getline(cin,escolha);
        if(escolha.size() != 0)break;
    }
    cout << endl;

    return escolha;
}

//Funções seguintes servem para escrever na tela ao usuario a resposta das informações.

void escreve_hollywood (lista<hollywood> & lista) {
    lista.inicia();
    while(! lista.fim()) {
        hollywood aux = lista.proximo();
        cout << "-->  Filme:  " << aux.filme << " " << "--> Ano do Filme:  "<< aux.ano << endl;
    }
}

void escreve_papeis (lista<papeis> & lista) {
    lista.inicia();
    while(! lista.fim()) {
        papeis aux = lista.proximo();
        cout << "--> Ator:  " << aux.ator << " " << "--> Quantidade de filmes em que atuaram:  " << aux.atuacoes << endl;
    }
}

void escreve_comum (lista<comum> & lista) {
    lista.inicia();
    while(! lista.fim()) {
        comum aux = lista.proximo();
        cout << aux.ator << endl;
    }
}

void escreve_atores(lista<string> & lista) {
    lista.inicia();
    while(! lista.fim()) {
        string aux = lista.proximo();
        cout <<"--> Ator:  " << aux << endl;
    }
}

void escreve_busca(lista<string> & lista, string & escolha) {
    cout << "--> Ator utilizado:  " << escolha << endl;

    lista.inicia();
    while(! lista.fim()) {
        string aux = lista.proximo();
        cout << "--> Ator:  " <<aux << endl;
    }
}

//Main do programa, onde a interface ao usuario esta escrita.

int main() {
    //Local do arquivo.
    string path = "../data/dados.txt";

    cout << "============ Bem Vindo! ============" << endl << " -> Ao  Programa de estatísticas sobre atores e filmes: " << endl;

    cout << endl;

    //Obtem o "mapa" dasn informações do arquivo.
    lista <info> Mapa = mapa(path);

    cout << "Escolha uma das informações possíveis, digitando um número: " << endl << "[1] - Os filmes em que um ator atuou." << endl;
    cout << "[2] - Os atores que atuaram em um dado filme." << endl << "[3] - Os atores que trabalharam com um dado ator." << endl;
    cout << "[4] - A listagem ordenada de atores, de acordo com a quantidade de filmes em que atuaram." << endl << "[5] - Para um dado ator, a listagem ordenada de atores de acordo com a quantidade de filmes em que atuaram em comum." << endl;

    //Digita a opção e verifica se o usario, escolheu um valor correspondente a uma função.
    string opcao;
    int conv = 0; //conversor para stoi.
    cout << "Agora digite sua opção: ";
    while(true) {
        getline(cin,opcao);
        conv = stoi(opcao);
        if(conv <= 5 && conv != 0)break;
    }

    //Variaveis usadas para armazenar as informações das funções.
    string escolha; //escolha de filme ou ator.
    lista <hollywood> search_filmes; // lista de filmes procurados.
    lista <string> search_atores; //lista de atores procurados.
    lista <string> busca_ator; //lista de ator busca apartir de um ator.
    lista <papeis> list_ator; // lista ator e a quantidade de seus papeis.
    lista <comum> list_comum; //lista de ator e seus filmes em comum.

    //Switchcase para escolhas, e em seguida rodar as informações.
    switch (conv) {

        case 1:
            cout << "Busca de filmes em que um ator atuou; digite inicialmente o nome de um ator." << endl;
            escolha_info(escolha);
            obtem_filmes(Mapa, search_filmes, escolha);
            escreve_hollywood(search_filmes);
            break;

        case 2:
            cout << "Busca de atores que atuaram em um dado filme; digite inicialmente o nome de um filme." << endl;
            escolha_info(escolha);
            obtem_atores(Mapa,search_atores,escolha);
            escreve_atores(search_atores);
            break;

        case 3:
            cout << "Busca dos atores que trabalharam com um dado ator; digite inicialmente o nome de um ator." << endl;
            escolha_info(escolha);
            busca_atores(Mapa,busca_ator,escolha);
            escreve_busca(busca_ator,escolha);
            break;

        case 4:
            cout << "A listagem ordenada de atores, de acordo com a quantidade de filmes em que atuaram." << endl;
            todos_atores(Mapa, search_atores);
            ordena_atores_atuar(Mapa,list_ator,search_atores);
            escreve_papeis(list_ator);
            break;

        case 5:
            cout << "A listagem ordenada de atores de acordo com a quantidade de filmes em que atuaram em comum; digite o ator." << endl;
            escolha_info(escolha);
            ordena_atores_comum(Mapa,list_comum,escolha);
            escreve_comum(list_comum);
            break;

    }

    //Fim do programa.
    return 0;

}
