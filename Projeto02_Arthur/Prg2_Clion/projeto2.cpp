#include "projeto2.h"

//Defines dos limites das quantidades de atores e filmes permitidos pelo programa.
#define QUANTIDADE 50
#define QUANTIDADE_FILMES 200

//Função para separação de linhas apartir de um separador.

lista<string> separa(const string & algo, const string & sep){
    //Variaveis auxiliares da função.
    lista <string> aux;
    int i = 0, j = 0;
    string posf;

    //laço que encontra a palavra por palavra apartir de um separador.

    while(true) {
        i = algo.find_first_not_of(sep, j);
        j = algo.find_first_of(sep, i);

        if(i == string::npos) break;
        posf = algo.substr(i, j-i);
        aux.anexa(posf);
    }

    return aux;
}

//Função que cria um mapa das informações do arquivo.

lista <info> mapa(const string & path) {
    //Variaveis auxiliares do programa.
    ifstream arq(path);
    string aux1,aux2;
    info local;

    //lista auxliares do programa.
    lista<string> auxliar1;
    lista<info> auxliar2;

    //Verifica se o arquivo não é invalido e entao monta o mapa das informaçoes em uma lista.
    if(! arq.is_open()){
        cout << "Arquivo Invalido!" << endl;
        throw -1;
    }
    while(getline(arq, aux1)){
        //Usa função separa para separar as 3 informações do arquivo
        auxliar1 = separa(aux1,";");
        if( auxliar1.comprimento() == 3) { //Ao obter 3 informações da linha, anexa elas a uma lista de estrutura(Info).
            local.filme = auxliar1.obtem(0);
            local.ano = auxliar1.obtem(1);

            aux2 = auxliar1.obtem(2);
            local.atores = separa(aux2, ",");

            auxliar2.anexa(local);
            auxliar1.esvazia();
        }
    }

    return auxliar2;
}

//Sobrecarga de operador para o ordenamento, apatir do ano.

bool operator<(const hollywood & int1, const hollywood & int2) {
    return int1.ano < int2.ano;
}

//Função que obtem uma lista de filmes ordena pelo ano.

lista <hollywood> obtem_filmes(const lista <info> & mapa, lista <hollywood> & movie, const string & escolha) {
    //Variaveis auxliares do programa.
    info aux2;
    hollywood aux3;
    lista <info> copia = mapa;
    lista <string> aux1;

    //Iteração para criar a lista de filmes da função.
    copia.inicia();
    while(! copia.fim()) {
        aux2 = copia.proximo();
        aux1 = aux2.atores;
        aux1.inicia();
        while(! aux1.fim()) {  //iteração da lista de atores q participaram de um filme
            string ator = aux1.proximo();
            if(ator == escolha) {  //Encontrar o ator na lista, anexa o fime e o ano em uma lista.
                aux3.filme = aux2.filme;
                aux3.ano = stoi(aux2.ano);
                movie.anexa(aux3);
            }
        }
    }

    //Ordena os filmes pelo ano.
    movie.ordena();
    return movie;
}

//Função que obtem uma lista de atores, ordenada alfabeticamente.

lista <string> obtem_atores(const lista <info> & mapa, lista <string> & actor, const string & escolha) {
    //Variaveis auxliares da função.

    info aux;
    lista <info> copia = mapa;

    //Iteração do mapa para gerar uma lista de atores.

    copia.inicia();
    while(! copia.fim()) {
        aux = copia.proximo();
        if(aux.filme == escolha) { //Econtra o filme escolhido no mapa, anexa em uma lista os atores q participaram.
            actor = aux.atores;
            actor.ordena(); //Ordena os atores alfabeticamente.
            return actor;
        }
    }
}

//Função que busca atores apartir de um dado ator.

lista <string> busca_atores(const lista <info> & mapa, lista <string> & atores,const string & escolha) {
    //Lista auxiliares da função.
    lista <hollywood> movies;
    lista <string> actors;
    lista <info> copia = mapa;

    //Variaveis auxiliares da função.
    hollywood aux1;
    string aux3,aux4;

    //Usa a função obtem filmes para obter todos os filmes feito pelo ator.
    obtem_filmes(copia,movies,escolha);

    //Iteração da lista de filmes feita pelo ator, para em seguida anexar todos os atores participantes do filmes.
    movies.inicia();
    while (! movies.fim()) {
        aux1 = movies.proximo();
        aux3 = aux1.filme;
        obtem_atores(copia,actors,aux3);
        actors.inicia();
        while(! actors.fim()) {
            aux4 = actors.proximo();
            atores.anexa(aux4);
        }
    }

    //Ordena a lista de atores alfabeticamente.
    atores.ordena();
    return atores;

}

