#include <stdio.h>

/*
    Funções são uma maneira útil de reutilizar código que possui uma lógica e/ou função útil para que não precisemos escrever o mesmo código
    duas vezes. Elas são declaradas por basicamente 4 partes: o tipo de retorno (void caso a função não retorne nada), o nome da função (que
    deve ser único), a lista de parâmetros com tipo e nome (que são tratados como variáveis locais da função, mas seus valores devem ser
    informados pelo código que a chamar) e o corpo da função (o código que será executato quando a função é chamada).

    Quando uma função atingue um comando de return, sua execução é interrompida e ela retorna o valor da expressão após o return. Caso a função
    retorne void (nada) ainda é possível usar o return, basta utilizá-lo sem nenhuma expressão na frente (return;). Funções com tipo de retorno
    diferente de void sempre devem utilizar o return com um valor válido para qualquer execução possível da função. Perceba que a função main
    (que retorna int) sempre deve retornar 0 no seu fim;
*/

// Função sem retorno e sem parâmetro (apenas efeito colateral)
void ola()
{
    printf("Olá, mundo!\n");
}

// Função sem retorno e com parâmetro do tipo char* (equivalente à string)
void ola_nome(char *nome)
{
    printf("Olá, %s!\n", nome);
}

// Função que retorna int e tem dois parâmetros do tipo int
int soma(int a, int b)
{
    // Uma variável local que só existe dentro dessa função. Se ela for chamada mais de uma vez, essa variável será criada novamente, ou seja,
    // chamar uma função várias vezes não deve ter resultados diferentes, pois suas variáveis locais não interagem umas com as outras
    int resultado = a + b;

    return resultado;
}

int main()
{
    // Chamando uma função sem retorno e sem parâmetro
    ola();

    // Variável string (char[] é equivalente à char*, e deve ser usado para variáveis locais que serão inicializadas posteriormente)
    char nome[100];
    printf("Entre com seu nome: ");
    scanf("%s", nome);

    // Chamando uma função sem retorno e com parâmetro
    ola_nome(nome);

    int a, b;
    printf("Entre com dois números: ");
    scanf("%d", &a);
    scanf("%d", &b);

    // Chamando uma função com retorno e com parâmetro. Seu retorno está sendo guardado em uma variável para ser usado mais tarde
    int resultado_soma = soma(a, b);

    printf("Resultado da soma: %d\n", resultado_soma);

    return 0;
}
