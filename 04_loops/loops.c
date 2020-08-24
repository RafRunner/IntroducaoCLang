#include <stdio.h>

/*
    Loops são partes importantes de qualquer linguágem de programação. Eles permitem executar repetidamente um bloco de código uma
    determinada quantidade de vezes ou enquanto uma expressão for verdadeira. Muito útei para evitar repetição de código ou para quando
    não sabemos de antemão (em tempo de compilação) quantas vezes um determinado treixo de código deve ser executado
*/

int main()
{
    int i = 0;

    // Equanto a expressao do while for verdadeira o código no bloco equivalente executado repetidamente
    while (i < 10)
    {
        printf("Valor atual de i: %d\n", i);
        // Se não atualizarmos o valor de i, o que acha que iria acontecer?
        i = i + 1;
    }

    i = 0;

    // O "do while" é bem parecido com o while, mas ele checa se a expressão é verdadeira depois de executar o bloco
    do
    {
        printf("Valor atual de i: %d\n", i);
        i = i + 1;
    } while (i < 10);

    // O loop for consite de 3 expressões:
    // A primeira é executada somente uma vez ao iniciar o loop, geralemnte é usado para settar o valor inicial da variável de loop
    // A segunda é semelhante a expressão do while: é avaliada no inicio de cada ciclo do loop, caso seja falsa o loop é interrompido
    // A terceira é cahamada toda vez ao fim do loop, é geralemnte usada para incrementar a variével do loop
    for (i = 0; i < 50; i++)
    {
        // i++ é uma maneira mais rápida de escrever i = i + 1;

        // Uma variavál declarada declarada dentro de um bloco (qualquer que seja) só existe dentro dele, podendo existir variáveis de mesmo nome em blocos diferentes
        int j;

        // É possivel aninhar quantos loops quiser
        for (j = 0; j < 50; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
