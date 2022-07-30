//Projeto 03 - Novas Estatísticas sobre atores e filmes
//Nome: Arthur Anastopulos dos Santos
//Data de entrega: 04/10/2019
#include <iostream>
#include <string>
#include "Projeto03.h"
#include "prglib.h"

#define LIMITADOR 10 //Define usado para limitar os top "N" atores para as busca popularidade e quantidades de filmes q participou.

using namespace std;
using prglib::lista;
using prglib::thash;

//Função para o usuario escrever um conjunto de filmes; que ele deseja usar para a função de buscar atores que atuaram em todos os filmes de um certo conjunto de filmes.

lista<string> lista_filmes(const thash<info> tabela,lista<string> & escolhas) {
    thash<info> copia = tabela;
    string filme;

    cout << "Digite o nome dos filmes q você deseja buscar os atores.[Não digite nada quando quiser encerrar.]" << endl;
    while(true) {
        cout << "Digite: ";
        getline(cin , filme);
        if(copia.existe(filme))escolhas.anexa(filme);
        if(filme.empty())break;
        cout << endl;
    }

    return escolhas;
}

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

//Funçoes seguintes são usadas para escrever na tela as informações dos processos.

void escreve_filmes(const lista<movie> & filmes) {
    lista<movie> copia = filmes;
    copia.inicia(); //Iteração para mostrar na tela as informações da função.
    while(! copia.fim()) {
        movie aux = copia.proximo();
        cout << "Filme: " << aux.filme << " " << "Ano: " << aux.ano << endl;
    }
}

void escreve_ator_filmes(const thash<int> & atores_filmes, const lista<string> filmes) {
    thash<int> copia1 = atores_filmes;
    lista<string> copia2 = filmes;

    cout << "Conjunto de filmes: ";
    copia2.escrevaSe(cout, ";");
    cout << endl;

    auto ator = copia1.chaves();    //Iteração para mostrar na tela as informações da função.
    ator->inicia();
    while(! ator->fim()) {
        string algo = ator->proximo();
        cout << "Ator: " << algo << endl;
    }
}

void escreve_ator(const lista<string> & atores, const string & escolha) {
    lista<string> copia = atores;
    string str = escolha;

    cout << "Ator Escolhido: "  << str << endl;

    copia.inicia();     //Iteração para mostrar na tela as informações da função.
    while(! copia.fim()) {
        string ator = copia.proximo();
        cout << "Ator: " << ator << endl;
    }
}

void escreve_ator_qnt(const lista<actor> & qnt_filmes){
    lista<actor> copia = qnt_filmes;
    int N = 0; //Conta a quantidade de atores.

    copia.inicia();
    while(! copia.fim() && N != LIMITADOR) {  //Quando N chegar ao numero do limitador saí da interação.
        actor aux = copia.proximo();
        cout << "Ator: " << aux.ator << "  " <<"Quantidade de Filmes: " << aux.filmes <<endl;
        N++;
    }
}

void escreve_ator_pop(const lista<popstar> & top_ator){
    lista<popstar> copia = top_ator;
    int N = 0;

    copia.inicia();
    while(! copia.fim() && N != LIMITADOR) {
        popstar aux = copia.proximo();
        cout << "Ator: " << aux.ator << "  " <<"Popularidade: " << aux.popularidade <<endl;
        N++;
    }
}

//Main do Programa.

int main() {
    //Local do arquivo.
    string path = "../data/dados.txt";

    cout << "============ Bem Vindo! ============" << endl << " -> Ao  Programa de estatísticas sobre atores e filmes: " << endl;

    cout << endl;

    //Obtem a "tabela" das informações do arquivo.
    thash <info> tab = tabela(path);

    cout << "Escolha uma das informações possíveis, digitando um número: " << endl << "[1] - Os filmes em que um ator atuou." << endl;
    cout << "[2] - Os atores que atuaram em todos os filmes de um certo conjunto de filmes." << endl << "[3] - Os atores que trabalharam com um dado ator." << endl;
    cout << "[4] - A listagem ordenada de atores, de acordo com suas popularidades." << endl << "[5] - A listagem ordenada de atores, de acordo com a quantidade de filmes em que atuaram." << endl;

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
    lista<string> escolhas;
    lista<movie> filmes;
    lista<string> atores;
    thash<int> atores_filmes(10007);
    lista<actor>qnt_filmes;
    lista<popstar> top_ator;


    //Switchcase para escolhas, e em seguida rodar as informações.
    switch (conv) {

        case 1:
            cout << "Busca de filmes em que um ator atuou; digite inicialmente o nome de um ator." << endl;
            escolha_info(escolha);
            busca_filmes(tab,filmes,escolha);
            escreve_filmes(filmes);
            break;

        case 2:
            cout << "Busca de atores que atuaram em um conjunto de filmes; digite inicialmente o nome dos filmes." << endl;
            lista_filmes(tab,escolhas);
            atores_de_filmes(tab,atores_filmes,escolhas);
            escreve_ator_filmes(atores_filmes,escolhas);
            break;

        case 3:
            cout << "Busca dos atores que trabalharam com um dado ator; digite inicialmente o nome de um ator." << endl;
            escolha_info(escolha);
            atores_de_ator(tab,atores,escolha);
            escreve_ator(atores,escolha);
            break;

        case 4:
            cout << "A listagem ordenada de atores, de acordo com suas popularidades." << endl;
            ator_pop(tab,top_ator);
            escreve_ator_pop(top_ator);
            break;

        case 5:
            cout << "A listagem ordenada de atores, de acordo com a quantidade de filmes em que atuaram." << endl;
            ator_filmes(tab,qnt_filmes);
            escreve_ator_qnt(qnt_filmes);
            break;

    }

    //Fim do programa.
    return 0;

}
