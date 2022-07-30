//Header Fila.

#ifndef FILA_H
#define	FILA_H

namespace prglib {
    
template <typename T> class fila {
public:
    // construtor: cria uma fila capaz de armazenmar até max_itens.
    fila(unsigned int max_itens);

    // construtor de cópia: cria uma fila que é uma cópia idêntica de outra fila.
    fila(const fila<T>& orig);

    // destrutor: destroi a fila, liberando qualquer memória alocada.
    ~fila();

    // enfileira um dado. Dispara uma exceção se fila estiver cheia.
    void enfileira(const T & algo);

    //Incompleto. -> enfileira um dado no começo da fila. Dispara uma exceção se a fila estiver cheia.
    void enfileiraDoComeco(const T & algo);
   
    // desenfileira um dado. Dispara uma exceção se fila estiver vazia
    T desenfileira();

    //desenfileira um dado do fim. Dispara uma exceção se a fila estiver vazia.
    T desenfileiraDoFim();

    // retorna uma referência ao dado que está na frente da fila
    T & frente();

    // retorna true se fila estiver vazia
    bool vazia() const;

    // retorna true se fila estiver cheia
    bool cheia() const;

    // retorna a quantidade de dados armazenada na fila
    unsigned int comprimento() const;

    // retorna a capacidade da fila
    unsigned int capacidade() const;

    // operador de atribuição: torna esta fila uma cópia da outra fila
    fila<T>& operator=(const fila<T> & outra);

    //Incompleto. -> esvazia a fila.
    void esvazia() const;

private:
    // N: quantidade de dados armazenados na fila
    // cap: capacidade da fila
    unsigned int N, cap;

    // buffer: área de memória onde estão armazenados os dados 
    //         implementada como um vetor a ser criado no construtor
    T * buffer;

    // inicio: posição do início da fila no buffer
    // fim: posição do fim da fila no buffer
    unsigned int inicio, fim;
};

}

#include <libs/fila-impl.h>

#endif	/* FILA_H */

