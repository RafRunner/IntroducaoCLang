#include <stdio.h>
#include <math.h>

/*
    Em C, boa partes dos tipos primitivos são números, e suprotam operações aritiméticas simples como soma(+), subtração(-), multiplicação(*)
    e divisão(/). O C respeita a ordem padrão de operações, e você pode usar parênteses para alternar a ordem padrão.

    Caso você queira usar operações mais complexas como potência, raiz quadrada, seno, cosseno, elas estão declaradas no header math.h incluido acima.
    Como isso entra na ordem das operações? Simples, funções são excutadas antes de qualquer outra operação, e o que está em seus arguemntos (entre "()")
    é executado antes ainda para que a função possa ser chamada. Veja os exemplos abaixo.

    Também é possível converter tipos primitivos usando uma operação chamada cast, ela é feita colocando o tipo para o qual você quer que o valor seja
    convertido entre parênteses antes de uma expressão ou valor. Veja abaixo para exemplos.
*/

int main()
{
    int operacao1 = 2 + 4 * 3;   // 14
    int operacao2 = (2 + 4) * 3; // 18

    printf("operacao1: %d\n", operacao1);
    printf("operacao2: %d\n", operacao2);

    // Perceba que sqrt (raiz quadrada) retorna double e aceita double, porém a conversão é feita automaticamente, sem precisar de cast
    // porém, na dúvida, sempre utiliza os tipos certos ou cast
    int raiz = sqrt(12 * 12);

    printf("raiz: %d\n", raiz);

    // Divisão de dois ints pode dar um float
    float divisao = (float)operacao1 / operacao2;

    printf("divisao: %f\n", divisao);

    // Utilizando cast para int
    int parte_inteira = (int)divisao;

    printf("parte_inteira: %d\n", parte_inteira);

    // Converter um int para char resultará em um caractere equivalente. Porém para qual caractere por depender de muitas coisas, como o encoding do arquivo
    // esse arquivo está em utf-8
    char caractere = (char)(int)(pow(2, 7) - (-14));

    printf("a: %c\n", caractere);

    return 0;
}
