/* 
 * File:   pilha.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef PILHA_H
#define	PILHA_H

#include <cstdlib>

namespace prglib {
    
template <typename T> class pilha  {
 public:
  // construtor: deve-se informar a capacidade da pilha
  pilha(unsigned int umaCapacidade);
 
  // construtor de cópia: cria uma pilha que é cópia de outra
  pilha(const pilha<T>& outra);
 
  // destrutor da pilha
  ~pilha();
 
  // operador de atribuição: torna esta pilha uma cópia de outra pilha
  pilha<T> & operator=(const pilha<T> & outra);
 
  // operações da pilha
 
  void push(const T & dado); // empilha um dado
 
  T pop(); // desempilha um dado
 
  const T& top() const; // retorna o dado do topo da pilha, sem retirá-lo

  // retorna true se pilha estiver vazia
  bool vazia() const;

  // retorna true se pilha estiver cheia
  bool cheia() const;

  // retorna a quantidade de dados armazenados na pilha
  unsigned int comprimento() const;

  // esvazia a pilha
  void esvazia();

  // retorna a capacidade da pilha (quantos dados cabem nela)
  unsigned int capacidade() const;

private:
  unsigned int N, topo;
  T * buffer;
};

} // fim do namespace

#include <libs/pilha-impl.h>

#endif	/* PILHA_H */

