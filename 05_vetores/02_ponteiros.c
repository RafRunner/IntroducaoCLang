#include <stdio.h>
#include <stdlib.h>

/*
    Antes de falar de vetores dinâmicos, precisamos falar de ponteiros. Não fique com medo! Nós já usamos ponteiros em strings e na função scanf,
    ponteiro nada mais é que um tipo especial de variável que guarda um endereço de memória. Podemos usar esse endereço para ler ou modificar o valor
    de uma variável. Veja o exemplo:
*/

void ponteiro_variavel_local()
{
    int a = 2;
    // Utilizamos "*" para marcar que "p" é um ponteiro e "&" para obter o endereço de memória de a
    int *p = &a;
    // Tenha em mente que, como a é uma variável local, assim que a execução dessa funão terminar, o endereço reservado para a variável a (guardado
    // na variável p) pode ser usado para qualquer outra coisa, e seu valor vai ser provavelmente sobreescrito

    printf("Endereco apontado por p: %p\n", p);
    // Utilizamos "*" antes de "p" para ler o valor que está no endereço apontado por "p"
    printf("Valor apontado por p: %d\n", *p);

    // Aqui alteramos a variável apontada por "p" (a variável "a") indiretamente. Perceba o uso de "*" antes do "p"!
    *p = 42;
    // p = 42 iria alterar a enredeço de memória para qual p está apontando (enredeço esse provavelmente usado por outro processo do sistema operacional,
    // tentar ler ou escrever em um endereço arbitrário assim tem grande chances de resultar em um erro!)

    printf("Valor de a: %d", a);
}

/*
    Um ponteiro para int (int*) não é fundamentalemnte diferentede um ponteiro para char (char*), o tipo é apenas uma forma de informar ao compilador
    quantos bytes de memória deverão ser usados para resgatar ou alterar o valor apontado pelo ponteiro. Podemos criar ponteiros para todos os tipos do C
    e tipos que nós definirmos também.

    Ok, nesse momento você pode estar se perguntando a utilidade de ponteiros, porque não só usamos variáveis normais? Bem, a utilidade deles está no fato
    de que, em C, as variáveis são passados por valor (isso significa que, ao chamar uma função "f" passando uma variável "a", apenar o valor desse variável
    será passado para a função, não sua referência, ou seja, se modificarmos o valor de "a" dentro de "f", o valor de "a" original (externo) não será modificado).
    Se quisermos modificar o valor de uma variável dentro de uma função devemos passar seu endereço no memória (um ponteiro que aponta para ela!) para que a
    função possa modificar seu valor modificando aquele endereço de memória. Veja abaixo:
*/

void passando_por_valor(int a)
{
    a = a + 10;
}

void passando_por_referencia(int *a)
{
    *a = *a + 10;
}

void valor_vs_referencia()
{
    int a = 10;
    printf("Valor de a: %d\n", a);

    passando_por_valor(10);
    printf("Valor de a: %d\n", a);

    int *p = &a;
    // Poderiamos ter chamado diretamente "passando_por_referencia(&a);"
    passando_por_referencia(p);
    printf("Valor de a: %d\n", a);
}

/*
    Além disso, outra utilizada de ponteiros é fazer com que um valor exista além de uma função. Lembra de que C desaloca o espaço de memória de 
    todas as variáveis no fim de uma função? Se quisermos que isso não aconteça temos que alocar manualmente algum espaço de memória. Para tal vamos
    utiliar a função "malloc" que está no header stdlib.h. Essa função aloca um espaço do tamanho passado como parâmetro para ela. Para saber o tamanho
    que é necessário alocar, usamos o operador "sizeof". A função "malloc" devolve um ponteiro para o endereço alocado.

    Tome cuidado, funções que alocam ou realocam memória podem falhar (afinal, o computador pode estar sem memória) então é uma boa prática checar se o
    ponteiro retornado por eles é NULL (o ponteiro NULL é um ponteiro especial que significa um ponteiro vazio e, quando retornado de uma função, geralmente
    significa que a operação falhou).

    Um detalhe muito importante! Ao usar malloc estamos falando para o compilador não liberar aquela memória, e é nossa responsabilidade liberá-la quando
    não vamos mais a utilizar. Se não fizermos isso, no programa irá gastar progressivamente mais memória enquanto estiver rodando até travar! Isso é chamado
    de memory leak. Para liberar um ponteiro alocado manualemnte usamos a função "free".
*/

double *reservando_memoria()
{
    // "sizeof(double)" irá retornar o tamanho necessário para alocar uma variável "double".
    double *p = malloc(sizeof(double));

    // Checando se malloc foi bem sucedido
    if (p == NULL)
    {
        printf("Acabou a memoria!\n");
        exit(1);
    }

    // Iniciando com 0
    *p = 0.0;

    return p;
}

void teste_malloc()
{
    double *double_reservado = reservando_memoria();
    printf("Valor double_reservado: %lf\n", *double_reservado);

    // Podemos utilizar o ponteiro reservador como uma variável normal, mesmo tendo sido criado em outra fução
    *double_reservado = 23.4;
    printf("Valor double_reservado: %lf\n", *double_reservado);

    // Como não vamos mais usar o valor, liberamos para evitar memory leak
    free(double_reservado);
    // É uma boa prática settar os ponteiros como NULL após liberá-los, porém nem sempre necessário quando se sabe que o ponteiro não será mais usado
    double_reservado = NULL;
}

int main()
{
    valor_vs_referencia();
    teste_malloc();

    return 0;
}
