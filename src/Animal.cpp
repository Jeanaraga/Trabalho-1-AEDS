#include "Animal.hpp"
#include <stack>
#include <cstdlib>
#include <ctime>

Animal::Animal()
{

     passos = 0;
     vivo = true;
     salvo = false;
}

void Animal::mover(vector<vector<int>> &matriz, ostream &os){
     if (!vivo){
          os << "Animal já está morto.\n";
          return;
     }

     // Verifica se a próxima posição da rota foi queimada
     if (!rota.empty()) {
          auto [nx, ny] = rota.front();
          if (matriz[nx][ny] == 2 || matriz[nx][ny] == 3)
          {
               os << "Na rota (" << nx << "," << ny << ") encontrou fogo. Animal morreu.\n";
               rota = queue<pair<int, int>>(); // limpa rota
          }
     }

     while (rota.empty() && tentativas > 0){
          pair<int, int> novaPos = escolherPosicaoInicialAleatoria(matriz);
          if (novaPos.first == -1) {
               vivo = false;
               os << "Nenhuma posição livre encontrada para recomeçar. Animal morreu.\n";
               return;
          }

          x = novaPos.first;
          y = novaPos.second;
          os << "Nova tentativa! Animal renasce em (" << x << "," << y << ")\n";

          bool achou = calcularRota(matriz);
          if (!achou) {
               tentativas--;
          } else break;
     
     }

     if (rota.empty()){
          os << "Animal não conseguiu encontrar rota após 3 tentativas. Morreu cercado.\n";
          vivo = false;
          return;
     }

     auto [novaX, novaY] = rota.front();
     rota.pop();

     if (x == novaX && y == novaY){
          os << "O animal comecou em (" << x << "," << y << ").\n";
          return;
     }

     os << "Animal se moveu de (" << x << "," << y << ") para (" << novaX << "," << novaY << ")\n";
     x = novaX;
     y = novaY;
     passos++;

     if (matriz[x][y] == 4){
          salvo = true;
          os << "Animal chegou na água e está salvo!\n";
          matriz[x][y] = 0;
          aplicarUmidadeAoRedor(matriz);
     }
}


bool Animal::calcularRota(vector<vector<int>> &matriz)
{
     int linhas = matriz.size();
     int colunas = matriz[0].size();
     vector<vector<bool>> visitado(linhas, vector<bool>(colunas, false));
     vector<vector<pair<int, int>>> anterior(linhas, vector<pair<int, int>>(colunas, {-1, -1}));

     pair<int, int> destino = bfsAteAgua(matriz, visitado, anterior);
     if (destino.first == -1) return false;

     auto novaRota = reconstruirCaminho(anterior, destino);
     salvarRota(novaRota);

     return true;
}

pair<int, int> Animal::bfsAteAgua(const vector<vector<int>> &matriz,
                                  vector<vector<bool>> &visitado,
                                  vector<vector<pair<int, int>>> &anterior)
{
     int linhas = matriz.size();
     int colunas = matriz[0].size();
     queue<pair<int, int>> fila;
     fila.push({x, y});
     visitado[x][y] = true;

     while (!fila.empty()){
          auto [cx, cy] = fila.front();
          fila.pop();

          if (matriz[cx][cy] == 4) return {cx, cy}; // achou a água

          vector<pair<int, int>> direcoes = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
          for (auto [dx, dy] : direcoes){

               int nx = cx + dx;
               int ny = cy + dy;

               if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny] && matriz[nx][ny] != 3) {

                    visitado[nx][ny] = true;
                    anterior[nx][ny] = {cx, cy};
                    fila.push({nx, ny});
               }
          }
     }

     return {-1, -1}; // não achou água
}

queue<pair<int, int>> Animal::reconstruirCaminho(const vector<vector<pair<int, int>>> &anterior,pair<int, int> destino){

     queue<pair<int, int>> caminho;
     pair<int, int> atual = destino;

     while (atual != make_pair(-1, -1)){
          caminho.push(atual);
          atual = anterior[atual.first][atual.second];
     }

     return caminho;
}

void Animal::salvarRota(const queue<pair<int, int>> &novaRota){
     stack<pair<int, int>> invertida;
     queue<pair<int, int>> copia = novaRota;

     while (!copia.empty()){
          invertida.push(copia.front());
          copia.pop();
     }

     while (!invertida.empty()){
          rota.push(invertida.top());
          invertida.pop();
     }
}

void Animal::aplicarUmidadeAoRedor(vector<vector<int>> &matriz){
     int linhas = matriz.size();
     int colunas = matriz[0].size();

     // Aplica umidade nas células adjacentes
     for (int dx = -1; dx <= 1; dx++){
          for (int dy = -1; dy <= 1; dy++) {
               if (dx == 0 && dy == 0)
                    continue; // Ignora a própria célula

               int novaX = x + dx;
               int novaY = y + dy;

               if (novaX >= 0 && novaX < linhas && novaY >= 0 && novaY < colunas){
                    if (matriz[novaX][novaY] != 0){ // Se for uma árvore saudável
                         matriz[novaX][novaY] = 1;
                    }
               }
          }
     }
}

pair<int, int> Animal::escolherPosicaoInicialAleatoria(const vector<vector<int>> &matriz)
{
     vector<pair<int, int>> posicoesValidas;
     int linhas = matriz.size();
     int colunas = matriz[0].size();

     for (int i = 0; i < linhas; ++i){
          for (int j = 0; j < colunas; ++j){
               if (matriz[i][j] == 0) {
                    posicoesValidas.push_back({i, j});
               }
          }
     }

     if (posicoesValidas.empty()) return {-1, -1}; // Nenhuma posição válida encontrada

     int indiceAleatorio = rand() % posicoesValidas.size();
     return posicoesValidas[indiceAleatorio]; // Retorna uma posição aleatória
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
