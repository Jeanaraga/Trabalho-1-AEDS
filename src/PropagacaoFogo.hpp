#pragma once
#include <vector>
#include <string>
#include <ostream>

// A classe PropagacaoFogo é responsável por encapsular toda a lógica de propagação.
class PropagacaoFogo {
public:
    // Método que recebe a matriz original, o número de linhas e colunas, e retorna a nova matriz atualizada
    // Também recebe um ostream para gravar os eventos da propagação (seja arquivo, console ou outro stream)
    static void propagarFogo(std::vector<std::vector<int>>& matriz, int linhas, int colunas,char direcao, std::ostream& os);
};
