#include "src/Floresta.hpp"
#include "src/config.hpp" // onde estão NUM_MAX_ITERACOES e VENTO
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    Floresta floresta;


    floresta.carregarMatriz("datasets/input.dat");
    floresta.simular(NUMERO_ITERACOES,DIRECAO_VENTO, "datasets/output.dat");

    
    return 0;
}
