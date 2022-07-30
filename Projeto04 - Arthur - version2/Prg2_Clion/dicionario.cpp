//Projeto 04 - Um dicionário de português
//Nome: Arthur Anastopulos dos Santos
//Data de Entrega:

#include <iostream>
#include <string>
#include "prglib.h"
#include "dicionario.h"
#include <fstream>

using namespace std;
using prglib::lista;
using prglib::arvore;

//Função que passa uma lista de verbetes para uma arvore binaria.
arvore<verbetes> * struct_to_arvore(lista<verbetes> list_verbetes) {
    list_verbetes.embaralha();
    list_verbetes.inicia();
    auto dicionario = new arvore<verbetes> (list_verbetes.proximo());
    while(! list_verbetes.fim()) {
        verbetes verb = list_verbetes.proximo();
         dicionario->adiciona(verb);
    }
    return dicionario;
}


//Função que passa o novo arquivo gerado pelo programa para uma lista de verbetes.
lista<verbetes> data_to_lista(const string & path) {
    ifstream arq(path);
    lista<verbetes> lista_de_verbetes;
    if(! arq.is_open()){
        cout << "Arquivo Invalido!" << endl;
        throw -1;
    }
    string aux;
    lista <string> auxiliar;
    lista <string> significado;
    verbetes data;
    //Anexa em uma lista auxiliar as linha do arquivo ate encontra uma string vazia.
    while (getline(arq,aux)) {
        if(aux.empty()) {
            //Processa a lista auxiliar para obter um verbete
            data.termo = auxiliar.obtem(0); //obtem o termo.
            data.tipo = auxiliar.obtem(1); //obtem a classe_gramatical.

            //Faz uma iteração do resto da lista para obter uma lista de significados.
            int N1 = 0;
            int N2 = auxiliar.comprimento() -2;
            auxiliar.iniciaPeloFim();
            while(! auxiliar.inicio() && N1 != N2) {
                string sig = auxiliar.anterior();
                if (sig[0] == '(') aux.clear();
                else {
                    significado.anexa(sig);
                    data.significados = significado; //obtem a lista de significados.
                }
                N1++;
            }
            lista_de_verbetes.anexa(data);
            significado.esvazia();
            auxiliar.esvazia();
        }
        else auxiliar.anexa(aux);
    }
    //retorna a lista do novo arquivo.
    return lista_de_verbetes;
}

//função que grava em um arquivo a arvore binaria.
void grava_arquivo(arvore<verbetes> * dicionario,const string & path_dic) {
    lista <verbetes> topologia;
    dicionario->listePreOrder(topologia);//lista a arvore no formato de sua topologia, assim ja sendo grava de forma balanceada;
    ofstream out(path_dic);
    topologia.inicia();
    //Iteração da lista para gravar os verbetes.
    while (! topologia.fim()) {
        verbetes verb = topologia.proximo();
        out << verb.termo << endl;
        out << verb.tipo << endl;

        verb.significados.inicia();
        while (! verb.significados.fim()) {
            string sig = verb.significados.proximo();
            out << sig << endl;
        }
        //grava uma quebra de linha para separar os verbetes no arquivo.
        out << endl;
    }
}

//Função que inicia o dicionario.
arvore<verbetes> * inicia_dicionario(const string & path_dic, const string & path) {
    arvore <verbetes> * dicionario;
    ifstream arq1(path_dic);
    //se o arquivo já existe cria uma arvore apartir dele, se for a primeira vez ao excutar o programa, gera uma arvore apartir do arquivo-fonte e grava ela no arquivo.
    if (arq1) {
        lista<verbetes> lista_de_verbetes = data_to_lista(path_dic);
        dicionario = struct_to_arvore(lista_de_verbetes);
        //Após criar a arvore balanceia ela.
        dicionario = dicionario->balanceia(true);
    } else {
        lista<verbetes> lista_de_verbetes = cria_lista_verbete(path);
        dicionario = struct_to_arvore(lista_de_verbetes);
        //Apos criar a arovre balanceia ela.
        dicionario = dicionario->balanceia(true);
        grava_arquivo(dicionario, path_dic);
    }
    //retorna a arvore do dicionario.
    return dicionario;
}

//Função que procura um verbete no dicionario.
verbetes search_termo(arvore<verbetes> * dicionario,const string & termo_procurado, verbetes & verb) {
    //Tenta procurar o verbete no dicionario, apartir da função obtem.
    verbetes aux;
    aux.termo = termo_procurado;
    try {
        verb = dicionario->obtem(aux);
        return verb;
    } catch (...) {//se nao encontrar gera uma excessao.
        throw -1;
    }
}

//Função que procura um lote de verbetes.
lista<verbetes> search_lote(arvore<verbetes> * dicionario, lista<string> lote_de_termos, lista<verbetes> & termos) {
    lote_de_termos.inicia(); //itera a lista de termos q o usuario deseja.
    while (!lote_de_termos.fim()) {
        string aux1 = lote_de_termos.proximo();
        verbetes aux;
        aux.termo = aux1;
        //Tenta procurar o verbete no dicionario, apartir da função obtem.
        try {
            verbetes verb = dicionario->obtem(aux);
            termos.anexa(verb);
        } catch (...) {
            //faz nada se nao encotrar o termo.
        }
    }
    //retorna todos os termos encontrados.
    return termos;
}

//Função que adiciona um verbete ao dicionario.
arvore<verbetes> * adiciona_verbete(arvore<verbetes> * dicionario, const string termo, const string classe_gramat, const lista<string> signif) {
    //coloca os parametros passados pelo usuario na struct.
    verbetes verb;
    verb.termo = termo;
    verb.tipo = classe_gramat;
    verb.significados = signif;

    //adiciona ao dicionario.
    dicionario->adiciona(verb);
    return dicionario;
}


//Procura o verbete apartir do prefixo.
lista<verbetes> search_verbete_prefixo(arvore<verbetes> * dicionario,const string & sufixo, lista<verbetes> & lista_de_prefixos) {
    //Itera a arvore para encontrar as palavras q contem o prefixo.
    int tamanho = sufixo.length();
    dicionario->inicia();
    while (! dicionario->fim()) {
        verbetes verb = dicionario->proximo();
        string prefixo = verb.termo.substr(0,tamanho); //Compara o prefixo apartir de uma substring do termo.
        if(prefixo == sufixo) {
            lista_de_prefixos.anexa(verb); //Anexa a palavra se possuir o prefixo.
        }
    }
    //Retorna a lista de prefixos.
    return lista_de_prefixos;

    //obs: por algum motivo ao tentar usar o obtemIntervalo gera um erro de undefined reference ao compilar.
}

