#include <stdio.h>

/*
    Se você estiver familiarizado com expressões booleanas, deve conhecer os operadores "e" e "ou". Em C eles são representados por
    "&&" e "||" respectivamente. Veja o código para exemplos

    Além disso, quando temos expressões e comportamentos simples, podemos utilizar o operador ternário "?". Veja abaixo para entender seu uso:
*/

char *true_ou_false(int valor)
{
    // Caso valor seja considerado verdadeiro (diferente de 0) o operador "?" retorna o que está antes de ":", caso contrário ele retorna o que
    // está depois
    return valor ? "true" : "false";
}

// Um triângulo só existe se a soma de quaisquer dois lados não for maior ou igual ao terceiro
int triangulo_existe(int ladoA, int ladoB, int ladoC)
{
    if (ladoA + ladoB >= ladoC || ladoB + ladoC >= ladoA)
    {
        // não é possível criar o triângulo
        return 0;
    }
    // não é necessário colcoar esse retorno dentro de um else pois, caso a expressão no if acima for verdadeira, o return dentro do bloco do if
    // fará com que o resto do código não seja executado, ou seja, só será retornado um valor
    return 1;
}

int triangulo_eh_equilatero(int ladoA, int ladoB, int ladoC)
{
    if (!triangulo_existe(ladoA, ladoB, ladoC))
    {
        // Nesse caso não retornamos nada, encerramos a execução do programa com código 1 (códigos diferentes de 0 são considerados erros). Uma medida
        // drástica mas que pode ser usada para aumentar a consistência do programa!
        printf("Triângulo inválido!\n");
        exit(1);
    }
    // Obs.: não podemos escrever ladoA == ladoB && ladoC pois isso será interpretado como ((ladoA == ladoB) && (ladoC)), já que o operador == só tem
    // dois parâmetros. Caso se escreva ladoA == (ladoB && ladoC) o seguinte será interpratado: o operador && retorna o que tem do lado esquerdo caso o
    // que esteja do lado direito seja considerado verdadeiro (nesse caso se ladoB diferente de 0) e a expressão será equivalente à ladoA == ladoC.
    // É NECESSÁRIO comparar o ladoA duas vezes com cada um dos outros valores
    if (ladoA == ladoB && ladoA == ladoC)
    {
        return 1;
    }

    return 0;
}

int main()
{
    // Não necessáriamente precisamos guardar o valor de retorno de uma função em uma variável, podemos usar eles diretamente em outras funções ou expressões
    printf("%s", true_ou_false(triangulo_existe(3, 4, 5)));

    printf("%s", true_ou_false(triangulo_existe(3, 10, 5)));

    printf("%s", true_ou_false(triangulo_eh_equilatero(3, 4, 5)));

    printf("%s", true_ou_false(triangulo_eh_equilatero(3, 3, 3)));

    printf("%s", true_ou_false(triangulo_eh_equilatero(7, 20, 5)));

    // Essa comparação não será executada pois o programa irá dar erro na chamada acima (exit(1), preceba o código de retorno)!
    printf("%s", true_ou_false(triangulo_eh_equilatero(1, 1, 1)));

    return 0;
}
