//Projeto 04 - Um dicionário de português
//Nome: Arthur Anastopulos dos Santos
//Data de Entrega:
#include <iostream>
#include <string>
#include <prglib.h>
#include "dicionario.h"
#include <fstream>

using namespace std;
using prglib::arvore;
using prglib::lista;

//Instruções de uso ao final do programa.

//Programa exemplo que demonstre o uso de cada uma de suas operações.
int main(int argc, char** argv) {
    string path1 = "../data/verbetes.txt";
    string path2 = "../data/dicionario.txt";
    arvore<verbetes> * dicionario = inicia_dicionario(path2,path1);

    cout << "Digite a  opção da função q deseja: " << endl;
    cout << "[1] - Procurar um verbete" <<endl;
    cout << "[2] - Procurar um lote de verbetes" <<endl;
    cout << "[3] - Adicionar um verbete" <<endl;
    cout << "[4] - Procurar verbetes por prefixo" <<endl;

    int opt = 0;
    while(true){
        cout << "Digite: ";
        cin >> opt;
        if(opt > 0 && opt < 5) break;
        cout << endl;
    }

    //Exemplo da funçao search_termo().
    if(opt == 1){
        string termo;
        cout << "Digite o termo que deseja procura: ";
        while(true) {
            getline(cin, termo);
            if(! termo.empty()) break;
        }
        verbetes verb1;
        search_termo(dicionario, termo, verb1);
        cout << endl << "Verbete: " << verb1.termo << endl;
        cout << "Classe Gramatical: " << verb1.tipo << endl;
        verb1.significados.inicia();
        while (!verb1.significados.fim()) {
            string aux1 = verb1.significados.proximo();
            cout << "Significado: " << aux1 << endl;
        }
    }

    //Exemplo da função search_lote().
    if(opt == 2){
        lista<string> termos;
        string termo;
        cout << "Digite os termos que deseja procurar: [enter para terminar]" << endl;
        while (true) {
            getline(cin, termo);
            termos.anexa(termo);
            if (termo.empty() && termos.comprimento() > 1)break;
        }
        lista<verbetes> verbs;
        search_lote(dicionario,termos, verbs);
        verbs.inicia();
        while (!verbs.fim()) {
            verbetes aux2 = verbs.proximo();
            cout << endl << "Verbete: " << aux2.termo << endl;
            cout << "Classe Gramatical: " << aux2.tipo << endl;
            aux2.significados.inicia();
            while (!aux2.significados.fim()) {
                string aux3 = aux2.significados.proximo();
                cout << "Significado: " << aux3 << endl;
            }
            cout << endl;
        }
    }

    //Exemplo da função adiciona_verbete().
    if(opt == 3){
        string add, clas_gra, sig;
        lista<string> significados;
        cout << "Digite o termo q deseja adicionar: ";
        while(true) {
            getline(cin, add);
            if(! add.empty()) break;
        }
        cout << endl << "Digte sua classe gramatical: ";
        while(true) {
            getline(cin, clas_gra);
            if(! clas_gra.empty()) break;
        }
        cout << endl << "Digite seus significados: [enter para terminar]";
        while (true) {
            getline(cin, sig);
            if (sig.empty())break;
            significados.anexa(sig);
        }
        adiciona_verbete(dicionario, add, clas_gra, significados);
        //recomendado após adicionar o verbete, gravar no arquivo gerado pelo programa.
        grava_arquivo(dicionario, path2);
    }

    //Exemplo da função search_verbete_prefixo().
    if(opt == 4){
        string sufixo;
        cout << "Digite o prefixo da palavra: ";
        while(true) {
            getline(cin, sufixo);
            if(! sufixo.empty()) break;
        }

        lista<verbetes> verbs2;
        search_verbete_prefixo(dicionario, sufixo, verbs2);
        verbs2.inicia();
        while (!verbs2.fim()) {
            verbetes aux4 = verbs2.proximo();
            cout << endl << "Verbete: " << aux4.termo << endl;
            cout << "Classe Gramatical: " << aux4.tipo << endl;
            aux4.significados.inicia();
            while (!aux4.significados.fim()) {
                string aux5 = aux4.significados.proximo();
                cout << "Significado: " << aux5 << endl;
            }
        }
    }

    delete dicionario;
}

//Ao iniciar o programa exemplo, o programa usa a função inicia_dicionario(), que envolve criar a árvore de pesquisa binária contendo os verbetes. Se for a primeira vez que se inicia o dicionário, a árvore é criada a partir dos verbetes originais,
//em seguida é balanceada e então gravada em um novo arquivo. No entanto, se esse arquivo contendo a árvore já existir, a árvore é criada diretamente a partir dele. O arquivo de árvore contém os verbetes numa sequência tal que a árvore criada fique balanceada.
// Além disso, os verbetes são representados nesse arquivo em um formato mais simples de ser lido.
//Em seguida usuario de digitar o numero da opção da função do dicionario que ele deseja usar.
//Opção 1 - search_termo() -Procurar um verbete: o dicionário possibilita que um verbete seja obtido a partir de um termo (uma palavra). Se o termo não existir, então uma exceção é gerada.
//Opção 2 - search_lote() -Procurar um lote de verbetes: o dicionário possibilita que se procure um lote de verbetes, a partir de uma lista de termos. Termos desconhecidos são ignorados.
//Opção 3 - adiciona_verbete() -Adicionar um verbete: o dicionário possibilita que se adicione um novo verbete. Recomendado que grave no arquivo o novo verbete.
//Opção 4 - search_verbete_prefixo() -Procurar verbetes por prefixo: o dicionário possibilita procurar todos os verbetes dos termos que tenham um prefixo em comum.