/* 
 * File:   pilha-impl.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef PILHA_IMPL_H
#define	PILHA_IMPL_H

#include "pilha.h"


namespace prglib {
    
template <typename T> pilha<T>::pilha(unsigned int umaCapacidade) {
    N = umaCapacidade; //capacidade.
    topo = 0; //topo inicial.
    buffer = new T[N]; //cria buffer.
}
 
template <typename T> pilha<T>::pilha(const pilha& outra) {
    N = outra.N;
    topo = outra.topo;

    buffer = new T[N];
    for(int cont = 0; cont < topo; cont++){
        buffer[cont] = outra.buffer[cont];
    }
}
 
template <typename T> pilha<T>::~pilha() {
    delete[] buffer; //deleta buffer.
}

template <typename T> pilha<T> & pilha<T>::operator=(const pilha<T> & outra) {
    if(N < outra.N) {
        N = outra.N;
        topo = outra.topo;

        delete[] buffer;
        buffer = new T[N];

        for(int cont = 0; cont < topo; cont++) {
            buffer[cont] = outra.buffer[cont];
        }

    }
}
 
template <typename T> void pilha<T>::esvazia() {
    topo = 0; //zera o topo.
    delete[] buffer; //deleta tudo q está dentro.
    buffer = new T[N]; //cria um buffer novo.
}
 
template <typename T> void pilha<T>::push(const T & dado) {
    if(topo < N){ //Se for menor q topo adiciona o dado, aumenta o tamanho do topo.
        buffer[topo] = dado;
        topo++;
    } else throw -2;
}
 
template <typename T> T pilha<T>::pop() {
    if(topo == 0)throw -3;

    topo--;//Decrementa o topo.
    T dado = buffer[topo]; //Pega o q esta no topo.

    return dado;//retorna o dado.
}
 
template <typename T> const T& pilha<T>::top() const{
    return buffer[topo-1]; //retorna o topo.
}

template <typename T> unsigned int pilha<T>::capacidade() const {
    return N; //retorna umaCapacidade/N.
}

template <typename T> bool pilha<T>::cheia() const {
    return topo == N; //True se for topo igual N.
}

template <typename T> bool pilha<T>::vazia() const {
    return topo == 0;//True se for topo igual zero.
}

template <typename T> unsigned int pilha<T>::comprimento() const {
    int cont = topo; //retorna o valor inteiro do topo.
    return cont;
}

}

#endif	/* PILHA_IMPL_H */

