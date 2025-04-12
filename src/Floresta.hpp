#pragma once
#include <vector>
#include <string>
#include <ostream>
using namespace std;

class Floresta {
private:
    int linhas, colunas;
    vector<vector<int>> matriz;

public:
    Floresta();

    bool carregarDeArquivo(const string& nomeArquivo);

    // Métodos de impressão
    void imprimirMatriz() const;
    void imprimirMatriz(ostream& os) const;
    
    vector<vector<int>> getMatriz() const;

    // Método para atualizar a matriz e salvar em um arquivo
    void atualizarESalvar(int iteracoes, char direcao, const string& nomeArquivo);

    // Método para verificar se ainda há fogo na floresta
    bool temFogo() const;
};
