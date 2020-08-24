
/*
    Em um programa real, utilizamos informações obtidas de forma externa do programa (entradas do usuário, dados de um arquivo, dados de um banco de dados,
    informações de uma request pela internet, etc) e portanto não sabemos previámente o valor de todas as nossas variáveis. Portanto é muito útil ter uma
    estrutura que possa decidir se uma parte do nosso código será executado ou não, se beaseando no valor de uma expressão booleana, para que possamos tratar
    todos os possíveis cenários.

    Para tal, temos no C a expressão if, que deverá ser seguida por uma expressão booleana entre () e um bloco de código. Caso a expressão entre () sejá
    verdadeira, o bloco de código é executado, caso não, o bloco será pulado. De toda forma todo código que vier depois do bloco do if é executado normalmente.

    Podemos utilizar operadores == (igual a), > (maior que), < (menor que), != (diferente de), >= (maior igual), <= (menor igual) em expressões booleanas para
    comparar valores. Também podemos usar o oprador ! para inverter o valor da expressão seguinte. Ateção! Não confunda = com ==, = é usado para atribuir um
    valor a uma variável e não tem valor booleano, já == é usado para comprar dois valores e esse sim tem valor booleano.

    Qualquer bloco if pode ser seguindo por uma expressão else, que deverá ser seguido por um bloco de código. Esse bloco é executado somente se a expressão
    no bloco if equivalente (logo anterior) for falso.

    É possivel checar várias possibilidades utilizando varios blocos if-else seguidos, veja o código abaixo para um exemplo.

    Obs.: no C não existe um tipo booleano propriamente dito, para tal é normalmente usado o tipo int, sendo 0 considerado falso e qualquer outro valor sendo
    considerado verdadeiro (geralmente se usa 1 para representar verdadeiro)

    Obs. 2: qualquer expressão que expere um bloco de código (menos funções) não necessariamente precisam de { } para marcar o bloco, no caso de se omitir as
    chaves, o bloco é considerado a primeira expressão/linha de código apos a expressão. Ex:

    if (numero < 0)
        printf("Número negativo!\n");
    
    return 0;
    // ^ return 0; não está no bloco do if
*/

int soma(int a, int b)
{
    return a + b;
}

// O operador modulo (a % b) retorna o resto da divisão de a por b (ex: 10 % 3 == 1, 8 % 2 == 0)
int eh_divisivel(int numero, int divisor)
{
    return numero % divisor == 0;
}

int flow_control()
{
    // Guardando o valor de uma soma em uma variável
    int resultado_soma = soma(21, 43);
    int input;

    printf("Entre com um número inteiro: ");
    scanf("%d", &input);

    // Declarando uma string para usar mais tarde
    char *resposta;

    if (input > resultado_soma)
    {
        // Executado caso a expressão no if acima seja verdadeira
        resposta = "maior que";
    }
    else if (input < resultado_soma)
    {
        // Executado caso a expressão no primeiro if seja falsa e o id acima seja verdadeira
        resposta = "menor que";
    }
    else
    {
        // Executado caso a expressão no if acima seja falsa
        resposta = "igual";
    }

    printf("Sua entrada foi %s a soma secreta\n", resposta);

    return 0;
}
