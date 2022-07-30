/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <prglib.h>

using namespace prglib;

using namespace std;

int main() {

    //Exemplo do Funcionamento da fila
    fila<int> f1(10); // cria uma fila chamada "f1", com capacidade 10

    // enfileira os números 5, 8, 2 e 4 na fila "f1"
    f1.enfileira(5);
    f1.enfileira(8);
    f1.enfileira(2);
    f1.enfileira(4);

    // desenfileira um por um dos dados da fila, mostrando-os na tela, até
    // que a fila fique vazia
    while (! f1.vazia()) cout << "Dado: " << f1.desenfileira() << endl;

    cout << endl << endl << endl;

    //Exemplo do funcionamento de uma pilha;

    pilha<int> q(6);

    q.push(5);
    q.push(8);
    q.push(4);
    q.push(2);
    q.push(3);

    cout << "Empilhou 5, 8, 4, 2, 3" << endl;

    while (! q.vazia()) {
        cout << "Topo da pilha=" << q.top();
        cout << "... desempilhou " << q.pop() << endl;
    }

    cout << endl << endl << endl;

    //Exemplo do funcionamento de uma lista;

    lista<string> list;

    list.anexa("Uma");
    list.anexa("coisa");
    list.anexa("legal");
    list.insere("Mais");

    cout << "Comprimento: " << list.comprimento() << endl;
    for (int pos=0; pos < list.comprimento(); pos++) {
        cout << "Posicao " << pos;
        cout << ": " << list.obtem(pos) << endl;
    }

    //Exemplo do funcionamento da arvore;

    string w[7] = {"graviola","caju","sapoti","acai", "banana","morango","laranja"};

    // Uma árvore deve ser criada dinamicamente ... isso facilita
    // sua implementação.
    arvore<string> * arv = new arvore<string>(w[0]);

    for (int n=1; n < 6; n++) arv->adiciona(w[n]);

    for (int n=0; n < 7; n++) {
        try {
            cout << "arv[" << w[n] << "] = " << arv->obtem(w[n]) << endl;
        } catch (...) {
            cout << "Ops: " << w[n] << " não está na árvore !" << endl;
        }
    }

    delete arv;

    return 0;
}