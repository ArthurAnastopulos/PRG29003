//Projeto 03 - Novas Estatísticas sobre atores e filmes
//Nome: Arthur Anastopulos dos Santos
//Data de entrega: 04/10/2019
#include "Projeto03.h"
#include <iostream>
#include <prglib.h>

using namespace std;
using prglib::thash;
using prglib::lista;


//Função para separar as informações de um arquivo.

lista<string> separa(const string & algo, const string & sep) {
    //Variaveis auxiliares da função.
    lista <string> aux;
    int i = 0, j = 0;
    string posf;

    //laço que encontra a palavra por palavra apartir de um separador.

    while(true) {
        i = algo.find_first_not_of(sep, j);
        j = algo.find_first_of(sep, i);

        if(i == string::npos) break;
        posf = algo.substr(i, j-i);
        aux.anexa(posf);
    }

    return aux;
}

//Função que cria uma tabela das informações do arquivo.

thash<info> tabela(const string & path) {
    //Variaveis auxiliares do programa.
    ifstream arq(path);
    string aux1,aux2;
    info aux;

    //lista e  tabela auxliares do programa.
    lista<string> auxliar1;
    thash<info> auxliar2 (70007);

    //Verifica se o arquivo não é invalido e entao monta o mapa das informaçoes em uma lista.
    if(! arq.is_open()){
        cout << "Arquivo Invalido!" << endl;
        throw -1;
    }
    while(getline(arq, aux1)){
        //Usa função separa para separar as 3 informações do arquivo
        auxliar1 = separa(aux1,";");
        if( auxliar1.comprimento() == 3) { //Ao obter 3 informações da linha, anexa elas a uma tabela de estrutura(Info).
            string chave = auxliar1.obtem(0); //nome do filme.
            aux.ano = auxliar1.obtem(1); // ano do filme

            aux2 = auxliar1.obtem(2);
            aux.atores = separa(aux2, ","); //lista de atores

            auxliar2.adiciona(chave, aux);
            auxliar1.esvazia();
        }
    }

    return auxliar2;
}

//Sobrecarga de operador para o ordenamento, apatir do ano.

bool operator<(const movie & int1, const movie & int2) {
    return int1.ano < int2.ano;
}

//Função que busca os filmes em que um ator atuou.

lista<movie> busca_filmes(const thash<info> & tabela, lista<movie> & filmes, const string & escolha) {
    //Tabela e estruturas auxiliares.
    thash<info> copia = tabela;
    info aux1;
    movie aux2;

    //Inicia uma iteração das chaves da tabela(filmes) para buscar a lista de atores de cada filme.
    auto busca = copia.chaves();
    busca->inicia();
    while(! busca->fim()){
        string filme = busca->proximo();
        aux1 = copia[filme];
        aux1.atores.inicia();   //Iteração dos atores do filme para procurar o ator escolhido pelo usuario.
        while(! aux1.atores.fim()) {
            string ator = aux1.atores.proximo();
            if (ator == escolha) {  //Encontrar o ator na lista, anexa o fime e o ano em uma lista. (Para poder ordenar)
                aux2.filme = filme;
                aux2.ano = stoi(aux1.ano);
                filmes.anexa(aux2);
            }
        }
    }

    //Ordena a lista apartir do ano.
    filmes.ordena();
    return filmes;
}

//Função que busca os atores que trabalharam com um dado ator.

lista<string> atores_de_ator(const thash<info> & tabela,lista<string> & atores, const string & escolha) {
    //Tabelas e estrutura auxliares.
    thash<info> copia = tabela;
    thash<int> auxiliar (10007);
    info aux;

    //iteração da chaves da tabela(filmes).
    auto busca = copia.chaves();
    busca->inicia();
    while(! busca->fim()) {
        string filme = busca->proximo();
        aux = copia[filme];
        lista <string> auxiliar1 = aux.atores;
        aux.atores.inicia();
        while(! aux.atores.fim()) {  //Pega a lista de ator de cada filme e itera para procura o escolhido pelo usuario.
            string ator = aux.atores.proximo();
            if (ator == escolha) {
                auxiliar1.inicia();  //Ao achar o ator escolhido adiciona cada ator daquela lista de atores do filme ao uma estrutura.(apartir de uma iteração).
                while(! auxiliar1.fim()) {
                    string chave = auxiliar1.proximo();
                    auxiliar.adiciona(chave, 1);  //obs: usado uma tabela para impedir q haja dois atores iguais na listagem.
                }
                break;
            }
        }
    }

    //Passa a tabela de chaves de atores para uma lista, assim podendo ser ordenada alfabeticamente.
    auto list = auxiliar.chaves();
    list->inicia();
    while(! list->fim()) {
        string conteudo = list->proximo();
        atores.anexa(conteudo);
    }

    atores.ordena();
    return atores;
}

//Função que busca os atores que atuaram em todos os filmes de um certo conjunto de filmes.

