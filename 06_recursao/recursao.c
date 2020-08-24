#include <stdlib.h>
#include <stdio.h>

/*
    Recursão é o nome que damos quando a definição de algo faz referência a ela mesma, como por exemplo, o nésimo número da sequência de
    Fibonacci é a soma dos dois números anteriores na sequência, exceto pelo primeiro e pelo segundo, que por definição são 0 e 1. Como podemos
    ver a definição é recursiva, exceto em dois casos (chamados de break condition), sem esses dois casos não recursivos, a definição da
    sequência de Fibonacci não teria muito sentido.

    Em programação, quando falamos de recursão geralmente estamos nos referindo a uma estrutura que tem referência a uma estrutura do mesmo tipo
    (como nodos de uma árvore ou de uma lista encadeada) ou, mais comumente, quando uma função faz uma chamada a si mesma (geralmente com argumentos
    diferentes). E, como na sequência de Fibonacci, toda boa função recursiva deve ter pelo menos uma break condition não recursiva, para que
    não fique computando infinitamente. Veja os exemplos abaixo:
*/

// Essa função imprime os números entre "inicial" e "final", com "inicial" inclusivo e "final" exclusivo. Perceba que recursão nesse caso é bem parecido
// com um loop, e muitas vezes realmente é, porém existem certos casos onde é muito mais fácil implementar algo usando recursão se comparado a um loop,
// como nos algorítimos de quicksort, mergesort ou de busca em árvores e grafos
void funcao(int inicial, int limite)
{
    // break condition
    if (inicial >= limite)
        return;

    printf("%d\n", inicial);
    funcao(inicial + 1, limite);
}

// A seguir dois exemplos canônicos de recursão: fatorial e a sequência de Fibonacci
int fatorial(int n)
{
    // Esse retorno faz sentido? O que você acha que deferia aconvtecer se essa função receber um número negativo?
    if (n < 0)
        return 0;

    // break condition
    if (n == 0)
        return 1;

    return n * fatorial(n - 1);
}

int fibonacci(int n)
{
    // multiplas break conditions
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Aqui está uma implementação da sequência de Fibonacci utilizando um for. Bem menos elegante, não? Porém tenha em mente isso: é muito mais
// custuso para um computador utilizar recursão do que utilizar um loop (por conta do cursto de alocação das variáveis e adição de chamada no stack)
// portanto você deve balancear velocidade com elegância/facilidade de leitura quando estiver escrevendo uma função dependendo do que é mais
// improtante para você naquele momento
int fibonacci_for(int a)
{
    int n = 0, nMenos1 = 1, nMenos2 = 0;

    if (a == 0)
        return 0;

    if (a == 1)
        return 1;

    int i;
    for (i = 0; i < a - 2; i++)
    {
        n = nMenos1 + nMenos2;
        nMenos2 = nMenos1;
        nMenos1 = n;
    }

    return n;
}

int main()
{
    funcao(3, 7);

    // Perceba a diferença de tempo para computar o mesmo valor por métodos diferentes
    printf("%d\n", fibonacci_for(1000));
    printf("%d\n", fibonacci(1000));

    return 0;
}