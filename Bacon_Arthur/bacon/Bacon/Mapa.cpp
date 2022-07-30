//
// Created by msobral on 22/08/2019.
//

#include "Mapa.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::exception;
using std::cout;
using std::endl;

void strip(string &s) {
    int pos = 0;
    while (pos < s.size()) {
        if (!isspace(s[pos])) {
            if (pos > 0) s.erase(0, pos);
            break;
        }
        pos++;
    }
    if (pos == s.size()) {
        s.clear();
        return;
    }

    pos = s.size()-1;
    while (pos >= 0) {
        if (!isspace(s[pos])) {
            if (pos < s.size()-1) s.erase(pos+1);
            break;
        }
        pos--;
    }
}

vector<string> split(const string & s, const string & delim) {
    vector<string> v;
    if (s.empty()) return v;

    //cout << ">>" << s << "===";
    //cout.flush();

    int pos = 0;
    while (pos != string::npos) {
        int pos1 = s.find_first_not_of(delim, pos);
        if (pos1 == string::npos) break;
        pos = s.find_first_of(delim, pos1);
        if (pos == string::npos) {
            v.push_back(s.substr(pos1));
            break;
        } else {
            v.push_back(s.substr(pos1, pos-pos1));
        }
    }
    //cout << "ok" << endl;
    return v;
}

Mapa::Mapa(const string &path) {
    ifstream arq(path);

    if (! arq.is_open()) throw -1;
    string w;
    while (getline(arq, w)) {
        auto v = split(w, ";");
        if (v.size() == 3) {
            m_filmes[v[0]] = split(v[2], ",");
            for (auto & act: m_filmes[v[0]]) {
                m_atores[act].push_back(v[0]);
            }
        }
    }
}

fila <string> Mapa::obtem_filmes(const string &ator) {
    auto & v = m_atores[ator];
    fila<string> q(v.size());

    for (auto &s: v) {
        if (s_filmes.count(s) == 0) {
            q.enfileira(s);
            s_filmes.insert(s);
        }
    }
    return q;
}

fila <string> Mapa::obtem_atores(const string &filme) {
    auto & v = m_filmes[filme];
    fila<string> q(v.size());

    for (auto &s: v) {
        if (s_atores.count(s) == 0) {
            q.enfileira(s);
            s_atores.insert(s);
        }
    }
    return q;
}

void Mapa::limpa() {
    s_atores.clear();
    s_filmes.clear();
}