thash<int> atores_de_filmes(const thash<info>  & tabela, thash<int>  & atores, const lista<string> & escolhas) {
    //Tabela,lista e estrutura auxiliares.
    thash <info> copia_tab = tabela;
    lista <string> copia_list = escolhas;
    info aux;
    int N = 0; //Contador usado para verificar se quantidade de filmes q ator participou é a mesma q a de filmes escolhidos,

    copia_list.inicia(); //Itera a lista de filmes escolhidos pelo usuario.
    while(! copia_list.fim()) {
        string filme = copia_list.proximo();
        if(copia_tab.existe(filme)) {  //Para cade filme verifica se existe na tabela.
            aux = copia_tab[filme];
            aux.atores.inicia();
            while(! aux.atores.fim()) { //Itera a lista de atores daquele filme e adiciona a uma tabela se o ator nao existe nela
                string aux1 = aux.atores.proximo();
                if(! atores.existe(aux1)) {
                    atores.adiciona(aux1, 1);
                } else { //Se existe incrementa a o conteudo da tabela em um(Onde numero é quantidade de filmes q participou da listagem).
                    atores[aux1]++;
                }
            }
            N++;
        }

    }

    auto algo = atores.chaves(); //Iteração das chaves da tabela para ver se o conteudo inteiro e o mesmo q o contador N.
    algo->inicia();
    while(! algo->fim()) {
        string ator = algo->proximo();
        if(atores[ator] != N) { //Se não for, então aquele ator nao participou de todos os filmes escolhido pelo usario
            atores.remove(ator); //remove da tabela.
        }
    }

    return atores;
}

//Sobrecarga de operador para o ordenamento, apatir da quantidade de filmes.

bool operator<(const actor & int1, const actor & int2) {
    return int1.filmes < int2.filmes;
}

//Função que faz a listagem ordenada de atores, de acordo com a quantidade de filmes em que atuaram.

lista<actor> ator_filmes(const thash<info> & tabela, lista<actor> & qnt_filmes) {
    //Tabela e estrutura auxiliares.
    thash<info> copia = tabela;
    thash<int> auxiliar(100000007);
    actor aux2;

    auto algo = copia.valores(); //Gera uma lista dos valores(conteudo) da tabela, para que possar ser interada.
    algo->inicia();
    while(! algo->fim()) {
        info aux = algo->proximo();
        aux.atores.inicia(); //Para cada lista de atores da listona, itera a lista de atores.
        while(! aux.atores.fim()) {
            string ator = aux.atores.proximo();
            if(! auxiliar.existe(ator)) {  //E verifica se existe numa tabela auxliar o ator
                auxiliar.adiciona(ator, 1);
            } else {
                auxiliar[ator]++; //Se já existe incrementa a quantidade de filmes que participou.
            }
        }
    }

    auto atores = auxiliar.chaves(); //Iteração da tabela para convertela em uma lista para que possa ser ordena.
    atores->inicia();
    while(! atores->fim()) {
        string chave = atores->proximo();
        int movie = auxiliar[chave];
        aux2.ator = chave;
        aux2.filmes = movie;
        qnt_filmes.anexa(aux2);
    }

    //Ordena apartir da quantidade de filmes e inverte a lista para que os maiores valores estejam no começo da lista.
    qnt_filmes.ordena();
    qnt_filmes.inverte();
    return qnt_filmes;
}

//Sobrecarga de operador para o ordenamento, apatir da popularidade.

bool operator<(const popstar & int1, const popstar & int2) {
    return int1.popularidade < int2.popularidade;
}

//Função que faz a listagem ordenada de atores, de acordo com suas popularidades.

lista<popstar> ator_pop(const thash<info> & tabela, lista<popstar> & top_ator) {
    //Tabela e estruturas auxiliares.
    thash<info> copia = tabela;
    thash<int> auxiliar(10000007);
    popstar aux2;

    auto algo = copia.valores(); //Gera uma lista dos valores(conteudo) da tabela, para que possar ser interada.
    algo->inicia();
    while(! algo->fim()) {
        info aux = algo->proximo();
        int quantidade = aux.atores.comprimento() - 1; //Quantiade total de atores de filmes menos o proprio ator.
        aux.atores.inicia();
        while(! aux.atores.fim()) { //Para cada lista de atores da listona, itera a lista de atores.
            string chave = aux.atores.proximo();
            if(! auxiliar.existe(chave)) {
                auxiliar.adiciona(chave, quantidade); //Não existindo tal ator na tabela a adiciona o ator e sua "popularidade"
            } else {
                auxiliar[chave] = auxiliar[chave] + quantidade; //Se não incrementa a "popularidade" do ator.
            }
        }
    }

    auto atores = auxiliar.chaves(); //Iteração da tabela para convertela em uma lista para que possa ser ordena.
    atores->inicia();
    while(! atores->fim()) {
        string chave = atores->proximo();
        int pop = auxiliar[chave];
        aux2.ator = chave;
        aux2.popularidade = pop;
        top_ator.anexa(aux2);
    }

    //Ordena apartir da "popularidade" e inverte a lista para que os maiores valores estejam no começo da lista.
    top_ator.ordena();
    top_ator.inverte();
    return top_ator;
}