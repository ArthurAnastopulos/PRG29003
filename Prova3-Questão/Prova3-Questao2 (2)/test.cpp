//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <prglib.h>
#include <map>
#include "gtest/gtest.h"

using namespace std;
using namespace prglib;

//Implementar sublista:
//
//lista<T> sublista(unsigned int pos1, int num)
//
//OBS: se num < 0: copiar os num dados  que antecedem pos1
//        OBS: se num exceder os limites da lista: copiar só até o limite

class TesteQuestao: public ::testing::Test {
protected:

    virtual void SetUp() {
        srand(clock());
    }

    double drand() {
        return (rand()%10) + 1e-2*(rand() % 100);
    }

    vector<double> gera_lista(int n) {
        double k = 0;
        vector<double> v;
        while (n-- > 0) {
            k += drand();
            v.push_back(k);
        }
        return v;
    }

    void copia(lista<double> & q, const vector<double> & v) {
        while (! q.vazia()) q.remove(0);
        for (auto & x: v) q.anexa(x);
    }

    bool compara(lista<double> & q, const vector<double> & v) {
        if (q.comprimento() != v.size()) return false;
        q.inicia();
        for (auto & x: v) {
            auto y = q.proximo();
            if (x != y) {
                return false;
            }
        }
        return true;
    }

    string qreport(lista<double> & q, const string & nome) {
        ostringstream out;
        out <<nome + ": ";
        q.escrevaSe(out, ",");
        return out.str();
    }

    string vreport(vector<double> & v, const string & nome) {
        ostringstream out;
        out <<nome + ": ";
        for (auto & x: v) out << x << ",";
        return out.str();
    }

    vector<double> fatia(vector<double> & v, int pos, int N) {
        vector<double> r;

        auto it = v.begin();
        it += pos;
        if (N > 0) while (N-- > 0 && it != v.end()) {
            r.push_back(*it);
            it++;
        } else {
            N = -N;
            while (N-- > 0) {
                r.push_back(*it);
                if (it == v.begin()) break;
                it--;
            }
        }

        return r;
    }
};

TEST_F(TesteQuestao, Normal)
{
    int k = 10;

    while (k-- > 0) {
        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        int pos = rand() % (v.size()/2);
        int N = rand() % (v.size()/2);

        try {
            lista<double> r;
            q.sublista(r, pos, N);
            auto res = fatia(v, pos, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                << "pos=" << pos << ", N=" << N
                << vreport(v, "; lista original: ")
                << qreport(r, "; sublista obtida: ")
                << vreport(res, "; sublista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}

TEST_F(TesteQuestao, Simples)
{
    int k = 10;

    while (k-- > 0) {
        lista<double> q;

        auto v = gera_lista(1);
        copia(q, v);

        int pos = 0;
        int N = 1;

        try {
            lista<double> r;
            q.sublista(r, pos, N);
            auto res = fatia(v, pos, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                      << "pos=" << pos << ", N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; sublista obtida: ")
                      << vreport(res, "; sublista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}

TEST_F(TesteQuestao,Vazia)
{
    int k = 10;

    while (k-- > 0) {
        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        int pos = rand()%(v.size()/2);
        int N = 0;

        try {
            lista<double> r;
            q.sublista(r, pos, N);

            if (not r.vazia()) {
                FAIL()<<"Sublista deveria ser vazia, pois: "
                      << "pos=" << pos << ", N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; sublista obtida: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}
// N excede a capacidade da lista !
TEST_F(TesteQuestao,Excesso)
{
    int k = 10;

    while (k-- > 0) {
        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        int pos = rand()%(v.size()/2);
        int N = v.size() - pos + (2 + rand() % 3);

        try {
            lista<double> r;
            q.sublista(r, pos, N);
            auto res = fatia(v, pos, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                      << "pos=" << pos << ", N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; sublista obtida: ")
                      << vreport(res, "; sublista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}

TEST_F(TesteQuestao, Reversa)
{
    int k = 10;

    while (k-- > 0) {
        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        int pos = v.size() - (rand() % (v.size()/2));
        int N = -(rand() % pos);

        try {
            lista<double> r;
            q.sublista(r, pos, N);
            auto res = fatia(v, pos, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado"
                      << "pos=" << pos << ", N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; sublista obtida: ")
                      << vreport(res, "; sublista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}
