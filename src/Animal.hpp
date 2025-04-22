#pragma once
#include <vector>
#include <ostream>
using namespace std;

class Animal {
private:
    int x, y; // posição atual
    int passos;
    bool vivo;
    bool salvo;

    pair<int,int> encontrarMelhorPosicao(vector<vector<int>>& matriz);
    int prioridadeCelula(int celula) const;

public:
    Animal(int startX, int startY);

    void mover(vector<vector<int>>& matriz, ostream& os);
    void aplicarUmidadeAoRedor(vector<vector<int>>& matriz);

    int getX() const;
    int getY() const;
    int getPassos() const;
    bool estaVivo() const;
    bool estaSalvo() const;
    bool setVivo(bool vivo);
};
