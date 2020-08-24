#include <stdio.h>
#include <stdlib.h>

/*
    Matrizes não são muito diferentes de vetores, em programação é muito comum pensar nessas como vetores de vetores. Se vetores são indexáveis em
    uma dimensão, matrizes são indexáveis em duas (ou mais, mas aqui vamos falar de matrizes bidimensionais). Ao acessar o primeiro índice (matriz[i])
    estamos acessando uma linha (a linha "i"), que é um vetor. Ao acessar o segundo índice (matriz[i][j]) estamos acessando a coluna "j" da linha "i"
    que pode ser considerada uma "célula", que em si realmente é um valor.

    Matrizes são muito úteis em álgebra linear, computação gráfica e inteligência artificial. Pesquise alguns usos de matrizes em computação e tente
    implementar alguns simples!
*/

// Difinindo uma struct para matriz para facilitar (não ser necessário passar 3 argumentos (valores, linhas e colunas) e podermos devovler apenas um
// valor em funções que retornam uma matriz)
typedef struct Matriz
{
    unsigned int linhas;
    unsigned int colunas;
    double **valores;
} Matriz;

Matriz *aloca_matriz(unsigned int linhas, unsigned int colunas)
{
    Matriz *matriz = malloc(sizeof(Matriz));

    // Checando se a alocação foi bem sucedida
    if (matriz == NULL)
        return NULL;

    double **valores = calloc(linhas, sizeof(double *));

    // Se a alocação da matriz foi bem sucedida mais a dos valores não, temos que liberar a matriz
    if (valores == NULL)
    {
        free(matriz);
        return NULL;
    }

    for (int i = 0; i < linhas; i++)
    {
        valores[i] = calloc(colunas, sizeof(double));

        // Se a alocação da matriz e dos valores foi bem sucedida mais a de uma das linhas não, temos que liberar todas as linhas anteriores,
        // os valores e a matriz
        if (valores[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(valores[j]);

            free(valores);
            free(matriz);
            return NULL;
        }
    }

    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->valores = valores;

    return matriz;
}

// Multiplicação de uma matriz por uma escalar resulta em uma matriz com cada elemento multiplicado pelo escalar
// Nessa funçao, como não vamos ou queremos mudar a matriz original, recebemos ela por valor (não usando um ponteiro)
Matriz *multiplicacao_escalar(Matriz matriz, double escalar)
{
    // Criando nova matriz para não sobreescrever a original
    Matriz *resultado = aloca_matriz(matriz.linhas, matriz.colunas);

    if (resultado == NULL)
        return NULL;

    for (unsigned int i = 0; i < matriz.linhas; i++)
    {
        for (unsigned int j = 0; j < matriz.colunas; j++)
        {
            // Armazenando a multiplicação na matriz resultado
            resultado->valores[i][j] = matriz.valores[i][j] * escalar;
        }
    }

    return resultado;
}

// Soma de duas matrizes. Elas precisam ser do mesmo tamanho
// Nessa funçao, como não vamos ou queremos mudar as matrizes originais, recebemos elas por valor (não usando um ponteiro)
Matriz *soma_matriz(Matriz matrizA, Matriz matrizB)
{
    if (matrizA.linhas != matrizB.linhas || matrizA.colunas != matrizB.colunas)
        return NULL;

    // Criando nova matriz para não sobreescrever as originais
    Matriz *resultado = aloca_matriz(matrizA.linhas, matrizA.colunas);

    if (resultado == NULL)
        return NULL;

    for (unsigned int i = 0; i < matrizA.linhas; i++)
    {
        for (unsigned int j = 0; j < matrizA.colunas; j++)
        {
            // Armazenando a soma na matriz resultado
            resultado->valores[i][j] = matrizA.valores[i][j] + matrizB.valores[i][j];
        }
    }

    return resultado;
}

// Multiplicação de duas matrizes. Pesquise pela definição pois ela é um pouco extensa!
// Nessa funçao, como não vamos ou queremos mudar as matrizes originais, recebemos elas por valor (não usando um ponteiro)
Matriz *multiplica_matriz(Matriz matrizA, Matriz matrizB)
{
    // Se matriz A é n x m, matriz B deve ser m x n
    if (matrizA.linhas != matrizB.colunas || matrizA.colunas != matrizB.linhas)
        return NULL;

    // Criando nova matriz para não sobreescrever as originais
    Matriz *resultado = aloca_matriz(matrizA.linhas, matrizB.colunas);

    if (resultado == NULL)
        return NULL;

    for (unsigned int i = 0; i < resultado->linhas; i++)
    {
        for (unsigned int j = 0; j < resultado->colunas; j++)
        {
            double resultado_elemento = 0.0;

            // Veja a definição de multiplicação de matrizes para entender o cálculo
            for (unsigned k = 0; k < matrizB.linhas; k++)
                resultado_elemento += matrizA.valores[i][k] * matrizB.valores[k][j];

            resultado->valores[i][j] = resultado_elemento;
        }
    }

    return resultado;
}

// Simples função para imprimir os valores da matriz
void imprime_matriz(Matriz matriz)
{
    for (unsigned int i = 0; i < matriz.linhas; i++)
    {
        for (unsigned int j = 0; j < matriz.colunas; j++)
        {
            printf("%.2lf ", matriz.valores[i][j]);
        }
        printf("\n");
    }
}

// Como Matriz é uma struct compelxa, temos que liberar seus elementos
void libera_matriz(Matriz *matriz)
{
    // Liberando as colunas
    for (unsigned int i = 0; i < matriz->linhas; i++)
        free(matriz->valores[i]);

    // Liberando os valores
    free(matriz->valores);
    free(matriz);
    matriz = NULL;
}

int main()
{
    // Para simplificar, não vamos checar se as alocações foram bem sucedidas. Fica como exercício!
    Matriz *matriz1 = aloca_matriz(3, 4);

    for (unsigned int i = 0; i < matriz1->linhas; i++)
    {
        for (unsigned int j = 0; j < matriz1->colunas; j++)
        {
            matriz1->valores[i][j] = i * matriz1->linhas + i + j;
        }
    }

    printf("Matriz original:\n");
    imprime_matriz(*matriz1);

    Matriz *matriz2 = multiplicacao_escalar(*matriz1, 1.32);

    printf("\nMatriz multiplicada por 1.32:\n");
    imprime_matriz(*matriz2);

    Matriz *matriz3 = soma_matriz(*matriz1, *matriz2);

    printf("\nMatriz original somada com o resultado da multiplicacao:\n");
    imprime_matriz(*matriz3);

    libera_matriz(matriz1);
    libera_matriz(matriz2);
    libera_matriz(matriz3);

    // Reutilizando os ponteiros, se certifique que todos estejam liberados ao fazer isso!
    matriz1 = aloca_matriz(2, 3);
    matriz2 = aloca_matriz(3, 2);

    matriz1->valores[0][0] = 2.0;
    matriz1->valores[0][1] = 3.0;
    matriz1->valores[0][2] = 1.0;
    matriz1->valores[1][0] = -1.0;
    matriz1->valores[1][1] = 0.0;
    matriz1->valores[1][2] = 2.0;

    matriz2->valores[0][0] = 1.0;
    matriz2->valores[0][1] = -2.0;
    matriz2->valores[1][0] = 0.0;
    matriz2->valores[1][1] = 5.0;
    matriz2->valores[2][0] = 4.0;
    matriz2->valores[2][1] = 1.0;

    matriz3 = multiplica_matriz(*matriz1, *matriz2);

    printf("\n");
    imprime_matriz(*matriz1);
    printf("x\n");
    imprime_matriz(*matriz2);
    printf("=\n");
    imprime_matriz(*matriz3);

    libera_matriz(matriz1);
    libera_matriz(matriz2);
    libera_matriz(matriz3);

    return 0;
}
