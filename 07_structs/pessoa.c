#include <stdlib.h>
#include <stdio.h>

/*
    Para coisas simples, os tipos primitivos do C podem bastar, mas e se quisermos representar estruturas mais complexas? Ou então poder passar
    muitas informações relacionadas utilizando somente uma variável? Para isso existem structs. Structs são tipos criados pelo usuário/bibliotecas
    que carregagam dentro delas vários campos de tipos diferentes (podendo também ser outras structs!). Veja acabixo o exemplo de uma struct que
    representa algumas informações de uma pessoa
*/

// definindo a struct "Pessoa", essa primeira linha poderia ser somente "typedef struct" com "Pessoa" apenas no final, mas é comum colocar nos dois
// lugares para dar clareza
typedef struct Pessoa
{
    // Vetores e outras structs que fazem parte de uma struct devem ser referidas por meio de ponteiros
    char *nome;

    // "unisigned" significa somente que a variável não tem sinal (>= 0). "short" é um tipo parecido com int, mas com alcanse menor (o maior número
    // que pode ser guardado é menor)
    unsigned short idade;

    // infelizmente não existe "unisigned float"
    float peso;
} Pessoa;

// É padrão criar uma função que cria uma struct (aloca memória, e devolve um ponteiro) usando seus campos
Pessoa *cria_pessoa(char *nome, unsigned short idade, float peso)
{
    // Podemos usar "sizeof" para pegar o tamanho de "Pessoa"
    Pessoa *pessoa = malloc(sizeof(Pessoa));

    // Para acessar os campos de um ponteiro para uma struct, usamos "->"
    pessoa->nome = nome;
    pessoa->idade = idade;
    pessoa->peso = peso;

    return pessoa;
}

void imprime_pessoa(Pessoa pessoa)
{
    // Para acessar os campos de uma struct (sem ser ponteiro), usamos ".". Essa forma é mais comum para acecar campos de estruturas em outras linguagens
    printf("Nome: %s\n", pessoa.nome);
    printf("Idade: %d\n", pessoa.idade);
    printf("Peso: %.3f\n", pessoa.peso);
}

// Como "Pessoa" é uma struct complexa (possui campos que são ponteiros) temos que liberar todos os campos que são ponteiros antes de libeara o ponteiro
// para a struct em si ou teremos memory leak
void free_pessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    free(pessoa);
}

int main()
{
    // Como será uma string entrada pelo usuário, temos que pré-alocar seu espaço (no caso assumimos que terá no máximo 128 caracteres)
    char *nome = calloc(128, sizeof(char));

    unsigned short idade;
    float peso;

    printf("Entre com seu nome: ");
    scanf("%s", nome);
    printf("Entre com sua idade: ");
    scanf("%d", &idade);
    printf("Entre com seu peso: ");
    scanf("%f", &peso);

    Pessoa *pessoa = cria_pessoa(nome, idade, peso);
    imprime_pessoa(*pessoa);

    free_pessoa(pessoa);

    return 0;
}
