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

//Implementar mult, que retorna uma nova lista contendo N cópias dos dados
//        da lista:
//
//lista<T> mult(int N);
//
//OBS: se N == 0: lista de resultado deve ser vazia

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

    vector<double> mult(vector<double> & v, int N) {
        vector<double> r;

        while (N-- > 0) {
            for (auto & x: v) r.push_back(x);
        }
        return r;
    }
};

TEST_F(TesteQuestao, Normal)
{
    int N = 5;

    while (N-- > 2) {
        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        try {
            auto r = q.mult(N);
            auto res = mult(v, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                << "N=" << N
                << vreport(v, "; lista original: ")
                << qreport(r, "; lista obtida: ")
                << vreport(res, "; lista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
    }
}

TEST_F(TesteQuestao, Simples)
{
    int N = 1;

        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        try {
            auto r = q.mult(N);
            auto res = mult(v, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                      << "N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; lista obtida: ")
                      << vreport(res, "; lista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
}

TEST_F(TesteQuestao,Vazia)
{
    int N = 0;

        lista<double> q;
        int m = 5 + (rand() % 15);

        auto v = gera_lista(m);
        copia(q, v);

        try {
            auto r = q.mult(N);
            auto res = mult(v, N);

            if (not compara(r, res)) {
                FAIL()<<"Conteúdo da lista diferente do esperado ... "
                      << "N=" << N
                      << vreport(v, "; lista original: ")
                      << qreport(r, "; lista obtida: ")
                      << vreport(res, "; lista esperada: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar sublista !";
            return;
        }
}

