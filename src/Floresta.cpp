#include "Floresta.hpp"
#include "PropagacaoFogo.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Floresta::Floresta()  {
    linhas = 0;
    colunas = 0;
}

bool Floresta::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return false;
    }

    int fogoLinha, fogoColuna;
    arquivo >> linhas >> colunas >> fogoLinha >> fogoColuna;

    matriz.resize(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo >> matriz[i][j];
        }
    }

    // Coloca o início do fogo na posição informada
    matriz[fogoLinha][fogoColuna] = 2;

    arquivo.close();
    return true;
}

void Floresta::imprimirMatriz() const {
    imprimirMatriz(cout);
}

void Floresta::imprimirMatriz(ostream& os) const {
    for (const auto& linha : matriz) {
        for (int celula : linha) {
            os << celula << " ";
        }
        os << "\n";
    }
}

bool Floresta::temFogo() const {
    for (const auto& linha : matriz) {
        for (int celula : linha) {
            if (celula == 2) { // Se houver fogo
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> Floresta::getMatriz() const {
    return matriz;
}

void Floresta::atualizarESalvar(int iteracoes,char direcao, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para gravação." << endl;
        return;
    }

    arq << "Matriz inicial:\n";
    // Imprime a matriz inicial
    arq << "Linhas: " << linhas << ", Colunas: " << colunas << "\n";
    arq << "Direção do vento: " << direcao << "\n";
    imprimirMatriz(arq);
    arq << "\n"; // separador entre iterações

    for (int k = 0; k < iteracoes; ++k) {
        //
        
        string cabecalho = "\n--- Iteração " + to_string(k + 1) + " ---\n";
        arq << cabecalho;  

        animal.mover(matriz, arq);

        // Verifica se o animal está salvo
        if (animal.estaSalvo()) {
            arq << "Animal salvo!\n";
            break;
        }

        // Se o anima esta no fogo, ele morre
        if (matriz[animal.getX()][animal.getY()] == 2) {
            animal.setVivo(false);
            if (animal.estaVivo()) {
                arq << "Animal está vivo.\n";
            } else {
                arq << "Animal morreu no fogo.\n";
            }   
            break;
        }

        

        // Chama o método estático para propagar o fogo
        PropagacaoFogo::propagarFogo(matriz, linhas, colunas,direcao, arq);

         string matMsg = "\nMatriz após Iteração " + to_string(k + 1) + ":\n";
         arq << matMsg;
        
         imprimirMatriz(arq);
         arq << "\n"; // separador entre iterações

        // Verifica se ainda há fogo na floresta
        if (!temFogo()) {
            arq << "Não há mais fogo na floresta. Simulação encerrada.\n";
            break;
        }

    }

    // Resumo da simulação
    arq << "\nResumo da simulação:\n";
    arq << "Animal na posição: (" << animal.getX() << ", " << animal.getY() << ")\n";
    arq << "Passos dados: " << animal.getPassos() << "\n";
    if (animal.estaVivo()) {
        arq << "Animal está vivo.\n";
    } else {
        arq << "Animal está morto.\n";
    }

    // Imprime a matriz final
    arq << "\nMatriz final:\n";
    imprimirMatriz(arq);



    arq.close();
}
