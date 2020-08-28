// A estrutura formada por "ifndef", "define" e "endif" serve para impedir que esse header seja importado mais de uma vez
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <stddef.h>

typedef struct ArrayList
{
    // A quantidade de itens na lista atualmente. A operação de retornar o tamanho da lista está implicito nessa propriedade
    int size;

    // O maior número de itens que podem ser guardados no array interno atualemente
    int max_size;

    // O array interno. "void*" é um ponteiro genérico para qualquer tipo de dado. Temos que usar um ponteiro duplo pois como não sabemos para qual
    // tipo de dado nossa lista será usada, teremos que armazenar os ponteiros para os items no lugar dos items propriamente ditos
    void **items;

    // Quando usamos "void*", temos que salvar o tamanho do tipo de dado que vamos guardar no ponteiro, ou então não será possível lê-lo
    size_t item_size;
} ArrayList;

// Declarando as assinaturas dos métodos que vamos implementar no arquivo de mesmo novo com terminação .c
ArrayList *ArrayList_create_with_size(int starting_size, size_t item_size);

ArrayList *ArrayList_create(size_t item_size);

void *ArrayList_get(ArrayList *list, int index);

int ArrayList_add(ArrayList *list, void *item, int index);

void *ArrayList_remove(ArrayList *list, int index);

int ArrayList_add_start(ArrayList *list, void *item);

int ArrayList_add_end(ArrayList *list, void *item);

void *ArrayList_remove_start(ArrayList *list);

void *ArrayList_remove_end(ArrayList *list);

void ArrayList_dealocate(ArrayList *list);

#endif // ARRAY_LIST_H
