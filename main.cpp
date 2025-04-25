#include "src/Floresta.hpp"
#include "src/config.hpp" // onde estão NUM_MAX_ITERACOES e VENTO
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand(time(0)); // inicializa aleatoriedade uma vez só

    // Cria a floresta (posição do animal será definida dinamicamente)
    Floresta floresta;

    // Carrega a matriz do input.dat
    if (!floresta.carregarMatriz("input.dat")) {
        cerr << "Erro ao carregar o arquivo input.dat\n";
        return 1;
    }

    // Executa a simulação
    floresta.simular(NUMERO_ITERACOES,DIRECAO_VENTO, "output.dat");

    
    return 0;
}