//Função que obtem todos os atores do arquivo (Uso de um Define para limitar quantidade de atores, para reduizir o tempo de processamento).

lista <string> todos_atores(const lista <info> & mapa, lista <string> & atores) {
    //Lista do auxiliar do programa.
    lista <info> copia = mapa;

    //embaralha lista para q programa nao pegue sempre as mesma funçoes
    copia.embaralha();

    //Iteração para obter todos os atores do mapa.
    copia.inicia();
    while(! copia.fim()) {
        info aux1 = copia.proximo();
        lista <string> aux = aux1.atores;
        aux.inicia();
        while(! aux.fim()) {
            string aux2 = aux.proximo();
            atores.anexa(aux2);
            if(atores.comprimento() == QUANTIDADE) return atores; //limita a quantidade de atores para reduzir o tempo de processo do programa.
        }
    }
    return atores;
}


//Sobrecarga de operador para o ordenamento, apatir do numero de filmes que atuou.

bool operator<(const papeis & int1, const papeis & int2) {
    return int1.atuacoes < int2.atuacoes;
}

//Funções que gera uma lista ordenada de atores, apartir da quantidade de filmes atuados.

lista <papeis> ordena_atores_atuar(const lista <info> & mapa, lista <papeis> & atores, const lista <string> & actor) {

    //Lista e variaveis auxiliares do programa.

    lista <string> copia_atores = actor;
    lista <info> dados = mapa;
    lista <string> aux;
    lista <hollywood> filmes;
    papeis aux2;

    //Iteração da lista limitada de atores e ve a quantidade de filmes atoados pelo ator apartir da comprimento da lista da função obtem_filmes.

    copia_atores.inicia();
    while(! copia_atores.fim()) {
        string ator = copia_atores.proximo();
        obtem_filmes(dados,filmes,ator);
        aux2.ator = ator;
        aux2.atuacoes = filmes.comprimento();

        //anexa as informações em uma lista.

        atores.anexa(aux2);
    }

    //Ordena a lista apartir da quantidades de filmes atuados.
    atores.ordena();
    return atores;
}


//Função que cria uma lista de string limitada de filmes para um determinado ator.

lista <string> filmes_string(const lista <info> & mapa, lista <string> & movie, const string & escolha) {
    //Variaveis auxliares do programa.
    info aux2;
    string aux3;
    lista <info> copia = mapa;
    lista <string> aux1;

    //Iteração para criar a lista de filmes da função.
    copia.inicia();
    while(! copia.fim()) {
        aux2 = copia.proximo();
        aux1 = aux2.atores;
        aux1.inicia();
        while(! aux1.fim()) {  //iteração da lista de atores q participaram de um filme
            string ator = aux1.proximo();
            if(ator == escolha) {  //Encontrar o ator na lista, anexa o fime e o ano em uma lista.
                aux3 = aux2.filme;
                movie.anexa(aux3);
                if(movie.comprimento() == QUANTIDADE_FILMES)return movie;
            }
        }
    }

    return movie;
}


//Sobrecarga de operador para o ordenamento, apatir do numero de filmes que atuou.

bool operator<(const comum & int1, const comum & int2) {
    return int1.quantidade < int2.quantidade;
}

//Funções que gera uma lista ordenada de atores, apartir da quantidade de filmes atuados em comum com dado ator.

lista <comum> ordena_atores_comum(const lista <info> & mapa, lista <comum> & atores, const string & escolha) {
    //Lista auxiliares da função.
    lista <info> dados = mapa;
    lista <string> aux;
    lista <string> filmes_do_ator;
    lista <string> filmes_aux;

    //obtem todos os atores e filmes q o ator escolhido participou.
    busca_atores(dados, aux, escolha);
    filmes_string(dados, filmes_do_ator, escolha);

    comum info;

    //Iteração da lista de atores q participaram com um dado ator.

    aux.inicia();
    while(! aux.fim()) {
        string ator = aux.proximo();
        int Limitador = QUANTIDADE_FILMES;
        filmes_string(dados,filmes_aux,ator);
        filmes_aux.inicia();  //Iteração do filme de um ator q participou com o dado ator.
        while(! filmes_aux.fim()) {
            string aux1 = filmes_aux.proximo(); //Procura o filme na lista de filmes do dado ator
            try {
                filmes_do_ator.procura(aux1);
            }
            catch (...) {  //Se não encontrar o filme decrementa da quantidade total de filmes do ator.
                Limitador--;
            }
        }
        info.ator = ator;
        info.quantidade = Limitador; //anexa informações na lista
        atores.anexa(info);
        filmes_aux.esvazia();
    }
    //Ordena e retorna a lista.
    atores.ordena();
    return  atores;
}