#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
using namespace std;

class Animal
{
private:
    int x, y;
    int passos;
    bool vivo;
    bool salvo;
    int tentativas = 3;
    queue<pair<int, int>> rota;

    
    pair<int, int> bfsAteAgua(const vector<vector<int>> &matriz,
                              vector<vector<bool>> &visitado,
                              vector<vector<pair<int, int>>> &anterior);

    queue<pair<int, int>> reconstruirCaminho(
        const vector<vector<pair<int, int>>> &anterior,
        pair<int, int> destino);

    void salvarRota(const queue<pair<int, int>> &novaRota);

public:
    Animal();

    void mover(vector<vector<int>> &matriz, ostream &os);
    void aplicarUmidadeAoRedor(vector<vector<int>> &matriz);

    bool calcularRota(vector<vector<int>> &matriz);
    pair<int, int> escolherPosicaoInicialAleatoria(const vector<vector<int>> &matriz);

    // Getters e setters
    int getX() const;
    int getY() const;
    int getPassos() const;
    bool estaVivo() const;
    bool estaSalvo() const;
    bool setVivo(bool vivo);
};
