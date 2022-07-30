//Projeto 04 - Um dicionário de português
//Nome: Arthur Anastopulos dos Santos
//Data de Entrega:

#ifndef PRG2_TREES_DICIONARIO_H
#define PRG2_TREES_DICIONARIO_H

#include <iostream>
#include <string>
#include <prglib.h>
#include <fstream>

using namespace std;
using prglib::lista;
using prglib::arvore;

//Struct usada para a processamento do dicionario.

struct verbetes {
    string termo; //termo.
    string tipo; //classe_gramatical.
    lista<string> significados; //lista de significados.

    bool operator<(const verbetes & termo1) const {
        return termo < termo1.termo;
    }
    bool operator==(const verbetes & termo1) const {
        return termo == termo1.termo;
    }
};

//Funções de ambos os .cpp

lista<string> separa(const string & algo, const string & sep);

lista <verbetes> cria_lista_verbete(const string & nome_arquivo);

arvore<verbetes> * struct_to_arvore(lista<verbetes> list_verbetes);

lista<verbetes> data_to_lista(const string & path);

void grava_arquivo(arvore<verbetes> * dicionario,const string & path_dic);

arvore<verbetes> * inicia_dicionario(const string & path_dic, const string & path);

verbetes search_termo(arvore<verbetes> * dicionario,const string & termo_procurado, verbetes & verb);

lista<verbetes> search_lote(arvore<verbetes> * dicionario, lista<string> lote_de_termos, lista<verbetes> & termos);

arvore<verbetes> * adiciona_verbete(arvore<verbetes> * dicionario, const string termo, const string classe_gramat, const lista<string> signif);

lista<verbetes> search_verbete_prefixo(arvore<verbetes> * dicionario,const string & sufixo, lista<verbetes> & lista_de_prefixos);

#endif //PRG2_TREES_DICIONARIO_H
