#pragma once
#include <vector>
#include <string>
#include <ostream>
#include "Animal.hpp"
using namespace std;

class Floresta {
private:
    int linhas, colunas;
    vector<vector<int>> matriz;
    Animal animal;

public:
    Floresta();

    bool carregarMatriz(const string& nomeArquivo);

    // Métodos de impressão
    void imprimirIteracao(int iteracao, ostream& os) const;
    void imprimirMatriz(ostream& os) const;
    void resumoFinal(ostream& os) const;
    void resumoInicial(ostream& os, char direcao) const;
    
    vector<vector<int>> getMatriz() const;

    // Método para atualizar a matriz e salvar em um arquivo
    void simular(int iteracoes, char direcao, const string& nomeArquivo);

    
};
