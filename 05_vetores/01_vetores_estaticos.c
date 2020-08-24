#include <stdio.h>

/*
    Vetores (arrays) são uma forma muito útil de armazenar mais de um valor utilizando uma única variável. Podemos declarar vetores de qualquer tipo
    disponível de tamanho natural maior que 0 n, e serão criados como que n variáveis daquele tipo, sendo acessíveis pelo identificador usado na
    declaração do vetor e um índice tambem natural. Importante: em C (e na maioria das linguagens de programação) o vetores começam no índice 0,
    ou seja, o primeiro elemento está no índice 0 e o último no índice n - 1.

    Ao criar um vetor, precisamos iniciar seus valores. Um vetor de int não será iniciado com 0s, pois não sabemos o que tem inicialmente na memória
    ao declarar o vetor.
    
    Tenha em mente que, para vetores estáticos, devemos saber em tempo de compilação o tamanho desse vetor (seu tamanho deve ser um inteiro
    literal, não pode ser uma variável), isso porque, como dito antes, o C rezerva na memória o espaço de todas as variáveis de uma função
    assim que ela é chamada, como ele irá saber o tanto de memória para alocar se o tamanho do vetor for uma variável ainda não definida?

    Pra criar um vetor com um tamanho só conhecido em tempo de execução (como o tamanho informado por uma variável) veja o próximo item
    nessa parte.
*/

int main()
{
    // Decalrando um vetor com 10 posições
    int numeros[10];
    int i;

    // Preenchendo o vetor com os números de 1 até 10
    for (i = 0; i < 10; i++)
    {
        // Atribui ao iésimo número no vetor
        numeros[i] = i + 1;
    }

    // Percorre o vetor imprimindo somente os números não divisíveis por 3
    for (i = 0; i < 10; i++)
    {
        // Obtem o iésimo número no vetor
        int numero_atual = numeros[i];

        // Checa se o número não é divisével por 3
        if (numero_atual % 3 != 0)
        {
            printf("O elemento na posicao %d eh %d\n", i, numero_atual);
        }
    }

    // Podemos declarar o vetor e seus conteúdo diretamente dessa forma, nesse caso podemos omitir seu tamanho (ele é inferido)
    // porém ele ainda é constante!
    double decimais[] = {0.3, -0.5, 0.2, 1.2, 8.4, 9.2, -10.3};
    int tamanho = 7;

    double soma;

    for (i = 0; i < tamanho; i++)
    {
        // Acumulando os valores do vetor numa variável soma. "a += b" é equivalente a "a = a + b". Também existe "*=". "/=" e "-="
        soma += decimais[i];
    }

    double media = soma / tamanho;

    printf("A soma dos elementos do vetor de decimais eh %d\n", soma);
    printf("A média dos elementos do vetor de decimais eh %d\n", media);

    return 0;
}
