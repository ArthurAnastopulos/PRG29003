// Projeto 01 -> Distância de Bacon
// Feito por Arthur Anastopulos dos Santos
// Data de entegra: 3/09/2019

#include <iostream>
#include <prglib.h>
#include <string>
#include "Mapa.h"

using namespace std;
using prglib::pilha;
using prglib::fila;

//Struct usada como o nó dos algoritmos.
struct path_bacon{
    string node; //Nó atual.
    string path; //Caminho até o nó atual.
    int dist; //Distância até o nó.
};

//Algoritmo de Busca em Largura.
path_bacon busca_bfs(path_bacon & caminho, string actor) {
    //um objeto Mapa que acessa o conteúdo do arquivo.
    Mapa dados("../data/dados.txt");

    //Fila da Busca e auxliares para o objeto mapa.
    fila<path_bacon> aux(1024000);
    fila<string> filmes(1024000);
    fila<string> atores(1024000);

    //String auxliares e um inteiro contador.
    string aux1,aux2;
    int n = 0;

    //Enfileira nó inicial.
    caminho.node = "Kevin Bacon";
    caminho.path += "Kevin Bacon";
    caminho.dist = n;

    aux.enfileira(caminho);

    while(! aux.vazia()) {
        caminho = aux.desenfileira();
        if(caminho.node == actor)return caminho;
        n = caminho.dist + 1;

        //Se não for o nó procurado, para cada nó adjacente ao nó desenfileirado, enfileira o nó adjacente.

        filmes = dados.obtem_filmes(caminho.node);

        while(! filmes.vazia()){
            aux2 = filmes.desenfileira();
            atores = dados.obtem_atores(aux2);

            while(! atores.vazia()){
                aux1 = atores.desenfileira();

                path_bacon novo = caminho;

                novo.node = aux1;
                novo.path += " -> ";
                novo.path += aux2;
                novo.path += " -> ";
                novo.path += aux1;
                novo.dist = n;
                
                aux.enfileira(novo);
            }
        }
    }
}

//Algoritmo de Busca em Profundidade.
path_bacon busca_dfs(path_bacon & caminho,string actor){
    //um objeto Mapa que acessa o conteúdo do arquivo.
    Mapa dados("../data/dados.txt");

    //Pilha da Busca e filas auxliares para o objeto mapa.
    pilha<path_bacon> aux(1024000);
    fila<string> filmes(1024000);
    fila<string> atores(1024000);

    //String auxliares e um inteiro contador.
    string aux1,aux2;
    int n = 0;

    //empilha o nó inicial
    caminho.node = "Kevin Bacon";
    caminho.path += "Kevin Bacon";
    caminho.dist = n;

    aux.push(caminho);

    while(! aux.vazia()) {
        caminho = aux.pop();
        if(caminho.node == actor)return caminho;
        n = caminho.dist + 1;

        //Se não for o nó procurado, para cada nó adjacente ao nó desempilhado, empilha o nó adjacente.

        filmes = dados.obtem_filmes(caminho.node);

        while(! filmes.vazia()){
            aux2 = filmes.desenfileira();
            atores = dados.obtem_atores(aux2);

            while(! atores.vazia()){
                aux1 = atores.desenfileira();

                path_bacon novo = caminho;

                novo.node = aux1;
                novo.path += " -> ";
                novo.path += aux2;
                novo.path += " -> ";
                novo.path += aux1;
                novo.dist = n;

                aux.push(novo);
            }
        }
    }
}

//Função para mostrar a Distância e a Sequencia percorrida, após a busca.
void show_path(path_bacon & caminho){
    cout << "Caminho percorrido: " << caminho.path;
    cout << endl;
    cout << "Distância de Bacon: " << caminho.dist;
}

int main() {
    string star;
    path_bacon caminho;
    int escolha;


    //Digita o nome do ator q deseja fazer a busca, tambêm impede de escolher o proprio Kevin Bacon.
    cout << "Digite o nome de um ator: ";
    while(true){
        getline(cin, star);
        if(star != "Bacon" || star != "Kevin Bacon")break;
    }

    cout << endl;

    //Permite o usuarío escolher, qual o tipo de busca deseja fazer.
    cout << "Escolha um metodo[1 -> bfs ou 2 -> dfs]: ";
    while(true){
        cin >> escolha;
        if(escolha == 1 || escolha == 2)break;
    }
    switch(escolha){
        case 1:
            busca_bfs(caminho,star);
            show_path(caminho);
            break;
        case 2:
           busca_dfs(caminho,star);
           show_path(caminho);
           break;
    }

    return 0;
}