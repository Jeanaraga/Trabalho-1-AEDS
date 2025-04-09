#include "Floresta.hpp"
#include <fstream>
#include <iostream>

Floresta::Floresta() {
    linhas = 0;
    colunas = 0;
}

bool Floresta::carregarDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return false;
    }

    int fogoLinha, fogoColuna;
    arquivo >> linhas >> colunas >> fogoLinha >> fogoColuna;

    matriz.resize(linhas, std::vector<int>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo >> matriz[i][j];
        }
    }

    // Coloca o início do fogo
    matriz[fogoLinha][fogoColuna] = 2;

    arquivo.close();
    return true;
}

void Floresta::atualizar() {
    std::vector<std::vector<int>> novaMatriz = matriz;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) { // Em chamas
                novaMatriz[i][j] = 3; // Vira queimada

                // Verifica vizinhos ortogonais
                if (i > 0 && matriz[i - 1][j] == 1) novaMatriz[i - 1][j] = 2;
                if (i < linhas - 1 && matriz[i + 1][j] == 1) novaMatriz[i + 1][j] = 2;
                if (j > 0 && matriz[i][j - 1] == 1) novaMatriz[i][j - 1] = 2;
                if (j < colunas - 1 && matriz[i][j + 1] == 1) novaMatriz[i][j + 1] = 2;
            }
        }
    }

    matriz = novaMatriz;
}

void Floresta::imprimir() {
    for (const auto& linha : matriz) {
        for (int celula : linha) {
            std::cout << celula << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> Floresta::getMatriz() const {
    return matriz;
}
