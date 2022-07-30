/* 
 * File:   arvore.h
 * Author: msobral
 *
 * Created on 12 de Agosto de 2016, 13:12
 */

#ifndef ARVORE_H
#define	ARVORE_H

#include <libs/BasicTree.h>
#include <string>


using std::string;

namespace prglib {
    
template <typename T> class arvore : private BasicTree{
 public:
  arvore();
  //arvore(const arvore<T> & outra);
  arvore(const T & dado);
  virtual ~arvore();

  // adiciona um dado à árvore
  void adiciona(const T& algo);

  // obtém um dado da árvore
  const T& obtem(const T & algo);

  // obtém o valor da raiz da árvore
  const T& obtem();

  // enumera os dados in-order, pre-order, post-order e breadth-first
  void listeInOrder(lista<T> & result);
  void listePreOrder(lista<T> & result);
  void listePostOrder(lista<T> & result);
  void listeEmLargura(lista<T> & result);

  // retorna a quantidade de dados na árvore
  unsigned int tamanho() const;

  // retorna a subárvore esquerda
  arvore<T> * esquerda();

  // retorna a subárvore direita
  arvore<T> * direita();

  // itera a árvore
  void inicia();
  bool fim();
  T& proximo();

  // itera a árvore de forma reversa
  void iniciaPeloFim();
  bool inicio();
  T& anterior();

  // remove um dado
  T remove(const T & algo);

  // retorna o menor dado
  T & obtemMenor() const;

  // retorna o maior dado
  T & obtemMaior() const;

  // copia na lista "result" os dados menores que "algo"
  void obtemMenoresQue(lista<T> & result, const T & algo);

  // copia na lista "result" os dados maiores que "algo"
  void obtemMaioresQue(lista<T> & result, const T & algo);
  
  // obtém todos valores entre "start" e "end" (inclusive)
  void obtemIntervalo(lista<T> & result, const T & start, const T & end);

    // retorna a altura da folha mais distante da raiz
    unsigned int altura() ;

    // retorna o fator de balanceamento
    int fatorB() ;

    // balanceia a árvore
    arvore<T> * balanceia();

    // balanceia a árvore repetidamente, até que a altura não mais se reduza
    arvore<T> * balanceia(bool otimo);

 protected:
     T data;
     
    // atribuição: *p1 <- *p2
    virtual void atribui(void * p1, void * p2);
    // compararação de igualdade
    virtual bool ehIgual(void * p1, void * p2);
    // comparação de precedência: *p1 < *p2
    virtual bool ehMenor(void * p1, void * p2);
    // destroi dado
    virtual void destroi(void * p1);
    
    virtual BasicTree * create(void * p_dado);
    
  arvore<T> * rotacionaL();
  arvore<T> * rotacionaR();
    
};

// gera uma descrição de um diagrama DOT para a árvore
// O resultado deve ser gravado em arquivo para se gerar o diagrama
// com o programa "dot" ou "dotty"
template <typename T> string desenha_arvore(arvore<T> * arv);

} // fim do namespace

#include <libs/arvore-impl.h>

#endif	/* ARVORE_H */

