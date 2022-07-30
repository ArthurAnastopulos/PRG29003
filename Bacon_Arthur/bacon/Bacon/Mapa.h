//
// Created by msobral on 22/08/2019.
//

#ifndef BACON_MAPA_H
#define BACON_MAPA_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <prglib.h>

using std::string;
using std::map;
using std::vector;
using prglib::fila;
using std::set;

const string bacon = "Kevin Bacon";

class Mapa {
public:
    // construtor: cria um objeto Mapa que acessa o conteúdo do arquivo cujo nome é
    // informado no parâmetro path
    Mapa(const string & path);

    // Obtem a lista de filmes em que um ator trabalhou
    fila<string> obtem_filmes(const string & ator);

    // Obtem a lista de atores que atuaram em um filme
    fila<string> obtem_atores(const string & filme);

    // esquece todos os atores e filmes já visitados
    void limpa();
private:
    map<string,vector<string>> m_filmes;
    map<string,vector<string>> m_atores;
    set<string> s_atores;
    set<string> s_filmes;
};


#endif //BACON_MAPA_H
