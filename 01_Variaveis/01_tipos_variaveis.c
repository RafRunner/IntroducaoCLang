#include <stdio.h>

/*
    Variáveis em C são identificadores nomeados e com tipo, que podem armazenar diferentes valores (dentro do mesmo tipo) e seu valor pode ou não mudar.

    Pense em variáveis como caixais, elas tem um rótulo (nome) e um tipo. Você pode guardar algo nessa caixa, ver o se valor e também colocar algo novo (mudar
    seu valor).

    Ao se criar (declarar) uma variável, não podemos determianr qual seu valor inicial (uma variável int não necessariamente será iniciada com 0), portanto
    é bom atribuir um valor inicial a uma variável.
    
    Cada variável existe apenas dentro da função/bloco onde ela foi variável. Inicialmente a única função que temos aqui é a main, a função chamada
    automaticamente ao executarmos o programa. Um bloco é qualquer segmento de código envolto por { } (incluindo funções). Essas são variáveis locais.
    Além disso existem variáveis globais, são as declaradas fora de uma função, elas existem em todo o arquivo atual. Atualmente é considerado indesejável
    a utilização de variávels globais. Por enquanto pense em um função como um bloco de código externo que pode ser executado (chamado) com certos parâmetros
    (os valores entre "()") e que pode ou não retornar um valor.

    No C variáveis locais são criadas (o espaço necessário para que seu conteúdo seja armanezado é alocado) ao aparecerem numa função/bloco e elas são
    destruidas (seu espaço na memória desaloacas) no fim da função/bloco. Mais para frente iremos ver como é possível fazer com que variáveis durem
    além de uma função sem utilizar variáveis globais.

    Para ver o valor de uma variável, podemos utilizar a função printf, que é declarada em stdio.h (Por isso o "#include <stdio.h>" no início do arquivo),
    bastando colcoar um formatador (%d, %f, veja exemplos abaixo) na string que será impressa (string é o valor entre parênteses) e a variável após a string
    separando os valores por vírgula. O "\n" no fim da string é um caractere especial para imprimir uma nova linha. Veja mais sobre isso pesquisando por
    "format specifiers" e "scape characteres" no C.

    Para ler uma variável vamos usar o scanf, função parecida com printf que vem do mesmo header (arquivo .h). Veja abaixo como usar, só nãos e esqeuça de
    colocar "&" antes da variável para funcionar! Vamos ver o depois porque.
*/

int main()
{
    // Tipos numpericos:
    int inteiro;
    inteiro = 32;

    float decimal;
    decimal = 10.2f;
    double decimal_mais_preciso = 2.3;
    // ^ É possivel atribuir valor à varivel junto com a declaração

    // Tipos de caracteres:
    char caractere = 'c';
    // Perceba que para caractere se usa aspas simples, para string duplas
    char *string = "Isso é uma string";

    // Formatadores para imprimir (e para usar com scanf e outras funções também)
    printf("%d\n", inteiro);
    printf("%f\n", decimal);
    printf("%lf\n", decimal_mais_preciso);
    printf("%c\n", caractere);
    printf("%s\n", string);

    // Mudando o valor do inteiro lendo entrada do usuário
    printf("\nEntre com um novo valor para a variável inteiro: ");
    scanf("%d", &inteiro);
    printf("\nVocê entrou com: %d\n", inteiro);

    return 0;
}
