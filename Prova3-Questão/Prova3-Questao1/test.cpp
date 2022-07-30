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

class TesteQuestao: public ::testing::Test {
protected:

    virtual void SetUp() {
        srand(clock());
    }

    double drand() {
        return (rand()%10) + 1e-2*(rand() % 100);
    }

    vector<double> gera_fila(int n) {
        double k = 0;
        vector<double> v;
        while (n-- > 0) {
            k += drand();
            v.push_back(k);
        }
        return v;
    }

    void copia(fila<double> & q, const vector<double> & v) {
        while (! q.vazia()) q.desenfileira();
        for (auto & x: v) q.enfileira(x);
    }

    bool compara(fila<double> q, const vector<double> & v) {
        if (q.comprimento() != v.size()) return false;
        for (auto & x: v) {
            auto y = q.desenfileira();
            if (x != y) return false;
        }
        return true;
    }

    string qreport(fila<double> & q, const string & nome) {
        ostringstream out;
        out <<nome + ": ";
        while (! q.vazia()) out << q.desenfileira() << ",";
        return out.str();
    }

    string vreport(vector<double> & v, const string & nome) {
        ostringstream out;
        out <<nome + ": ";
        for (auto & x: v) out << x << ",";
        return out.str();
    }
};

TEST_F(TesteQuestao, Normal)
{
    int k = 10;

    while (k-- > 0) {
        fila<double> q(20);
        int m = 5 + (rand() % 15);

        auto v = gera_fila(m);
        auto bk = v;
        copia(q, v);

        try {
            q.inverte();
            reverse(v.begin(), v.end());

            if (not compara(q, v)) {
                FAIL()<<"Conteúdo da fila diferente do esperado"
                << vreport(bk, "; fila antes de inverte: ")
                << qreport(q, "; fila após inverte: ")
                << vreport(v, "; resultado esperado: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar inverte !";
            return;
        }
    }
}

TEST_F(TesteQuestao, Simples)
{
    int k = 10;

    while (k-- > 0) {
        fila<double> q(20);

        auto v = gera_fila(1);
        auto bk = v;
        copia(q, v);

        try {
            q.inverte();
            reverse(v.begin(), v.end());

            if (not compara(q, v)) {
                FAIL()<<"Conteúdo da fila diferente do esperado"
                      << vreport(bk, "; fila antes de inverte: ")
                      << qreport(q, "; fila após inverte: ")
                      << vreport(v, "; resultado esperado: ");
            }
        } catch (...) {
            FAIL()<<"Exceção inesperada ao chamar inverte !";
            return;
        }
    }

}

TEST_F(TesteQuestao,Vazia)
{
    int k = 10;

    while (k-- > 0) {
        fila<double> q(20);
        try {
            q.inverte();

            if (! q.vazia()) {
                FAIL() << "Fila vazia deve continuar vazia após inverte, mas sua fila ficou assim:"
                << qreport(q, "");
            }
        } catch (...) {
        }
    }

}
