#include "src/Floresta.hpp"
#include "src/PropagacaoFogo.hpp"
#include <iostream>
using namespace std;

int main() {
    Floresta floresta;

    if (!floresta.carregarDeArquivo("src/input.dat")) {
        cerr << "Erro ao carregar a floresta." << endl;
        return 1;
    }

    // Se desejar, pode imprimir a matriz inicial no arquivo também
    floresta.atualizarESalvar(5, "src/output.dat");

    cout << "Simulação finalizada! Verifique o arquivo output.dat para a saída completa." << endl;
    return 0;
}
