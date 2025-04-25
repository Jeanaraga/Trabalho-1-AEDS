#include "PropagacaoFogo.hpp"
#include <iostream>
#include <string>
using namespace std;

void PropagacaoFogo::propagarFogo(vector<vector<int>>& matriz, int linhas, int colunas, char direcao, ostream& os) {
    // Cria uma nova matriz para registrar as atualizações sem interferir na iteração atual
    vector<vector<int>> novaMatriz = matriz;

    

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) { // célula em chamas
                // A célula em chamas passa a ser queimada
                
                novaMatriz[i][j] = 3;
                os << "(" << i << "," << j << ") virou 3 (queimado)\n";

                // Verifica os vizinhos ortogonais e atualiza os que são árvores saudáveis (valor 1)
                if ((i > 0 && matriz[i - 1][j] == 1) && (direcao == '-' || direcao == 'N')) {
                    novaMatriz[i - 1][j] = 2;
                    os << "(" << i - 1 << "," << j << ") virou 2 (fogo) [abaixo]\n";
                }
                if ((i < linhas - 1 && matriz[i + 1][j] == 1) && (direcao == '-' || direcao == 'S')) {
                    novaMatriz[i + 1][j] = 2;
                    os << "(" << i + 1 << "," << j << ") virou 2 (fogo) [acima]\n";
                }
                if ((j > 0 && matriz[i][j - 1] == 1) && (direcao == '-' || direcao == 'L')) {
                    novaMatriz[i][j - 1] = 2;
                    os << "(" << i << "," << j - 1 << ") virou 2 (fogo) [direita]\n";
                }
                if ((j < colunas - 1 && matriz[i][j + 1] == 1) && (direcao == '-' || direcao == 'O')) {
                    novaMatriz[i][j + 1] = 2;
                    os << "(" << i << "," << j + 1 << ") virou 2 (fogo) [esquerda]\n";
                }
            }
        }
    }

    // Atualiza a matriz original com as mudanças da nova matriz
    matriz = novaMatriz;
}

bool PropagacaoFogo::temFogo(const vector<vector<int>>& matriz) {
    for (const auto& linha : matriz) {
        for (int celula : linha) {
            if (celula == 2) { // Se houver fogo
                return true;
            }
        }
    }
    return false;
}
