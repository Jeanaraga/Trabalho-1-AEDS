#include "src/Floresta.hpp"
#include "src/config.hpp"

int main() {
    // posição inicial do animal (exemplo: 5,5)
    Floresta floresta(5, 5);

    if (!floresta.carregarDeArquivo("src/input.dat")) return 1;

    floresta.atualizarESalvar(NUMERO_ITERACOES, DIRECAO_VENTO, "src/output.dat");

    return 0;
}
