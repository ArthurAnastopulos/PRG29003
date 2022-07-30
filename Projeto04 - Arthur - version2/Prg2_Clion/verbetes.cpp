//Projeto 04 - Um dicionário de português
//Nome: Arthur Anastopulos dos Santos
//Data de Entrega:
#include <iostream>
#include <string>
#include "prglib.h"
#include <fstream>
#include "dicionario.h"

using namespace std;
using prglib::lista;
using prglib::arvore;

//Função separa, usada para quebrada de string apartir de um separador.

lista<string> separa(const string & algo, const string & sep){
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

//Função que cria uma lista de verbetes apartir de um arquivo.

lista <verbetes> cria_lista_verbete(const string & nome_arquivo) {
    //Verifica se o arquivo é invalido.
    lista<verbetes> dicionario;
    ifstream arq(nome_arquivo);
    if(! arq.is_open()){
        cout << "Arquivo Invalido!" << endl;
        throw -1;
    }
    string aux;
    verbetes novo;
    lista<string> auxiliar1;
    lista<string> signifacado;
    //Anexa em uma lista auxiliar as linha do arquivo ate encontra uma string vazia.
    while(getline(arq, aux)) {
        if (aux.empty()) {
            //Processa a lista auxiliar para obter um verbete
            string aux1 = auxiliar1.obtem(0);
            lista<string> auxiliar2 = separa(aux1, "*");
            auxiliar2.inverte();
            novo.termo = auxiliar2.obtem(1); //obtem o termo
            novo.tipo = auxiliar1.obtem(1); //obtem o tipo/classe_gramatical.

            //Faz uma iteração do resto da lista para obter uma lista de significados.
            int N1 = 0;
            int N2 = auxiliar1.comprimento() -2;
            auxiliar1.iniciaPeloFim();
            while(! auxiliar1.inicio() && N1 != N2) {
                string sig = auxiliar1.anterior();
                if (sig[0] == '(') aux1.clear();
                else {
                    signifacado.anexa(sig);
                    novo.significados = signifacado; //obtem a lista de significados.
                }
                N1++;
            }

            dicionario.anexa(novo);
            signifacado.esvazia();
            auxiliar1.esvazia();
            auxiliar2.esvazia();
        } else {
            auxiliar1.anexa(aux);
        }
    }
    //retorna a lista de verbetes ao usuario.
    return dicionario;
}






/*
verbetes cria_verbete (ifstream & arq) {
    string aux;
    verbetes novo;
    lista<string> auxiliar1;
    lista<string> signifacado;
    while(getline(arq, aux)){
        if(aux.empty()) {
            auxiliar1.inicia();
            int N1 = 0;
            int N2 = 0;
            while (! auxiliar1.fim()) {
                string aux1 = auxiliar1.proximo();
                if(N1 == 0) {
                    lista<string> auxiliar2 = separa(aux1,"*");
                    auxiliar2.iniciaPeloFim();
                    while(! auxiliar2.inicio() && N2 != 2) {
                        string aux2 = auxiliar2.anterior();
                        if(N2 == 1) {
                            novo.termo = aux2;
                        }
                        N2++;
                    }
                }
                else if(N1 == 1) novo.tipo = aux1;
                else {
                    if (aux1[0] == '(') aux1.clear();
                    else {
                        signifacado.anexa(aux1);
                        novo.significados = signifacado;
                    }
                }
                N1++;
            }
            return novo;
        }
        else {
            auxiliar1.anexa(aux);
        }
    }
}
*/
