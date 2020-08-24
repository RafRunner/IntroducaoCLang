#include <stdio.h>
#include <locale.h>

/*
    Em casos onde temos uma variável ou expressão e queremos ter vários possíveis comportamentos dependendo do seu valor, podemos utilizar
    uma expressão chamada switch para facilitar a leitura e melhorar a performance no lugar de utilizar vários if-else.

    Essa expressão é seguida pela variável ou expressão entre ( ) e um bloco de código especial entre { }. Nesse bloco escrevemos varios case
    onde descrevemos blocos que sejá executados para cada caso (esse é o único local onde não utilizamos { } para marcar um bloco, mas sim ":" para
    iniciar e "break;" prar finalizar).

    No fim do bloco do switch podemos colocar opcionalemente o caso especial "default". Ele é executado caso a variável/espressão do switch não bata
    com nenhum dos outros casos.
*/

int main()
{
    setlocale(LC_ALL, "Portuguese");

    float preco;

    printf("Bem vindo à sanduicheria CLang! O que gostaria de pedir?\n");
    printf("1- Sanduiche - R$8,00\n");
    printf("2- Coxinha - R$3,50\n");
    printf("3- Coca-Cola - R$3,00\n");
    printf("4- Suco natural - R$3,00\n");
    printf("5- Pastel - R$5,00\n");

    int item_escolhido;
    scanf("%d", &item_escolhido);

    switch (item_escolhido)
    {
    // Checa se a variável "item_escolhido" é igual a 1 (como em "item_escolhido == 1")
    case 1:
        preco = 8.0f;
        break;

    case 2:
        preco = 3.5f;
        break;

    // Como Coca-Cola e Suco natural tem o mesmo preço (mesmo comportamento), podemos juntar os dois blocos dessa forma:
    case 3:
    case 4:
        preco = 3.0f;
        break;

    default:
        preco = 5.0f;
    }

    // %.2f formata o número real para ser impresso com somente duas casas decimais
    printf("Preço do seu pedido: %.2f\n", preco);

    return 0;
}
