#include <stdio.h>
#include <stdlib.h>

/*
    Se você entendeu a parte anterior de ponteiros, essa parte vai ser fácil! Um vetor dinânico nada mais é que um ponteiro alocado para mais de uma variável!
    Eles se comportam de forma muito semelhante a vetores, veja abaixo:
*/

// Declarando as assinaturas das funções que vamos usar abaixo
void imprime_vetor(int *vetor, int tamanho);
int *cria_vetor_aleatorio(int tamanho);

int main()
{
    // Multiplicamos "sizeof(int)" por 10 para criar um vetor de 10 posições, aqui sim podemos usar uma variável de valor desconhecido em tempo de compilação,
    // pois a memória só será alocada quando a função for executada e o valor da variável for conhecida
    int tamanho = 10;
    int *vetor = malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = i * i;
    }

    imprime_vetor(vetor, tamanho);

    // Diferentemente de vetores estáticos, temos que liberar os dinâmicos!
    free(vetor);

    // Reutilizando o ponteiro "vetor" para outro vetor
    vetor = cria_vetor_aleatorio(tamanho);
    imprime_vetor(vetor, tamanho);

    // Precisamos libearar "vetor" novamente pois ele recebeu outro ponteiro alocado em "cria_vetor_aleatorio"
    free(vetor);

    return 0;
}

// Podemos passra um vetor como um argumento para uma função e também retorná-los. Só é preciso ficar atento de que precisamos passar também o tamanho, já que
// ele não pode ser inferido!
void imprime_vetor(int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int *cria_vetor_aleatorio(int tamanho)
{
    // "calloc" é semelhante à "malloc", porém recebe dois argumentos, o número de elementos a serem alocados e o tamanho do tipo a ser alocado. Ele também já preenche
    // o vetor alocado com 0s, o que pode ser útil em certas situações
    int *vetor = calloc(tamanho, sizeof(tamanho));

    for (int i = 0; i < tamanho; i++)
    {
        // Número pseudo aleatório entre 0 e 10000
        vetor[i] = rand() % 1000;
    }

    return vetor;
}

/* 
    Nessa lição não fizemos nenhum tipo de check (verificar se foi passado um tamanho negativo para criar o vetor, verificar se alocação retornou NULL) o que pode
    ser ok para peguenos projetos e códigos educacionais (especialmente por deixar o código mais limpo) mas não é a melhor prática. Tente reescrever o código dessa
    aula fazendo todos os check necessários!
*/
