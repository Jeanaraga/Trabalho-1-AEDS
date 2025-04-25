

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


**🧠 Lógica da Fuga do Animal**

- O animal se move **antes da propagação do fogo**.
- Ele tenta encontrar **o caminho mais curto até a água** (`4`) usando **Busca em Largura (BFS)**.
- Se o caminho for bloqueado pelo fogo, o animal pode tentar **até 3 reposicionamentos aleatórios** em células `0` para recalcular uma nova rota.
- Ao alcançar a água, o animal **fica salvo** e aplica **umidade nas células vizinhas**, dificultando a propagação do fogo naquela área.

---

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
