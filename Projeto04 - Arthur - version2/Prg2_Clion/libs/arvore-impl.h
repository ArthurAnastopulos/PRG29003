/* 
 * File:   arvore-impl.h
 * Author: sobral
 *
 * Created on 8 de Outubro de 2016, 19:37
 */

#ifndef ARVORE_IMPL_H
#define	ARVORE_IMPL_H

#include "arvore.h"
#include <sstream>
#include <ostream>

using std::ostream;
using std::ostringstream;
using std::endl;

namespace prglib {

template <typename T> arvore<T>::~arvore() {    
}
    
template <typename T> arvore<T>::arvore() : BasicTree() {    
}

template <typename T> arvore<T>::arvore(const T & dado) : data(dado),BasicTree((void*)&data) {    
}

//template <typename T> arvore<T>::arvore(const arvore<T> & outra) : BasicTree(outra) {}

template <typename T> BasicTree * arvore<T>::create(void * p_dado) {
    T * o = (T*)p_dado;
    arvore<T> * ptr = new arvore<T>(*o);
    return (BasicTree*) ptr;
}

template <typename T> void arvore<T>::adiciona(const T & algo) {
    BasicTree::adiciona((void*)&algo);
}

template <typename T> const T& arvore<T>::obtem(const T & algo)  {
    T * o = (T*)BasicTree::obtem((void*)&algo);
    return *o;
}

template <typename T> const T& arvore<T>::obtem() {
    return this->data;
}

template <typename T> arvore<T> * arvore<T>::esquerda() {
    return static_cast<arvore<T>*>(this->esq);
}

template <typename T> arvore<T> * arvore<T>::direita() {
    return static_cast<arvore<T>*>(this->dir);
}

template <typename T> void arvore<T>::listeEmLargura(lista<T> & result) {
    lista<void*> l;
    
    BasicTree::listeEmLargura(l);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> void arvore<T>::listeInOrder(lista<T> & result) {
    lista<void*> l;
    
    BasicTree::listeInOrder(l);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> void arvore<T>::listePreOrder(lista<T> & result) {
    lista<void*> l;
    
    BasicTree::listePreOrder(l);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> void arvore<T>::listePostOrder(lista<T> & result) {
    lista<void*> l;
    
    BasicTree::listePostOrder(l);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> unsigned int arvore<T>::tamanho() const {
    return BasicTree::tamanho();
}

template <typename T> int arvore<T>::fatorB()  {
    return BasicTree::fatorB();
}

template <typename T> unsigned int arvore<T>::altura()  {
    return BasicTree::altura();
}

template <typename T> arvore<T>* arvore<T>::balanceia() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::balanceia();
    return ptr;
}

template <typename T> arvore<T>* arvore<T>::balanceia(bool otimo) {
    arvore<T> * ptr = (arvore<T>*)BasicTree::balanceia(otimo);
    return ptr;
}

template <typename T> void arvore<T>::inicia() {
    BasicTree::inicia();
}

template <typename T> T& arvore<T>::proximo() {
    T * ptr = (T*)BasicTree::proximo();
    return *ptr;
}

template <typename T> bool arvore<T>::fim() {
    return BasicTree::fim();
}

template <typename T> void arvore<T>::iniciaPeloFim() {
    BasicTree::rinicia();
}

template <typename T> T& arvore<T>::anterior() {
    T * ptr = (T*)BasicTree::rproximo();
    return *ptr;
}

template <typename T> bool arvore<T>::inicio() {
    return BasicTree::rfim();
}

template <typename T> T& arvore<T>::obtemMenor() const{
    T * ptr = (T*)BasicTree::obtemMenor();
    return *ptr;    
}

template <typename T> T arvore<T>::remove(const T & algo) {
    if (not (esq or dir)) throw -1; // tem apenas raiz
    
    T coisa;
    BasicTree::remove((void*)&algo, (void*)&coisa);
    return coisa;    
}

template <typename T> T& arvore<T>::obtemMaior() const{
    T * ptr = (T*)BasicTree::obtemMaior();
    return *ptr;    
}

template <typename T> void arvore<T>::obtemMenoresQue(lista<T> & result, const T & algo) {
    lista<void*> l;
    BasicTree::obtemMenoresQue(l, (void*)&algo);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> void arvore<T>::obtemMaioresQue(lista<T> & result, const T & algo) {
    lista<void*> l;
    BasicTree::obtemMaioresQue(l, (void*)&algo);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> void arvore<T>::obtemIntervalo(lista<T>& result, const T& start, const T& end) {
    lista<void*> l;
    BasicTree::obtemIntervalo(l, (void*)&start, (void*)&end);
    l.inicia();
    while (not l.fim()) result.anexa(*(T*)l.proximo());
}

template <typename T> arvore<T> * arvore<T>::rotacionaL() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::rotacionaL();
    return ptr;
}

template <typename T> arvore<T> * arvore<T>::rotacionaR() {
    arvore<T> * ptr = (arvore<T>*)BasicTree::rotacionaR();
    return ptr;
}

template <typename T> void arvore<T>::atribui(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    *o1 = *o2;
}
    // comparara????o de igualdade
template <typename T> bool arvore<T>::ehIgual(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 == *o2;
}
    
    // compara????o de preced??ncia: *p1 < *p2
template <typename T> bool arvore<T>::ehMenor(void * p1, void * p2) {
    T * o1 = (T*)p1;
    T * o2 = (T*)p2;
    return *o1 < *o2;
}
    // destroi dado
template <typename T> void arvore<T>::destroi(void * p1) {
    T * o1 = (T*)p1;
    delete o1;
}

    template <typename T> void desenha_nodos(arvore<T> * arv, ostream & out) {
        auto raiz = arv->obtem();
        auto esq = arv->esquerda();
        auto dir = arv->direita();

        if (! esq and ! dir) out << raiz << endl;
        else {
            if (esq) {
                out << raiz << " -- " << esq->obtem() << endl;
                if (esq->altura()) desenha_nodos(esq, out);
            }
            if (dir) {
                out << raiz << " -- " << dir->obtem() << endl;
                if (dir->altura()) desenha_nodos(dir, out);
            }
        }

    }

    template <typename T> string desenha_arvore(arvore<T> * arv) {
        ostringstream out;

        out << "strict graph {" << endl;
        desenha_nodos(arv, out);
        out << "}" << endl;

        return out.str();
    }

};

#endif	/* ARVORE_IMPL_H */

