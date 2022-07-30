/* 
 * File:   arvore.h
 * Author: msobral
 *
 * Created on 12 de Agosto de 2016, 13:12
 */

#ifndef ARVORE_H
#define	ARVORE_H

#include <istream>
#include <ostream>
#include <string>

using std::string;
using std::ostream;
using std::istream;

namespace prglib {
    
template <typename T> class arvore {
 public:
  // este construtor na prática não deve ser usado ...
  arvore();

  // cria um nodo da árvore, o qual contém o dado passado no parâmetro "dado"
  arvore(const T & dado);

  // cria uma árvore cujos nodos contêm os dados contidos na lista "dados"
  arvore(lista<T> & dados);

  // cria uma árvore cujos nodos contêm os dados contidos na stream "inp" (que pode ser um arquivo)
  arvore(istream & inp);

  // cria uma árvore que é uma cópia de "outra"
  arvore(const arvore<T> * outra);

  // destrutor da árvore
  ~arvore();

  // adiciona um dado à árvore
  void adiciona(const T& algo);

  // acessa um dado contido na árvore. OBS o dado acessado não pode ser modificado !
  const T& obtem(const T & algo) const;

  // obtém o valor da raiz da árvore. OBS esse valor não pode ser modificado !
  const T& obtem() const ;

  // operações de enumeração dos dados da árvore
  void listeInOrder(lista<T> & result);
  void listePreOrder(lista<T> & result);
  void listePostOrder(lista<T> & result);
  void listeEmLargura(lista<T> & result);

  void escrevaSe(ostream & out) const;

  // retorna a quantidade de dados contidos na árvore
  unsigned int tamanho() const;

  // retorna a altura da árvore
  unsigned int altura() ;

  // retorna o fator de balanceamento da árvore (em torno da raiz)
  int fatorB() ;

  // balanceia a árvore usando o algoritmo AVL
  // retorna a nova raiz da árvore
  arvore<T> * balanceia();

  // balanceia a árvore usando o algoritmo AVL
  // se o parâmetro "otimo" for true, repete o balanceamento sucessivamente, até que
  // a altura da árvore não mais reduza
  // retorna a nova raiz da árvore
  arvore<T> * balanceia(bool otimo);

  // retorna a subárvore esquerda
  arvore<T> * esquerda();

  // retorna a subárvore direita
  arvore<T> * direita();

  // Iteração da árvore (in-order)
  void inicia();
  bool fim();
  T& proximo();

  // iteração reversa da árvore (in-order)
  void iniciaPeloFim();
  bool inicio();
  T& anterior();

  // remove um dado da árvore. Retorna uma cópia do dado removido
  T remove(const T & algo);

  // obtém o menor dado contido na árvore. OBS esse dado não pode ser modificado
  const T & obtemMenor() const;

  // obtém o maior dado contido na árvore. OBS esse dado não pode ser modificado
  const T & obtemMaior() const;

  // obtém os dados menores que "algo"
  void obtemMenoresQue(lista<T> & result, const T & algo);

  // obtém os dados maiores que "algo"
  void obtemMaioresQue(lista<T> & result, const T & algo);

  // obtém todos valores entre "start" e "end" (inclusive)
  void obtemIntervalo(lista<T> & result, const T & start, const T & end);

  T obtem_sucessor(const T & dado);

  arvore<T> * rotacionaL();
  arvore<T> * rotacionaR();

  bool folha() const;

  void obtem_folhas(lista<T> & result);

 protected:
     T data;
     arvore<T> * esq, * dir, * pai;
     int h_nodo = 0;

     lista<arvore<T> *> * p_stack;
};

} // fim do namespace

#include <libs/arvore-impl.h>

#endif	/* ARVORE_H */

