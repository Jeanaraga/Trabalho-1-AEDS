#include "src/Floresta.hpp"
#include <iostream>

int main() {
    Floresta floresta;

    if (!floresta.carregarDeArquivo("input.dat")) {
        std::cerr << "Erro ao carregar a floresta." << std::endl;
        return 1;
    }

    std::cout << "Matriz inicial:\n";
    floresta.imprimir();

    floresta.atualizar();

    std::cout << "\nMatriz após 1 atualização:\n";
    floresta.imprimir();

    return 0;
}
