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
        len = 0; //anexa nodo por nodo da "outra" lista gerando uma copia;
        for(Nodo * nodo = outra.guarda.proximo; nodo != &outra.guarda; nodo = nodo->proximo)anexa(nodo->dado);
    }

//Incompleto...
    template <typename T> lista<T>::lista(std::istream &inp) {
        //inverso do escreva-se;sepera
    }

    template <typename T> lista<T>::~lista() {
        esvazia(); //Esvazia como destrutor;
    }

    template <typename T> void lista<T>::insere(const T& algo) {
        auto dado = new Nodo(algo);

        dado->conecta(guarda.proximo); //conecta dado após a guarda.proximo;


        //Modelo sem o uso do conecta;
        /*Nodo * sucessor = guarda.proximo;
        dado->proximo = sucessor;
        guarda.proximo = dado;
        dado->anterior = &guarda;
        sucessor->anterior = dado;*/

        len++;
    }

    template <typename T> void lista<T>::anexa(const T& algo) {
        auto dado = new Nodo(algo);
        dado->conecta(&guarda); //conecta dado;

        //Modelo sem o uso do conecta;
        /*Nodo * last = guard.anterior;
        dado->proximo = &guarda;
        guarda.anterior = dado;
        dado->anterior = last;
        last->proximo = dado;*/

        len++;
    }

    template <typename T> void lista<T>::anexa(const lista<T> & dados) {
        //Anexa os "dados" da lista gerendo em uma outra lista;
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
        while(len != 0)T algo = remove(0); //remove dado por dado até a lista ficar vazia;
    }

    template <typename T> void lista<T>::insere(const T& algo, int posicao) {
        if(posicao >= len) anexa(algo); //se posição for maior que len anexa ao final da lista;
        else {
            auto dado = new Nodo(algo);

            //localiza a posição e conecta o nodo;
            Nodo * ptr = guarda.proximo;
            for (/*posicao*/; posicao > 0; posicao--)ptr = ptr->proximo;
            dado->conecta(ptr);

            len++;
        }
    }

    template <typename T> T& lista<T>::obtem(int posicao) const {
        if(posicao >= len) throw -1;

        //localização e retorna;
        Nodo * ptr = guarda.proximo;
        for(/*posicao*/;posicao > 0;posicao--)ptr = ptr->proximo;

        return ptr->dado;
    }

    template <typename T> T& lista<T>::operator[](int pos) const {
        obtem(pos); //chama internamente obtem(pos);
    }

    template <typename T> void lista<T>::escrevaSe(std::ostream& out) const {
        escrevaSe(out, "\n"); //chama escrevaSe() com delimitador "\n";
    }

    template <typename T> void lista<T>::escrevaSe(std::ostream& out, const std::string & delim) const {
        if(vazia()) return;
        Nodo * ptr = guarda.proximo; //escreve nodo por nodo até o penultimo nodo;
        for(ptr = guarda.proximo; ptr != guarda.anterior; ptr = ptr->proximo)out << ptr->dado << delim;
        //escreve o penultimo nodo;
        out << guarda.anterior->dado;
    }

    template <typename T> T lista<T>::remove(int posicao) {
        if(posicao >= len) throw -1; //Se uma posição maior q len, gera uma exceção;

        Nodo * ptr = guarda.proximo;
        for(/*posicao*/;posicao > 0;posicao--)ptr = ptr->proximo;//Localiza nodo e desconecta;
        ptr->desconecta();
        T dado = ptr->dado;
        delete ptr; //deleta o ptr; e decrementa len;
        len--;
        return dado; //retorna o dado;
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
            for(/*posicao*/; i > 1;i--)ptr = ptr->proximo;
            ptr->desconecta();
            len--;
            aux++;
        }
        delete ptr;
        return aux;
    }

    template <typename T> void lista<T>::retira(const T& algo) {
        Nodo * ptr;
        Nodo * aux; //Localiza a posições que possuem "algo" e desconecta ele da lista;
        for(aux = guarda.proximo; aux != guarda.anterior; aux = aux->proximo) {
            ptr = ptr->proximo;
            T dado = ptr->dado;
            if(dado == algo) {
                ptr->desconecta();
                len--; //decrementa len;
            }
        }
    }

    template <typename T> bool lista<T>::vazia() const {
        return len == 0;
    }

    template <typename T> void lista<T>::insereOrdenado(const T & algo) {
        insere(algo); //insere e ordena internamente a lista;
        ordena();
    }


    template <typename T> void lista<T>::ordena() {
        ordenaSelection(); //Usa metodo ordernaSelection
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

//Metodo de ordenamento não recomendado;
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
            if(aux->dado == algo) { //localiza o nodo q possui "algo" e retorna se encontra
                T & dado = aux->dado;
                return dado;
            }
        }
        throw -1; //gera exceção não encontrando o dado;
    }

    template <typename T> lista<T>& lista<T>::procuraMuitos(const T& algo, lista<T>& outra) const {
        for(Nodo * aux = guarda.proximo; aux != &guarda; aux = aux->proximo){
            if(aux->dado == algo) {
                T & dado = aux->dado;
                outra.anexa(dado); //Igual procura, mas anexa em uma lista o dado toda vez q for encontrado;
            }
        }
        if(outra.vazia())throw -1; //se a "outra" lista
        return outra;
    }

    template <typename T> std::shared_ptr<lista<T>> lista<T>::procuraMuitos(const T& algo) const {
        lista<T> outra;
        return procuraMuitos(algo, outra);
    }

    template <typename T> lista<T>& lista<T>::operator=(const lista<T>& outra) {
        esvazia(); //esvazia a lista, anexa dado por dado da "outra" lista;
        for(Nodo * nodo = outra.guarda.proximo; nodo != &outra.guarda; nodo = nodo->proximo)anexa(nodo->dado);
    }

    template <typename T> bool lista<T>::operator==(const lista<T>& outra) const {
        if(len != outra.len) return false; //comprimento diferentes retorna false;
        else {
            Nodo * aux = guarda.proximo;
            for(Nodo * nodo = guarda.proximo; nodo != &guarda; nodo = nodo->proximo) {
                if(nodo->dado != aux->dado)return false;
                aux = aux->proximo; //Verifica se toodos os dados são iguais na lista, e na mesmas posições;
            }
        }
        return true;
    }

    template <typename T> void lista<T>::inverte() {
        if(len < 2) return; //não faz nada para uma lista de um ou menos de comprimento;

        Nodo * ptr = &guarda;
        do { //troca de lugar os nodos, ficando com as suas posições invertidas;
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
        if(pos2 < pos1)throw -1; //verifica se as posições estao de acordo, se não gera uma exceção.

        for(int i = pos1; i <= pos2; i++) {
            T & dado = obtem(i);
            outra.anexa(dado); //anexa em uma "outra" lista os dados que estao dentro daquela posições;
        }
    }

    template <typename T> lista<T>* lista<T>::sublista(unsigned int pos1, unsigned int pos2) const {
        lista<T> outra;
        return sublista(pos1,pos2,outra);
    }

    template <class T> void lista<T>::embaralha() {
        if(len < 2)return;

        //gera alteatoriamente dois dados e troca eles de lugar;
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
