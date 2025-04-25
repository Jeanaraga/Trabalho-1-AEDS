#include "Floresta.hpp"
#include "PropagacaoFogo.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Floresta::Floresta()
{
    linhas = 0;
    colunas = 0;
}

bool Floresta::carregarMatriz(const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return false;
    }

    int fogoLinha, fogoColuna;
    arquivo >> linhas >> colunas >> fogoLinha >> fogoColuna;

    matriz.resize(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            arquivo >> matriz[i][j];
        }
    }

    // Coloca o início do fogo na posição informada
    matriz[fogoLinha][fogoColuna] = 2;

    arquivo.close();
    return true;
}




void Floresta::simular(int iteracoes, char direcao, const string &nomeArquivo)
{
    ofstream arq(nomeArquivo);
    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para gravação." << endl;
        return;
    }

    resumoInicial(arq, direcao); // imprime info da matriz inicial

    for (int k = 0; k < iteracoes; ++k)
    {
        arq << "Iteração " << k + 1 << ":\n";
        animal.mover(matriz, arq);

        if (animal.estaSalvo()) {
            arq << "Animal salvo!\n";
            break;
        }

        if (matriz[animal.getX()][animal.getY()] == 2) {
            animal.setVivo(false);
            arq << "Animal morreu por fogo!\n";
            break;
        }

        PropagacaoFogo::propagarFogo(matriz, linhas, colunas, direcao, arq);
        imprimirIteracao(k + 1, arq); // imprime a matriz com a numeração da iteração

        if (!PropagacaoFogo::temFogo(matriz)) {
            arq << "Não há mais fogo na floresta. Simulação encerrada.\n";
            break;
        }
    }

    resumoFinal(arq);
    arq.close();
}



void Floresta::resumoFinal(ostream &os) const
{
    os << "\nResumo da simulação:\n";
    os << "Animal na posição: (" << animal.getX() << ", " << animal.getY() << ")\n";
    os << "Passos dados: " << animal.getPassos() << "\n";
    if (animal.estaVivo())
    {
        os << "Animal está vivo.\n";
    }
    else
    {
        os << "Animal está morto.\n";
    }

    os << "\nMatriz final:\n";
    imprimirMatriz(os);
}

void Floresta::resumoInicial(ostream &os, char direcao) const
{
    os << "Matriz inicial:\n";
    os << "Linhas: " << linhas << ", Colunas: " << colunas << "\n";
    os << "Direção do vento: " << direcao << "\n";
    imprimirMatriz(os);
    os << "\n";
}

void Floresta::imprimirMatriz(ostream &os) const
{
    for (const auto &linha : matriz)
    {
        for (int celula : linha)
        {
            os << celula << " ";
        }
        os << "\n";
    }
}

vector<vector<int>> Floresta::getMatriz() const
{
    return matriz;
}

void Floresta::imprimirIteracao(int iteracao, ostream& os) const {
    
    os << "\nMatriz após Iteração " << iteracao << ":\n";
    imprimirMatriz(os);
    os << "\n";
}

