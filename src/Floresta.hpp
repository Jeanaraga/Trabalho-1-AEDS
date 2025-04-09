#pragma once
#include <vector>
#include <string>

class Floresta {
private:
    int linhas, colunas;
    std::vector<std::vector<int>> matriz;

public:
    Floresta(); // Construtor padrão

    bool carregarDeArquivo(const std::string& nomeArquivo);
    void atualizar();

    void imprimir(); // apenas para debug
    std::vector<std::vector<int>> getMatriz() const;
};
