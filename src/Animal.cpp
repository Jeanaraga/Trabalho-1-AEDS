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

     pair<int, int> melhorMov = encontrarMelhorPosicao(matriz);
     int novaX = melhorMov.first;
     int novaY = melhorMov.second;

     if (novaX != -1 && novaY != -1)
     {
          // Atualiza a posição do animal
          matriz[x][y] = 0; // Marca a posição antiga como vazia
          x = novaX;
          y = novaY;
          passos++;

          

          if (matriz[x][y] == 4)
          {
               salvo = true;
               os << "Animal se moveu para " << x << "," << y << " e encontrou água! Animal salvo!\n";
               matriz[x][y] = 0; // Marca a posição como vazia após encontrar água
               aplicarUmidadeAoRedor(matriz);
          }
          else
          {
               os << "O animal esta cercado e não pode se mover em " << x << "," << y << "\n";
          }
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

pair<int, int> Animal::encontrarMelhorPosicao(vector<vector<int>> &matriz)
{
     int linhas = matriz.size();
     int colunas = matriz[0].size();

     vector<pair<int, int>> direcaos = {
         {-1, 0}, // cima
         {1, 0},  // baixo
         {0, -1}, // esquerda
         {0, 1}   // direita
     };

     pair<int, int> melhorPosicao = {-1, -1};

     int melhorPrioridade = -1;

     for (auto [dx, dy] : direcaos)
     {
          int novaX = x + dx;
          int novaY = y + dy;

          if (novaX >= 0 && novaX < linhas && novaY >= 0 && novaY < colunas)
          {
               int valorCelula = matriz[novaX][novaY];
               int prioridade = prioridadeCelula(valorCelula);

               // Se a célula é válida e tem prioridade maior que a melhor encontrada
               if (prioridade > melhorPrioridade)
               {
                    melhorPrioridade = prioridade;
                    melhorPosicao = {novaX, novaY};
               }
          }
     }

     return melhorPosicao;
}

int Animal::prioridadeCelula(int valor) const
{

     if (valor == 4)
          return 0; // agua
     if (valor == 0)
          return 1; // vazio
     if (valor == 1)
          return 2; // arvore saudavel
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

