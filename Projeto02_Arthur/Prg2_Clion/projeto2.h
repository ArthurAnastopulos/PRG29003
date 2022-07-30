#ifndef PRG2_DEMO_PROJETO2_H
#define PRG2_DEMO_PROJETO2_H

#include <iostream>
#include <string>
#include <prglib.h>
#include <fstream>

using namespace std;
using prglib::lista;

//Estrutura do mapa.

struct info {
    string filme; //rotulo.
    string ano; //sub-rotulo.
    lista <string> atores; //conteudo
};

//Estrutura dos filmes.

struct hollywood {
    string filme;
    int ano;
};

//Estrutura para ator e quantidade de filmes.

struct papeis {
    string ator;
    int atuacoes;
};

//Estrutura para ator e a quantidade de filmes em comum.

struct comum {
    string ator;
    int quantidade;
};

//Declaração das funções.

lista<string> separa(const string & algo, const string & sep);

lista<info> mapa(const string & path);

lista <hollywood> obtem_filmes(const lista <info> & mapa, lista <hollywood> & movie, const string & escolha);

lista <string> obtem_atores(const lista <info> & mapa, lista <string> & actor, const string & escolha);

lista <string> todos_atores(const lista <info> & mapa, lista <string> & atores);

lista <comum> ordena_atores_comum(const lista <info> & mapa, lista <comum> & atores, const string & escolha);

lista <string> filmes_string(const lista <info> & mapa, lista <string> & movie, const string & escolha);

lista <papeis> ordena_atores_atuar(const lista <info> & mapa, lista <papeis> & atores, const lista <string> & actor);

lista <string> busca_atores(const lista <info> & mapa, lista <string> & atores,const string & escolha);

#endif //PRG2_DEMO_PROJETO2_H
