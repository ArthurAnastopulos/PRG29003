/*
 * File:   lista-impl.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 09:02
 */

#ifndef LISTA2_IMPL_H
#define	LISTA2_IMPL_H

namespace prglib {


template <typename T> lista<T>::lista() {
    // o guarda é criado automaticamente
    len = 0;

    atual = &guarda;
}

template <typename T> lista<T>::lista(const lista<T> & outra) {
    len = 0;
    for(Nodo * nodo = outra.guarda.proximo; nodo != &outra.guarda; nodo = nodo->proximo) {
        anexa(nodo->dado);
    }
}

template <typename T> lista<T>::lista(std::istream &inp) {
    //inverso do escreva-se;sepera
}

template <typename T> lista<T>::~lista() {
    esvazia();
}

template <typename T> void lista<T>::insere(const T& algo) {
    auto dado = new Nodo(algo);

    dado->conecta(guarda.proximo);

    /*Nodo * sucessor = guarda.proximo;
    dado->proximo = sucessor;
    guarda.proximo = dado;
    dado->anterior = &guarda;
    sucessor->anterior = dado;*/

    len++;
}

template <typename T> void lista<T>::anexa(const T& algo) {
    auto dado = new Nodo(algo);
    dado->conecta(&guarda);

    /*Nodo * last = guard.anterior;
    dado->proximo = &guarda;
    guarda.anterior = dado;
    dado->anterior = last;
    last->proximo = dado;*/

    len++;
}

template <typename T> void lista<T>::anexa(const lista<T> & dados) {
    for(Nodo * nodo = dados.guarda.proximo; nodo != &dados.guarda; nodo = nodo->proximo) {
        auto dado = new Nodo(nodo->dado);
        dado->conecta(&guarda);
        len++;
    }
}

template <typename T> int lista<T>::comprimento() const {
    return len;
}

template <typename T> void lista<T>::esvazia() {
    while(len != 0) {
        T algo = remove(0);
    }
}

template <typename T> void lista<T>::insere(const T& algo, int posicao) {
    if(posicao >= len) anexa(algo);
    else {
        auto dado = new Nodo(algo);

        Nodo * ptr = guarda.proximo;
        for (/*posicao*/; posicao > 0; posicao--) {
            ptr = ptr->proximo;
        }
        dado->conecta(ptr);

        len++;
    }
}

template <typename T> T& lista<T>::obtem(int posicao) const {
    if(posicao >= len) throw -1;

    Nodo * ptr = guarda.proximo;
    for(/*posicao*/;posicao > 0;posicao--) {
        ptr = ptr->proximo;
    }

    return ptr->dado;
}

template <typename T> T& lista<T>::operator[](int pos) const {
    obtem(pos);
}

template <typename T> void lista<T>::escrevaSe(std::ostream& out) const {
    escrevaSe(out, "\n");
}

template <typename T> void lista<T>::escrevaSe(std::ostream& out, const std::string & delim) const {
    if(vazia()) return;
    Nodo * ptr = guarda.proximo;
    for(ptr = guarda.proximo; ptr != guarda.anterior; ptr = ptr->proximo){
        out << ptr->dado << delim;
    }
    out << guarda.anterior->dado;

}

template <typename T> T lista<T>::remove(int posicao) {
    if(posicao >= len) throw -1;

    Nodo * ptr = guarda.proximo;
    for(/*posicao*/;posicao > 0;posicao--) {
        ptr = ptr->proximo;
    }
    ptr->desconecta();
    T dado = ptr->dado;
    delete ptr;
    len--;
    return dado;
}

template <typename T> int lista<T>::trunca(int posicao) {
    if(len == 0) return 0;
    if(posicao > len) return 0;

    Nodo * ptr;
    int j = len - posicao;
    int aux = 0;
    while(aux < j) {
        ptr = guarda.proximo;
        int i = posicao - aux;
        for(/*posicao*/; i > 1;i--) {
            ptr = ptr->proximo;
        }
        ptr->desconecta();
        len--;
        aux++;
    }
    delete ptr;
    return aux;
}

template <typename T> void lista<T>::retira(const T& algo) {
    Nodo * ptr;
    Nodo * aux;
    for(aux = guarda.proximo; aux != guarda.anterior; aux = aux->proximo) {
        ptr = ptr->proximo;
        T dado = ptr->dado;
        if(dado == algo) {
            ptr->desconecta();
            len--;
        }
    }
}

template <typename T> bool lista<T>::vazia() const {
    return len == 0;
}

template <typename T> void lista<T>::insereOrdenado(const T & algo) {
    insere(algo);
    ordena();
}

template <typename T> void lista<T>::ordena() {
    ordenaSelection();
}

template <typename T> void lista<T>::ordenaSelection() {
    if(len < 2) return;

    for(Nodo * ptr = guarda.proximo; ptr != guarda.anterior; ptr = ptr->proximo) {
        Nodo * menor = ptr;
        for(Nodo * aux = ptr->proximo; aux != &guarda; aux = aux->proximo) {
            if (menor->dado > aux->dado) menor = aux;
        }
        if(menor != ptr) {
            T dado = ptr->dado;
            ptr->dado = menor->dado;
            menor->dado = dado;
        }
    }
}

template <typename T> void lista<T>::ordenaBolha() {
    if(len < 2) return;

    for(Nodo * ptr = guarda.anterior; ptr != guarda.proximo;ptr = ptr->anterior) {
        for(Nodo * aux = guarda.proximo; aux != ptr; aux = aux->proximo) {
            if(aux->proximo->dado < aux->dado) {
                T dado = aux->dado;
                aux->dado = aux->proximo->dado;
                aux->proximo->dado = dado;
            }
        }
    }

}

template <typename T> T& lista<T>::procura(const T& algo) const {
    for(Nodo * aux = guarda.proximo; aux != &guarda; aux = aux->proximo){
        if(aux->dado == algo) {
            T & dado = aux->dado;
            return dado;
        }
    }
    throw -1;
}

template <typename T> lista<T>& lista<T>::procuraMuitos(const T& algo, lista<T>& outra) const {
    for(Nodo * aux = guarda.proximo; aux != &guarda; aux = aux->proximo){
        if(aux->dado == algo) {
            T & dado = aux->dado;
            outra.anexa(dado);
        }
    }
    if(outra.vazia())throw -1;
    return outra;
}

template <typename T> std::shared_ptr<lista<T>> lista<T>::procuraMuitos(const T& algo) const {
    lista<T> outra;
    return procuraMuitos(algo, outra);
}

template <typename T> lista<T>& lista<T>::operator=(const lista<T>& outra) {
    esvazia();
    for(Nodo * nodo = outra.guarda.proximo; nodo != &outra.guarda; nodo = nodo->proximo) {
        anexa(nodo->dado);
    }
}

template <typename T> bool lista<T>::operator==(const lista<T>& outra) const {
    if(len != outra.len) return false;
    else {
        Nodo * aux = guarda.proximo;
        for(Nodo * nodo = guarda.proximo; nodo != &guarda; nodo = nodo->proximo) {
            if(nodo->dado != aux->dado)return false;
            aux = aux->proximo;
        }
    }
    return true;
}

template <typename T> void lista<T>::inverte() {
    if(len < 2) return;

    Nodo * ptr = &guarda;
    do {
        Nodo * aux = ptr->proximo;
        ptr->proximo = ptr->anterior;
        ptr->anterior = aux;
        ptr = aux;
    } while (ptr != &guarda);
}

template <typename T> bool lista<T>::inicio() const {
    return atual == &guarda;
}

template <typename T> bool lista<T>::fim() const {
    return atual == &guarda;
}

template <typename T> void lista<T>::inicia() {
    atual = guarda.proximo;
}

template <typename T> void lista<T>::iniciaPeloFim() {
    atual = guarda.anterior;
}

template <typename T> T& lista<T>::proximo() {
    if(fim()) throw -1;

    T &aux = atual->dado;
    atual = atual->proximo;
    return aux;
}

template <typename T> T& lista<T>::anterior() {
    if(inicio()) throw -1;

    T &aux = atual->dado;
    atual = atual->anterior;
    return aux;
}

template <typename T> lista<T>& lista<T>::sublista(unsigned int pos1, unsigned int pos2, lista<T> & outra) const {
    if((pos1 < 0) || (pos2 >= len))throw -1;
    if(pos2 < pos1)throw -1;

    for(int i = pos1; i <= pos2; i++) {
        T & dado = obtem(i);
        outra.anexa(dado);
    }
}

template <typename T> lista<T>* lista<T>::sublista(unsigned int pos1, unsigned int pos2) const {
    lista<T> outra;
    return sublista(pos1,pos2,outra);
}

template <class T> void lista<T>::embaralha() {
    if(len < 2)return;

    for(int i = len-1; i > 0; i--) {
        int j = rand() % (i + 1);

        if (i != j) {
            T & dado1 = obtem(i);
            T & dado2 = obtem(j);

            T aux = dado1;
            dado1 = dado2;
            dado2 = aux;
        }
    }
}

} // fim namespace

#endif	/* LISTA_IMPL_H */

