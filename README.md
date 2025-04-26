

# Trabalho 1 - AEDS

## 📝 Introdução

Este trabalho consiste na simulação de um incêndio em uma floresta, onde há um animal que precisa encontrar uma fonte de água para se salvar. A floresta é representada por uma matriz `N x M`, onde cada elemento numérico simboliza um tipo de célula:

- `0`: espaço vazio  
- `1`: árvore saudável  
- `2`: árvore em chamas  
- `3`: árvore queimada  
- `4`: água

Também são utilizadas variáveis globais para definir a estratégia de propagação do fogo, incluindo a **direção do vento**.

O objetivo é desenvolver:
1. Um **algoritmo que propague o fogo** pela floresta de acordo com as regras estabelecidas;
2. Um **algoritmo para a movimentação do animal**, que tenta fugir do fogo e alcançar uma célula com água (`4`).



### 🔥 Regras da Simulação

- As entradas e saídas de dados devem ser feitas apenas por **arquivos `.dat`**.
- Uma **árvore saudável (`1`) vira fogo (`2`)** se tiver **pelo menos um vizinho em chamas**.
- Uma **árvore em chamas (`2`) vira queimada (`3`)** após **uma iteração completa**.
- A propagação do fogo depende da variável global `DIRECAO_VENTO`:
  - Se **não houver vento**, o fogo se propaga em **todas as 4 direções ortogonais**.
  - Se **houver vento**, o fogo se propaga **apenas na direção especificada**.


🧠 Da Fuga do Animal

- O animal se move **antes da propagação do fogo**.
- Ele tenta encontrar um caminho para a água `4`.
- Se o caminho for bloqueado pelo fogo, o animal pode tentar **até 3 vezes** para tentar achar um novo caminho.
- Ao alcançar a água, a posição do animal vira `0` e os seus vizinhos `1`.



### 📁 Estrutura do Projeto

```
projeto/
├── build/               # Pasta para arquivos compilados via Makefile
├── datasets/            # Arquivos de entrada e saída
│   ├── input.dat        # Entrada: dimensões da matriz, fogo inicial, conteúdo da matriz
│   └── output.dat       # Saída: logs da simulação, matriz por iteração, status do animal
├── src/                 # Código-fonte da simulação
│   ├── Floresta.cpp/hpp         # Leitura da floresta, controle da simulação
│   ├── Animal.cpp/hpp           # Lógica da fuga do animal
│   ├── PropagacaoFogo.cpp/hpp   # Propagação do fogo com e sem vento
│   └── config.hpp               # Variáveis globais como direção do vento e número de iterações
├── main.cpp             # Ponto de entrada da aplicação
├── Makefile             # Compilação e execução
└── README.md            # Documentação
```

---

## 🧪 Metodologia

O trabalho foi dividido em **3 classes principais**, onde cada uma contém toda a lógica necessária para a simulação.

#### Classe `Floresta`
É a classe **central da simulação**, contendo os métodos principais `simular` e `carregarMatriz`, que são chamados no `main`.

- O método `carregarMatriz` é responsável por **ler o arquivo de entrada**, fazer a lógica de separação dos dados para definir o **tamanho da matriz**, **posição inicial do fogo** e os **elementos da floresta**.

- O método `simular` é responsável por:
  - Executar um **laço de repetição** definido por uma variável global de número de iterações.
  - Dentro do laço, ele chama:
    1. O método `mover` do animal (passando a matriz e o arquivo de saída como parâmetro);
    2. O método que espalha o fogo;
    3. E repete isso até o número de iterações acabar ou o fogo sumir da floresta.

####  Classe `Animal`
O método principal dessa classe é o `mover`, que foi **dividido em outros métodos menores**.

- Primeiro, ele faz **várias verificações**:
  - Se o próximo movimento foi comprometido (com fogo ou queimada);
  - Enquanto a rota estiver vazia e ainda houver tentativas sobrando:
    - Escolhe uma **nova posição para recomeçar** aleatoriamente;
    - **Procura um novo caminho** até a água com `calcularRota`;
    - Se encontrar, **sai do loop**.

- Depois dessa verificação:
  - Ele pega o **primeiro elemento da fila (rota)** e já o remove;
  - Move para essa nova posição;
  - Por fim, verifica se chegou na água. Se sim:
    - Aplica **umidade ao redor**.
    - Marca como salvo;


- O método `calcularRota` encontra o caminho usando **BFS**, que busca a água pela matriz;
  - Depois, **reconstrói o caminho de trás pra frente**;
  - Salva essa rota para que o método `mover` possa usar **uma posição por iteração**, e não fazer tudo de uma vez.


####  Classe `PropagacaoFogo`
Possui apenas **dois métodos**:

- Um que **espalha o fogo**, aplicando fogo nos vizinhos ortogonais de todas as árvores em chamas.
  - Se houver vento, ele só espalha na **direção definida**.
  - As células que estavam em chamas viram **queimadas**.
  - Após isso, é criada uma **nova matriz** com essas atualizações.

- Outro método verifica **se ainda há fogo na floresta**:
  - Ele percorre toda a matriz e, se encontrar fogo (`2`), retorna `true`; caso contrário, retorna `false`.

---

### Detalhamento dos Principais Métodos


> Logo abaixo, farei uma explicação mais detalhada dos métodos mais importantes das classes que envolvem a lógica da simulação.
> 

Animal

[`bfsAteAgua(...)`](https://github.com/Jeanaraga/Trabalho-1-AEDS/blob/77b4378e4a045e4b5a4229b87b93474a80dd19eb/src/Animal.cpp#L93-L125)
primero pega o tamanho da matriz, cria a fila do bfs, e define que a posicao que o animal esta foi visitada. logo apos cria um loop que enquanto a fila estiver item ela vai ocorer, dentro deste loop pega a posicao do animal cx,cy, retira da fila, verifica se a posicao do animal tem agua,se tiver retorna a posicao, apos a verificação defini as posicao ortogonais, cria um loop com todos ate acabar as posicoes, dentro deste loop calculo a posicao do vizinho com a soma do animal mas os ortogonais, faz uma verificao se esta dentro do limite da matriz, e se 





