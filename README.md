# Trabalho 1 AEDS

## 📝Introdução
O trabalho se trata de uma simulação de incêndio na floresta em há um animal nesta floresta e ele precisa buscar agua dentro desta floresta pra se sentir seguro. A Floresta neste trabalho é representada por uma matrzi NxM em que dentro dela existem elementos numeruicos que representam elementos da floresta como 0(lugar vazio) 1(arvore saudavel) 2(arvore pegando fogo) 3 (arvore queimada) e 4 (agua). deve se tambem definir variaveis globais que definem a estrategia de propagação do fogo e a direção do vento. O objetivo seria desenvolver um algoritmo que espalhe o fogo pela floresta respeitando as regras da propagação; além disso seria necessaria desenvolver um algoritmo para fazer a fuga do animal a cada movimento.

#### 🛠️Tecnologias e Linguagens utilizadas

- Linguagem: C++
- Compilação via makefile
- Estrutura do Projeto
     - [Animal](https://github.com/Jeanaraga/Trabalho-1-AEDS/blob/main/src/Animal.cpp) (Toda logica que envolve o animal na simulação,como, mover o anima, calcula a rota, aplicar umidade[espalhar 1 ao redor do animal])
     - [Floresta](https://github.com/Jeanaraga/Trabalho-1-AEDS/blob/main/src/Floresta.cpp) (
     - [PropagaçãoFogo](https://github.com/Jeanaraga/Trabalho-1-AEDS/blob/main/src/PropagacaoFogo.cpp)
     - [config](https://github.com/Jeanaraga/Trabalho-1-AEDS/blob/main/src/config.hpp)

 #### 💡Como funciona
