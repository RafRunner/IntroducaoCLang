
// A estrutura formada por "ifndef", "define" e "endif" serve para impedir que esse header não seja importado mais de uma vez
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

// Ao não utilizar "typedef" antes de "struct", simplificamos a declaração, mas temos que usar "struct" antes do nome da estrutura ao nos
// referirmos a ela. Como essa struct não será utilizado pelo usuário final do código (é um detalhe de implementação que deveria ser visível
// apenas para quem for mexer no código da biblioteca em si) não vamos nos preocupar com o nome (é padrão usar _nome nesses casos);
struct _node
{
    // Estamos usando ponteiro para void, mas nesse caso não precisamos nos preocupar com o tamanho do dado que será guardado aqui, pois estamos
    // armezenando apenas um valor, não um vetor, será responsabildiade do código cliente alocar espaço para o ponteiro e fornecer somente o ponteiro
    // genérico, que poderá ter seu tipo resgatado posteriormente também pelo código cliente, como vamos ver nos exemplos
    void *data;

    // Perceba que o nodo tem dois ponteiros para outros nodos, por isso dizemos que listas linkadas são estruturas recursivas!
    struct _node *next;
    struct _node *prev;
};

// A lista em si é somente uma referência para o primeiro nodo "head", o último "last" (não é necessário, mas facilita e acelera bastante) e o tamanho
// atual da lista (contagem de itens, serve também para validação de índices)
typedef struct LinkedList
{
    struct _node *head;
    struct _node *last;
    unsigned int size;
} LinkedList;

// Declarando as assinaturas dos métodos que vamos implementar no arquivo de mesmo novo com terminação .c
// Perceba que são os mesmos que implementamos em ArrayList, isso porque as duas listas tem a mesma interface (devem ter o mesmo comportamento com as mesmas
// operações, apenas os detalhes internos são diferentes)
LinkedList *LinkedList_create();

int LinkedList_add(LinkedList *list, void *item, unsigned int index);

int LinkedList_add_start(LinkedList *list, void *item);

int LinkedList_add_end(LinkedList *list, void *item);

void *LinkedList_remove_start(LinkedList *list);

void *LinkedList_remove_end(LinkedList *list);

void *LinkedList_get(LinkedList *list, unsigned int index);

void *LinkedList_remove(LinkedList *list, unsigned int index);

void LinkedList_dealocate(LinkedList *list);

#endif // LINKED_LIST_H
