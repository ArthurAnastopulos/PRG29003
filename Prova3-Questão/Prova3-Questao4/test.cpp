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

//Implementar a operação floor da árvore, que procura o maior valor
//que seja menor ou igual ao seu argumento:
//
//T floor(const T & arg);


class TesteQuestao: public ::testing::Test {
protected:

    virtual void SetUp() {
        srand(clock());
    }

    double drand() {
        return (3+(rand()%10)) + 1e-2*(rand() % 100);
    }

    vector<double> gera_lista(int n) {
        vector<double> v;
        while (n-- > 0) {
            v.push_back(drand());
        }
        return v;
    }

    arvore<double> * gera_arvore(vector<double> & v, double & maior, double & menor) {
        auto a = new arvore<double>(v[0]);
        maior = menor = v[0];
        for (auto x: v) {
            a->adiciona(x);
            if (x > maior) maior = x;
            if (x < menor) menor = x;
        }
        sort(v.begin(), v.end());
        return a;
    }

    double chao(vector<double> & v, double arg) {
        double r = 0;

        for (auto & x: v) {
            if (x <= arg) r = x;
        }

        return r;
    }

    void copia(lista<double> & q, const vector<double> & v) {
        while (! q.vazia()) q.remove(0);
        for (auto & x: v) q.anexa(x);
    }

//    bool compara(lista<double> & q, const vector<double> & v) {
//        if (q.comprimento() != v.size()) return false;
//        q.inicia();
//        for (auto & x: v) {
//            auto y = q.proximo();
//            if (x != y) {
//                return false;
//            }
//        }
//        return true;
//    }
//
//    string qreport(lista<double> & q, const string & nome) {
//        ostringstream out;
//        out <<nome + ": ";
//        q.escrevaSe(out, ",");
//        return out.str();
//    }

    string vreport(vector<double> & v, const string & nome) {
        ostringstream out;
        out <<nome + ": ";
        for (auto & x: v) out << x << ",";
        return out.str();
    }

};

double rand1() {
    double r = rand() % 1024;

    if (r == 0) return r;
    return (r+1)/1024;
}

TEST_F(TesteQuestao, Normal)
{
    int N = 10;

    while (N-- > 0) {
        int m = 5 + (rand() % 15);
        double maior, menor;
        arvore<double> * a;

        auto v = gera_lista(m);
        try {
            a = gera_arvore(v, maior, menor);
        } catch(...) {
            FAIL() << "Erro ao criar uma árvore (verifique construtor ou adiciona)";
        }

        double arg = menor + rand1()*(maior-menor);

        try {
            auto r = a->floor(arg);
            auto res = chao(v, arg);

            if (r != res) {
                FAIL()<<"Resultado deveria ser: " << res
                << ", mas floor retornou: " << r
                << "; arg=" << arg
                << vreport(v, "; dados da árvore: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar floor !";
        }
    }
}

TEST_F(TesteQuestao, Menor)
{
    int N = 10;

    while (N-- > 0) {
        int m = 5 + (rand() % 15);
        double maior, menor;
        arvore<double> * a;

        auto v = gera_lista(m);
        try {
            a = gera_arvore(v, maior, menor);
        } catch(...) {
            FAIL() << "Erro ao criar uma árvore (verifique construtor ou adiciona)";
        }

        double arg = maior + (1  + (rand() % 4));

        try {
            auto r = a->floor(arg);
            auto res = chao(v, arg);

            if (r != res) {
                FAIL()<<"Resultado deveria ser: " << res
                      << ", mas floor retornou: " << r
                      << "; arg=" << arg
                      << vreport(v, "; dados da árvore: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar floor !";
        }
    }
}

TEST_F(TesteQuestao,Invalido)
{
    int N = 10;

    while (N-- > 0) {
        int m = 5 + (rand() % 15);
        double maior, menor;
        arvore<double> * a;

        auto v = gera_lista(m);
        try {
            a = gera_arvore(v, maior, menor);
        } catch(...) {
            FAIL() << "Erro ao criar uma árvore (verifique construtor ou adiciona)";
        }

        double arg = menor - (1+(rand() % 4));

        try {
            auto r = a->floor(arg);
            FAIL()<<"floor deveria disparar uma exceção ... "
                  << "; arg=" << arg
                  << vreport(v, "; dados da árvore: ");

        } catch (...) {
        }
    }
}

