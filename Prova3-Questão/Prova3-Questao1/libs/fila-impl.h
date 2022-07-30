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
        //copia N, cap, inicio, fim da orig;
        N = orig.N;
        cap = orig.cap;

        inicio = orig.inicio;
        fim = orig.fim;

        //cria um buffer com o cap e copia da dado por dado da fila orig.
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
            cap = outra.cap; //copia cap, N da orig;
            N = outra.N;

            //deleta qualquer informação na memoria q existia na fila originalmente;
            delete[] buffer;
            //cria um buffer com o cap e copia da dado por dado da fila orig.
            buffer = new T[cap];

            for (int cont = 0; cont < N; cont++)buffer[cont] = outra.buffer[cont];
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

        //buffer[inicio] = algo; //aloca algo a posiçao inicio.
        //N++;  //Incrementa a quantidade.

        //if(inicio == cap) inicio = 0;
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
        if(vazia()) throw -1; //Se estiver vazia, gera uma execeção;
        else {
            fim--; //Decrementa o fim para entra na posição do buffer q possui o ultimo dado;
            T & dado = buffer[fim];
            N--; //decrementa a quantidade;
            if(fim == 0)fim = cap; //se fim for zero volta para o cap(fila circular);
            return dado;
        }
    }

    template <typename T> T & fila<T>::frente() {
        if(vazia()) throw -4;//Gera uma exceçãp se vazia;
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

//Incompleto...
    template <typename T> void fila<T>::esvazia() const{
        //delete buffer;
    }

    template <typename T> void fila<T>::inverte() {
        if(N < 2)return;
        int cont = 0;

        int aux1 = inicio;
        int aux2 = fim;

        do{
            T & dado1 = buffer[aux1];
            buffer[aux1] = buffer[aux2];
            buffer[aux2] = dado1;


            aux1++;
            aux2--;
            cont++;
        } while (cont != N);
    }

} // fim namespace

#endif	/* FILA_IMP_H */
