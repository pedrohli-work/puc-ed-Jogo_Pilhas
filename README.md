# Jogo das Pilhas Coloridas

Este é um jogo desenvolvido em C, baseado na clássica mecânica de jogo das pilhas coloridas. O objetivo do jogo é mover peças de diferentes cores entre pilhas, de modo a preencher cada pilha com peças da mesma cor. O jogo termina quando todas as pilhas estão corretamente preenchidas.

## Funcionalidades

- **Distribuição Aleatória**: As peças de diferentes cores são distribuídas aleatoriamente entre as pilhas.
- **Movimento de Peças**: O jogador pode mover uma peça de uma pilha para outra, desde que a jogada seja válida.
- **Verificação de Vencedor**: O jogo verifica automaticamente se as pilhas estão corretamente preenchidas.

## Requisitos

- **Compilador C**: O projeto foi desenvolvido em C, e pode ser compilado em qualquer compilador que suporte o padrão C99 ou superior.
- **Ambiente Windows**: Algumas funções específicas (como a mudança de cor no terminal) são dependentes de um ambiente Windows.

## Como Executar

1. **Clone o repositório**:

   ```bash
   git clone https://github.com/seu-usuario/jogo-pilhas.git
   cd jogo-pilhas
   Compilar o Projeto:
   gcc -o jogo jogo_pilhas.c
   Executar o Jogo:
   ./jogo

