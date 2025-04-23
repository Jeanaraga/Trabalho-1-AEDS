#include "Animal.hpp"

Animal::Animal(int startX, int startY)
{
     x = startX;
     y = startY;
     passos = 0;
     vivo = true;
     salvo = false;
}

void Animal::mover(vector<vector<int>> &matriz, ostream &os)
{
     if (!vivo)
     {
          os << "Animal já está morto.\n";
          return;
     }

     if(rota.empty())
     {
          bool achou =  calcularRota(matriz);
          if(!achou)
          {
               os << "Animal não encontrou uma rota para a água.\n";
               return;
          }
     }

     auto [novaX, novaY] = rota.front();
     rota.pop();

     os << " O animal se moveu de (" << x << ", " << y << ") para (" << novaX << ", " << novaY << ").\n";
     x = novaX;
     y = novaY;
     passos++;

     if (matriz[x][y] == 4) // Se o animal chegou na água
     {
          salvo = true;
          os << "Animal chegou na água e está salvo!\n";
          matriz[x][y] = 0; // Marca a célula como vazia
          aplicarUmidadeAoRedor(matriz); // Aplica umidade ao redor
          return;
     }
}

void Animal::aplicarUmidadeAoRedor(vector<vector<int>> &matriz)
{
     int linhas = matriz.size();
     int colunas = matriz[0].size();

     // Aplica umidade nas células adjacentes
     for (int dx = -1; dx <= 1; dx++)
     {
          for (int dy = -1; dy <= 1; dy++)
          {
               if (dx == 0 && dy == 0)
                    continue; // Ignora a própria célula

               int novaX = x + dx;
               int novaY = y + dy;

               if (novaX >= 0 && novaX < linhas && novaY >= 0 && novaY < colunas)
               {
                    if (matriz[novaX][novaY] == 1)
                    {                              // Se for uma árvore saudável
                         matriz[novaX][novaY] = 4; // Marca como úmida
                    }
               }
          }
     }
}


bool Animal::calcularRota(vector<vector<int>> &matriz)
{
     int linhas =  matriz.size();
     int colunas = matriz[0].size();
     vector<vector<bool>> visitado(linhas, vector<bool>(colunas, false));
     

     queue<pair<int, int>> fila;
}



// GET E SETTERS PADRÃO

int Animal::getX() const
{
     return x;
}

int Animal::getY() const
{
     return y;
}

int Animal::getPassos() const
{
     return passos;
}

bool Animal::estaVivo() const
{
     return vivo;
}
bool Animal::estaSalvo() const
{
     return salvo;
}

bool Animal::setVivo(bool vivo)
{
     this->vivo = vivo;
     return this->vivo;
}
