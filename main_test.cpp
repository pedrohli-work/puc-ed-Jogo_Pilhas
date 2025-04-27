/// Grupo: PedroLi-18168500, BrunoDocs-14291983, WesleyCairesdeCosta-20083077
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <iostream>

// Número total de tubos no jogo
#define TAM 6

using namespace std;

typedef int stack_element;

#include "stack_ld.h"

typedef struct
{
    int numero_elementos;
    Stack pilha;
} Tubo;

// Protótipos das funções
void iniciar_vazias(Tubo T[]);
void distribuir(Tubo T[]);
void mudacor(int cor);
void printa_cor(int I);
void mostrar(Tubo T[]);
int validar(Tubo T[], int o, int d);
int validar_fim(Tubo T[]);
int jogada(Tubo T[]);

void iniciar_vazias(Tubo T[])
{
    for (int i = 0; i < TAM; i++)
    {
        initStack(T[i].pilha);
        T[i].numero_elementos = 0;
    }
}

/// função que distribui aleatoriamente os numeros
/// nas TAM-1 PILHAS - deixando a ULTIMA vazia
void embaralhar(stack_element *array, int n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            stack_element t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void distribuir(Tubo T[])
{
    int total_pecas = (TAM - 1) * (TAM - 1);
    stack_element *pecas = (stack_element *)malloc(total_pecas * sizeof(stack_element));
    if (pecas == NULL)
    {
        // Trate o erro de alocação aqui
        exit(EXIT_FAILURE);
    }
    int indice = 0;

    // Preenchendo o array com números/cores
    for (int cor = 1; cor < TAM; cor++)
    {
        for (int vezes = 0; vezes < TAM - 1; vezes++)
        {
            pecas[indice++] = cor;
        }
    }

    // Embaralhar as peças
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    embaralhar(pecas, total_pecas);

    // Distribuir as peças pelas pilhas, exceto a última
    indice = 0;
    for (int i = 0; i < TAM - 1; i++)
    {
        while (T[i].numero_elementos < TAM - 1 && indice < total_pecas)
        {
            push(T[i].pilha, pecas[indice++]);
            T[i].numero_elementos++;
        }
    }

    // A última pilha fica vazia
    initStack(T[TAM - 1].pilha);
    T[TAM - 1].numero_elementos = 0;
}

/// função para mudar a cor do que será impresso
void mudacor(int cor)
{
    HANDLE Saida;
    Saida = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Saida, cor);
}

/// função para imprimir o simbolo colorido - usa a função muda cor
void printa_cor(int I)
{
    int cor[5] = {9, 13, 2, 15, 6};
    /// char simbolo[5]={'*', '@', 'O', 'X', '#'};
    mudacor(cor[I - 1]);
    cout << 'O';
    /// printf("%c", '\261');
    /// printf("%c", '\251');
    /// cout<<'*';
    /// cout<<simbolo[I-1];
    /// mudacor(0);
    /// cor texto preto
    mudacor(15);
}

/// função que imprime o conteúdo das TAM PILHAS - usa PILHAS auxiliares
/// as auxiliares recebem os valores desempilhados
/// e depois retornam para as originais
void mostrar(Tubo T[])
{
    Stack aux[TAM];             // Pilhas auxiliares
    int alturaMaxima = TAM - 1; // Altura máxima dos tubos

    // Inicializar pilhas auxiliares
    for (int i = 0; i < TAM; i++)
    {
        initStack(aux[i]);
    }

    // Determinar a altura máxima de um tubo para imprimir de cima para baixo
    for (int i = 0; i < TAM; i++)
    {
        if (T[i].numero_elementos > alturaMaxima)
        {
            alturaMaxima = T[i].numero_elementos;
        }
    }

    // Desempilhar as pilhas originais para as auxiliares, exibindo os elementos
    for (int altura = alturaMaxima; altura >= 0; altura--)
    {
        for (int i = 0; i < TAM; i++)
        {
            if (altura < T[i].numero_elementos)
            {
                stack_element elemento = pop(T[i].pilha);
                printa_cor(elemento); // Função que imprime o elemento colorido
                push(aux[i], elemento);
            }
            else
            {
                std::cout << " "; // Espaço para tubos vazios ou níveis sem elementos
            }
            std::cout << "  "; // Espaçamento entre os tubos
        }
        std::cout << std::endl;
    }

    // Restaurar as pilhas originais a partir das auxiliares
    for (int i = 0; i < TAM; i++)
    {
        while (!isEmpty(aux[i]))
        {
            stack_element elemento = pop(aux[i]);
            push(T[i].pilha, elemento);
        }
    }

    // Imprimir os números dos tubos na base
    for (int i = 0; i < TAM; i++)
    {
        std::cout << "" << i + 1 << "  "; // Ajustar espaçamento conforme necessário
    }
    std::cout << std::endl;
}

