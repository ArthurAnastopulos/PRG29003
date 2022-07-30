/* 
 * File:   hash-impl.h
 * Author: msobral
 *
 * Created on 11 de Agosto de 2016, 13:59
 */

#ifndef HASH_IMPL_H
#define	HASH_IMPL_H

namespace prglib {
    
template <typename T> thash<T>::thash(int num_linhas) {
}

template <typename T> thash<T>::thash(const thash & outro)  {
}

template <typename T> thash<T>::~thash() {
}

template <typename T> void thash<T>::adiciona(const std::string& chave, const T& algo) {
}

template <typename T> T& thash<T>::operator[](const std::string& chave) {
}

template <typename T> T& thash<T>::obtem(const std::string& chave) {
}

template <typename T> bool thash<T>::existe(const std::string& chave) const {
}

template <typename T> void thash<T>::esvazia() {
}

template <typename T> T thash<T>::remove(const std::string& chave) {
}

template <typename T> unsigned int thash<T>::tamanho() const {
}

template <typename T> std::shared_ptr<lista<std::string>> thash<T>::chaves() const {
}

template <typename T> std::shared_ptr<lista<T>> thash<T>::valores() const {
}
    
}

#endif	/* HASH_IMPL_H */

