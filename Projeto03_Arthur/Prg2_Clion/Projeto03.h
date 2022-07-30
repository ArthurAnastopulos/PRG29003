//Projeto 03 - Novas Estatísticas sobre atores e filmes
//Nome: Arthur Anastopulos dos Santos
//Data de entrega: 04/10/2019

#ifndef PRG2_DEMO_PROJETO03_H
#define PRG2_DEMO_PROJETO03_H

#include <iostream>
#include <prglib.h>
#include <string>
#include <fstream>

using namespace std;
using prglib::lista;
using prglib::thash;

//Estrutura das informaçoes da tabela.

struct info {
    string ano;
    lista <string> atores;
};

//Estrutura para a lista que ordena os filmes apartir do ano.

struct movie {
    string filme;
    int ano;
};

//Estrutura para a lista que ordena os atores apartir da quantidade de atores q atuaram junto a ele.

struct popstar {
    string ator;
    int popularidade;
};

//Estrutura para a lista que ordena os atores apartir da quantidade de filmes q aturaram.

struct actor {
    string ator;
    int filmes;
};

//Declaração das funções.

lista<string> separa(const string & algo, const string & sep);

thash<info> tabela(const string & path);

lista<movie> busca_filmes(const thash<info> & tabela, lista<movie> & filmes, const string & escolha);

lista<string> atores_de_ator(const thash<info> & tabela, lista<string> & atores, const string & escolha);

thash<int> atores_de_filmes(const thash<info>  & tabela, thash<int>  & atores, const lista<string> & escolhas);

lista<actor> ator_filmes(const thash<info> & tabela, lista<actor> & qnt_filmes);

lista<popstar> ator_pop(const thash<info> & tabela, lista<popstar> & top_ator);

#endif //PRG2_DEMO_PROJETO03_H