/// função que valida se as escolhas de ORIGEM e DESTINO podem ser
/// executadas: se a ORIGEM tem valor e se a DESTINO já tem TAM-1
/// elementos. Aqui o Numero_elementos da struct tubo é usado
int validar(Tubo T[], int o, int d)
{
    // Verificar se os índices de origem e destino estão dentro do intervalo válido
    if (o < 0 || o >= TAM || d < 0 || d >= TAM)
    {
        return 0; // Índices inválidos
    }

    // Verificar se a pilha de origem tem pelo menos um elemento
    if (isEmpty(T[o].pilha))
    {
        return 0; // Origem vazia
    }

    // Verificar se a pilha de destino tem espaço para mais um elemento
    if (T[d].numero_elementos >= TAM - 1)
    {
        return 0; // Destino cheio
    }

    return 1; // Jogada válida
}

/// função que verifica se as pilhas estão com TAM-1 elementos e se
/// são todos iguais. Retorna UM se vai continuar o jogo - não acabou
/// e ZERO se já acertou tudo.
int validar_fim(Tubo T[])
{
    for (int i = 0; i < TAM - 1; i++)
    { // A última pilha deve estar vazia
        if (T[i].numero_elementos != TAM - 1)
        {
            return 1; // Ainda não acabou: alguma pilha não está cheia
        }

        // Verificar se todos os elementos na pilha são iguais
        if (!isEmpty(T[i].pilha))
        {
            stack_element primeiroElemento = peek(T[i].pilha);
            Stack aux;
            initStack(aux);
            int todosIguais = 1;

            while (!isEmpty(T[i].pilha))
            {
                stack_element elementoAtual = pop(T[i].pilha);
                if (elementoAtual != primeiroElemento)
                {
                    todosIguais = 0;
                }
                push(aux, elementoAtual);
            }

            // Restaurar a pilha original
            while (!isEmpty(aux))
            {
                push(T[i].pilha, pop(aux));
            }

            if (!todosIguais)
            {
                return 1; // Ainda não acabou: nem todos os elementos são iguais
            }
        }
    }

    return 0; // Jogo acabou: todas as pilhas estão corretas
}

/// função que executa a JOGADA;
/// faz a leitura da ORIGEM e do DESTINO(repete leitura se diferente de -1(parar)
/// e fora do intervalo 1 a 6; chama a função validar(..)
/// que verifica se a jogada é valida
/// Se não for, repete a leitura de ORIGEM e DESTINO
/// Se a jogada for válida - desempilha elemento da PILHA Origem
/// e empilha na PILHA Destino.
/// E incrementa UMA unidade, usando o campo número_elementos da struct TUBO,
/// relativa à pilha DESTINO e, DECREMENTA uma unidade da ORIGEM
/// E, no final, chama a função para validar_fim(..)
/// e retorna o mesmo valor que retornou da função validar_fim(..)
int jogada(Tubo T[])
{
    int origem, destino, resultado;

    do
    {
        printf("Escolha o TUBO ORIGEM (1 a %d, -1 para parar): ", TAM);
        scanf("%d", &origem);
        if (origem == -1)
            return 1; // Encerrar a jogada

        printf("Escolha o TUBO DESTINO (1 a %d, -1 para parar): ", TAM);
        scanf("%d", &destino);
        if (destino == -1)
            return 1; // Encerrar a jogada

        // Ajustar índices para base 0
        origem--;
        destino--;

    } while (!validar(T, origem, destino)); // Repetir se a jogada não for válida

    // Executar a jogada
    stack_element elemento = pop(T[origem].pilha);
    push(T[destino].pilha, elemento);
    T[origem].numero_elementos--;
    T[destino].numero_elementos++;

    // Verificar se o jogo terminou
    resultado = validar_fim(T);
    return resultado;
}

int main()
{
    Tubo T[TAM];
    int repetir = 1, retorno;

    do
    {
        iniciar_vazias(T);
        distribuir(T);
        mostrar(T);

        do
        {
            /// 1: continuar jogada, 0: acabou jogo
            retorno = jogada(T);
            mostrar(T);
            if (retorno == 0)
                break;
        }

        while (retorno);
        mostrar(T);

        cout << "\n P A R A B E N S ! ! ! !";
        cout << "\n Jogar Novamente? 1 (sim) ou 0 (nao): ";
        cin >> repetir;
    }

    while (repetir);
    cout << "Fim de JOGO!";
    return 0;
}