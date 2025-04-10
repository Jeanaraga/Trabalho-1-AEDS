#include "Floresta.hpp"
#include "PropagacaoFogo.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Floresta::Floresta() {
    linhas = 0;
    colunas = 0;
}

bool Floresta::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return false;
    }

    int fogoLinha, fogoColuna;
    arquivo >> linhas >> colunas >> fogoLinha >> fogoColuna;

    matriz.resize(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo >> matriz[i][j];
        }
    }

    // Coloca o início do fogo na posição informada
    matriz[fogoLinha][fogoColuna] = 2;

    arquivo.close();
    return true;
}

void Floresta::imprimirMatriz() const {
    imprimirMatriz(cout);
}

void Floresta::imprimirMatriz(ostream& os) const {
    for (const auto& linha : matriz) {
        for (int celula : linha) {
            os << celula << " ";
        }
        os << "\n";
    }
}

vector<vector<int>> Floresta::getMatriz() const {
    return matriz;
}

void Floresta::atualizarESalvar(int iteracoes, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para gravação." << endl;
        return;
    }

    for (int k = 0; k < iteracoes; ++k) {
        //
        
        string cabecalho = "\n--- Iteração " + to_string(k + 1) + " ---\n";
        arq << cabecalho;  

        // Chama o método estático para propagar o fogo
        PropagacaoFogo::propagarFogo(matriz, linhas, colunas, arq);

        string matMsg = "\nMatriz após Iteração " + to_string(k + 1) + ":\n";
        arq << matMsg;
        
        imprimirMatriz(arq);
        arq << "\n"; // separador entre iterações
    }

    arq.close();
}
