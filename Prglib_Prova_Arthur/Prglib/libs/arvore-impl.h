/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H

#include "arvore.h"
#include <string>

using std::string;

namespace prglib {

template <typename T> arvore<T>::~arvore() {
    //"vazio"
}
    
template <typename T> arvore<T>::arvore() {
    //"vazio"
}

template <typename T> arvore<T>::arvore(const T & dado) {
    data = dado;
    pai = this;
    esq = dir = nullptr;
}

template <typename T> arvore<T>::arvore(const arvore<T> * outra) {
    if(outra == nullptr)throw -1;
    data = outra->data;
    if(outra->esq != nullptr)esq = new arvore<T> (outra->esq);
    if(outra->dir != nullptr)dir = new arvore<T> (outra->dir);
}

template <typename T> arvore<T>::arvore(istream &inp) {

}

template <typename T> arvore<T>::arvore(prglib::lista<T> &dados) {
    if(dados.vazia())throw -1;
    dados.inicia();
    data = dados.proximo();
    while(! dados.fim())adiciona(dados.proximo());
}

template <typename T> void arvore<T>::adiciona(const T & algo) {
    arvore<T> * atual = this;
    while(true) {
        if(atual->data == algo) {
            atual->data = algo;
            return;
        }
        if(algo < atual->data) { //esq
            if(atual->esq != nullptr) {
                atual = atual->esq;
            } else {
                atual->esq = new arvore<T>(algo);
                atual->esq->pai = atual;
                return;
            }
        } else { //dir
            if (atual->dir != nullptr) {
                atual = atual->dir;
            } else {
                atual->dir = new arvore<T>(algo);
                atual->dir->pai = atual;
                return;
            }
        }
    }
}

template <typename T> const T& arvore<T>::obtem(const T & algo) const {
    auto atual = this;
    while(true) {
        if(atual->data == algo)return atual->data;
        else if(algo < atual->data) { //testa esq
            if(atual->esq == nullptr) throw -1;
            atual = atual->esq;
        } else {
            if(atual->dir == nullptr) throw -1;
            atual = atual->dir;
        }
    }
}

template <typename T> const T& arvore<T>::obtem() const {
    auto atual = this;
    if(atual->pai == nullptr){
        throw -1;
    }else {
        return atual->data;
    }
}

template <typename T> void arvore<T>::listeEmLargura(lista<T> & result) {
    lista <arvore<T>*> folha;
    folha.anexa(this);

    while(! folha.vazia()) {
        arvore * nodo = folha.remove(0);
        result.anexa(nodo->data);
        if(nodo->esq)folha.anexa(nodo->esq);
        if(nodo->dir)folha.anexa(nodo->dir);
    }
}

template <typename T> void arvore<T>::listeInOrder(lista<T> & result) {
    if(esq)esq->listeInOrder(result);
    result.anexa(data);
    if(dir)dir->listeInOrder(result);
}

template <typename T> void arvore<T>::listePreOrder(lista<T> & result) {
    result.anexa(data);
    if(esq)esq->listePreOrder(result);
    if(dir)dir->listePreOrder(result);

   /* lista <arvore<T>*> folha;
    folha.insere(this);

    while(! folha.vazia()) {
        arvore * nodo = folha.remove(0);
        result.anexa(nodo->data);
        if(nodo->dir)folha.insere(nodo->dir);
        if(nodo->esq)folha.insere(nodo->esq);
    } */
}

template <typename T> void arvore<T>::listePostOrder(lista<T> & result) {
    if(esq)esq->listePostOrder(result);
    if(dir)dir->listePostOrder(result);
    result.anexa(data);
}

template <typename T> void arvore<T>::escrevaSe(ostream& out) const {
    static int nivel = -1;
    string prefixo;

    nivel++;
    prefixo.append(nivel, ' ');

    if (dir) dir->escrevaSe(out);
    out << prefixo << data << std::endl;
    if (esq) esq->escrevaSe(out);
    nivel--;
}

template <typename T> unsigned int arvore<T>::tamanho() const {
    int i = 0;
    if(dir) {
        i = i + dir->tamanho();
    }
    if(esq) {
        i = i + esq->tamanho();
    }
    i++;
    return i;
}

template <typename T> int arvore<T>::fatorB()  {
    int h1 = 0, h2 = 0;
    if(esq != nullptr) h1 = 1 + esq->altura();
    if(dir != nullptr) h2 = 1 + dir->altura();
    return  h1 - h2;
}

template <typename T> unsigned int arvore<T>::altura() {
    int h1 = 0, h2 = 0;
    if (esq) h1 = 1 + esq->altura();
    if (dir) h2 = 1 + dir->altura();

    if (h1 > h2) {
        return h1;
    } else {
        return h2;
    }
}

template <typename T> arvore<T>* arvore<T>::rotacionaL() {
    arvore<T> * n1 = this;
    arvore<T> * n2 = dir;
    arvore<T> * b = n2->esq;

    n2->esq = n1;
    n1->dir = b;
    return n2;
}

template <typename T> arvore<T>* arvore<T>::rotacionaR() {
    arvore<T> * n2 = this;
    arvore<T> * n1 = esq;
    arvore<T> * b = n1->dir;

    n1->dir = n2;
    n2->esq = b;
    return n1;
}

template <typename T> arvore<T>* arvore<T>::balanceia() {
    if(esq)esq = esq->balanceia();
    if(dir)dir = dir->balanceia();

    auto atual = this;

    while(atual->fatorB() < -1){
        if(atual->dir->fatorB() > 0)atual->dir = atual->dir->rotacionaR();
        atual = atual->rotacionaL();
    }

    while(atual->fatorB() > 1){
        if(atual->esq->fatorB() < 0)atual->esq = atual->esq->rotacionaL();
        atual = atual->rotacionaR();
    }

    return atual;
}

template <typename T> arvore<T>* arvore<T>::balanceia(bool otimo) {
    if (! otimo) return balanceia();

    auto atual = this;
    while (true) {
        atual = atual->balanceia();
        int h1 = atual->altura();
        atual = atual->balanceia();
        int h2 = atual->altura();
        if(h1 == h2)return atual;
    }
}

template <typename T> void arvore<T>::inicia() {
    if(p_stack == nullptr) p_stack = new lista<arvore<T>*>;
    else p_stack->esvazia();

    //versão inicial: pre-order
    p_stack->insere(this);
}

template <typename T> T& arvore<T>::proximo() {
    if(fim())throw -1;

    arvore * nodo = p_stack->remove(0);
    if (nodo->dir)p_stack->insere(nodo->dir);
    if (nodo->esq)p_stack->insere(nodo->esq);

    return nodo->data;
}

template <typename T> bool arvore<T>::fim() {
    return p_stack->vazia();
}

template <typename T> T arvore<T>::remove(const T &algo) {
    auto atual = this;
    bool proc = true;

    //Localiza
    while(proc) {
        if(atual->data == algo)proc = false;
        else if(algo < atual->data) {
            if(atual->esq == nullptr) throw -1;
            atual = atual->esq;
        } else {
            if(atual->dir == nullptr) throw -1;
            atual = atual->dir;
        }
    }

    T dado = atual->data;
    if(atual->folha()) {
        atual = nullptr;
        delete atual;
        return dado;
    }


    //"Verifica"
    if(atual->fatorB() > 0){
        T algo = atual->esq->obtemMaior();
        atual->data = algo;
        if(atual->esq->folha()) {
            delete atual->esq;
            atual->esq = nullptr;
        } else {
        atual->esq->remove(algo);
        }
    } else {
        T algo = atual->dir->obtemMenor();
        atual->data = algo;
        if(atual->dir->folha()) {
            delete atual->dir;
            atual->dir = nullptr;
        } else {
            atual->dir->remove(algo);
        }
    }
    return dado;
}

template <typename T> bool arvore<T>::folha() const {
    return dir == nullptr && esq == nullptr;
}

template <typename T> void arvore<T>::obtem_folhas(lista<T> & result) {
    auto atual = this;
    if (atual->folha())result.anexa(atual->data);
    if (atual->esq != nullptr)atual->esq->obtem_folhas(result);
    if (atual->dir != nullptr)atual->dir->obtem_folhas(result);
}



template <typename T> const T& arvore<T>::obtemMenor() const{
    auto atual = this;
    while(true) {
        if(atual->esq == nullptr) {
            return atual->data;
        } else {
            atual = atual->esq;
        }
    }
}

template <typename T> const T& arvore<T>::obtemMaior() const{
    auto atual = this;
    while(true) {
        if(atual->dir == nullptr) {
            return atual->data;
        } else {
           atual = atual->dir;
        }
    }
}

template <typename T> void arvore<T>::obtemMenoresQue(lista<T> & result, const T & algo) {
    auto arv = this;
    arv->inicia();
    while (! arv->fim()) {
        T dado = arv->proximo();
        if(dado <= algo)result.anexa(dado);
    }
}

template <typename T> void arvore<T>::obtemMaioresQue(lista<T> & result, const T & algo) {
    auto arv = this;
    arv->inicia();
    while (! arv->fim()) {
        T dado = arv->proximo();
        if(dado >= algo)result.anexa(dado);
    }
}

template <typename T> void arvore<T>::obtemIntervalo(lista<T>& result, const T& start, const T& end) {
    auto arv = this;

    //arv->inicia();
    //while (! arv->fim()) {
        //T dado = arv->proximo();
        //if((dado >= start) && (dado <= end))result.anexa(dado);
    //}


    T dado = arv->data;
    if(arv->data >= start && arv->data <= end){
        result.anexa(dado);
        if(arv->esq != nullptr) arv->esq->obtemIntervalo(result, start, end);
        if(arv->dir != nullptr) arv->dir->obtemIntervalo(result, start, end);
    }
    else if (arv->data < start) {
        if(arv->dir != nullptr)arv->dir->obtemIntervalo(result, start, end);
    }
    else if (arv->data > end){
        if(arv->esq != nullptr)arv->esq->obtemIntervalo(result, start, end);
    }

}

template <typename T> T arvore<T>::obtem_sucessor(const T & algo) {
    if(algo >= obtemMaior())throw -1;
    T aux = obtemMaior();

    auto atual = this;

    while(true) {
        if(atual->data > algo) {
            if(atual->data < aux)aux = atual->data;
            if(atual->esq == nullptr)return aux;
                atual = atual->esq;
        } else {
            if(atual->dir == nullptr)return aux;
            atual = atual->dir;
        }
    }

}

};

#endif	/* ARVORE_IMPL_H */

