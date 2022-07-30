/* 
 * File:   fila-imp.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef FILA_IMP_H
#define	FILA_IMP_H

namespace prglib {
    
template <typename T> fila<T>::fila(unsigned int max_itens) {
    if(max_itens == 0) throw -1;
    cap = max_itens; //capacidade max da fila.
    N = 0;  //quantidade de dados armazenados no momento.

    inicio = 0;  //posiçao inicial.
    fim = 0;  //posiçao final.

    buffer = new T[cap]; //alocaçao da area da memoria da fila.
}

template <typename T> fila<T>::fila(const fila& orig) {
    N = orig.N;
    cap = orig.cap;

    inicio = orig.inicio;
    fim = orig.fim;

    buffer = new T[cap];

    unsigned int i = inicio;
    int cont = 0;
    while (cont != N) {
        buffer[i] = orig.buffer[i];
        i++;
        if(i == cap)i = 0;
        cont++;
    }
}

template <typename T> fila<T>::~fila() {
    delete[] buffer;
}

template <typename T> fila<T>& fila<T>::operator=(const fila& outra) {
    if(cap < outra.cap) {
        cap = outra.cap;
        N = outra.N;

        delete[] buffer;
        buffer = new T[cap];

        for (int cont = 0; cont < N; cont++) {
            buffer[cont] = outra.buffer[cont];
        }
    }
}

template <typename T> void fila<T>::enfileira(const T& algo) {
    if(cheia()) throw -2; //Se estiver cheia, gera uma execeçao.
    buffer[fim] = algo; //aloca algo a posiçao fim.

    N++;  //Incrementa a quantidade e passa o fim para a posição seguinte.
    fim++;
    if(fim == cap)fim = 0; //Se o fim igual a cap volta para 0.
    //fim = (fim + 1) % cap; ^2.
}

//incompleto...
template <typename T> void fila<T>::enfileiraDoComeco(const T& algo) {
    if(cheia()) throw -2; //Se estiver cheia, gera uma execeçao.

    buffer[inicio] = algo; //aloca algo a posiçao fim.
    N++;  //Incrementa a quantidade e passa o fim para a posição seguinte.

    if(inicio == cap) inicio = 0;
}

template <typename T> T fila<T>::desenfileira() {
    if(vazia()) throw -3; //Se estiver vazia, gera uma execeçao.
    T & dado = buffer[inicio];

    N--; //Decrementa a quantidade e aumenta a posiçao do inicio.
    inicio++;

    if(inicio == cap) inicio = 0; //Se o inicio for igual a cap volta para 0.

    return dado;
}

template <typename T> T fila<T>::desenfileiraDoFim() {
    if(vazia()) throw -1;
    else {
        fim--;
        T & dado = buffer[fim];
        N--;
        if(fim == 0)fim = cap;
        return dado;
    }
}

template <typename T> T & fila<T>::frente() {
    if(vazia()) throw -4;
    return buffer[inicio];
}

template <typename T> bool fila<T>::vazia() const {
    return N == 0;
}

template <typename T> bool fila<T>::cheia() const {
    return N == cap;
}

template <typename T> unsigned int fila<T>::capacidade() const {
    return cap;
}

template <typename T> unsigned int fila<T>::comprimento() const {
    return N;
}

template <typename T> void fila<T>::esvazia() const{
}

} // fim namespace

#endif	/* FILA_IMP_H */

