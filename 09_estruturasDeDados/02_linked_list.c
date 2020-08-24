#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "02_linked_list.h"

/*
    A próxima estrutura de dados que vamos estudar é outra implementação muito comum de Lista, a LinkedList (ou lista linkada). Ela implementa
    as funcionalidades de lista utilizando utilizando uma subestrtutura auxiliar chamada de nodo. Cada nodo armazena informação (nosso item),
    uma referência para o próximo nodo na lsita e (no nosso caso, como estamos implementando uma lista duplamente linkada) uma referência para
    o nodo anterior na lista. O primeiro nodo da lista tem a referência do anterior como NULL e o útimo tem a referência do próximo como NULL,
    assim sabemos quando estamos nos extremos da lista. Veja uma exemplificação gráfica abaixo:

    NULL <- 3 -> <- 4 -> <- 5 -> <- 7 -> NULL

    Na LinkedList acima temos que 3 é o primeiro item e 7 o útimo. O item 4 aponta para 5 (próximo) e para 3 (anterior), e  etc.

    Perceba que teoricamente não temos index nessa lista, os elementos não tem um índice implícito associado a eles, porém, como ordena a interface
    de lista, temos que permitir acessar/adicionar/remover itens em índices específicos, fazemos isso navegando pela lista, contando os elementos
    até atingir o index desejado.

    Como em ArrayList, veja o arquivo .h para ver as definições das structs e as assinaturas dos métodos
*/

// Criando uma lista vazia, de tamanho 0
LinkedList *LinkedList_create()
{
    LinkedList *list = malloc(sizeof(LinkedList));

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

// Função auxiliar que cria um nodo. Será visível somente nesse arquivo pois sua assinatura não está no .h
struct _node *create_node(void *data, struct _node *prev, struct _node *next)
{
    struct _node *node = malloc(sizeof(struct _node));

    // Não vamos liberar "data*" aqui pois jogamos a responsabilidade para quem o alocou inicialmente
    if (node == NULL)
        return NULL;

    node->data = data;
    node->prev = prev;
    node->next = next;

    return node;
}

// Função auxiliar também somente para uso inerno
struct _node *get_node(LinkedList list, unsigned int index)
{
    // Não vamos fazer check de índice aqui pois será somente para uso interno em funções que já fazem esse check

    // Contando a partir da cabeça para encontrar o nodo no índice
    struct _node *node_at_index = list.head;

    for (unsigned int i = 0; i < index; i++)
        node_at_index = node_at_index->next;

    return node_at_index;
}

void *LinkedList_get(LinkedList *list, unsigned int index)
{
    // Índice inválido
    if (index >= list->size)
        return NULL;

    // Retornando apenas a informação
    return get_node(*list, index)->data;
}

// Como em linked list inserir/remover no final são casos especiais, vamos implementá-los primeiro
int LinkedList_add_start(LinkedList *list, void *item)
{
    // A lista atingiu o maior tamanho indexável
    if (list->size == UINT_MAX)
        return 0;

    struct _node *old_head = list->head;
    // A nova cabeça da lista deve apontar o anterior como NULL e próximo como a antiga cabeça
    struct _node *new_head = create_node(item, NULL, old_head);

    // Não conseguimos alocar mais um nodo
    if (new_head == NULL)
        return 0;

    // A antiga cabeça deve apontar o anterior como a nova cabeça e próximo não deve ser alterado
    if (old_head != NULL)
        old_head->prev = new_head;

    list->head = new_head;
    list->size++;

    // Esse tipo de check será comum ao adicionarmos/removermos um item, pois caso uma LinkedList tenha tamanho 1,
    // a "head" e "last" devem ser iguais e não nulas
    if (list->size == 1)
        list->last = new_head;

    return 1;
}

// Bem parecido com add_start
int LinkedList_add_end(LinkedList *list, void *item)
{
    if (list->size == UINT_MAX)
        return 0;

    struct _node *old_last = list->last;
    struct _node *new_last = create_node(item, old_last, NULL);

    if (new_last == NULL)
        return 0;

    if (old_last != NULL)
        old_last->next = new_last;

    list->last = new_last;
    list->size++;

    if (list->size == 1)
        list->head = new_last;

    return 1;
}

void *LinkedList_remove_start(LinkedList *list)
{
    // Não tem o que remover!
    if (list->size == 0)
        return NULL;

    struct _node *old_head = list->head;
    struct _node *new_head = old_head->next;

    // "prev" da cabeça deve ser NULL por definção
    if (new_head != NULL)
        new_head->prev = NULL;

    // Mudando a referência da cabeça
    list->head = new_head;
    list->size--;

    if (list->size <= 1)
        list->last = new_head;

    old_head->next = NULL;
    // Extraindo a informação do nodo e depois liberando ele (importante!)
    void *data = old_head->data;
    free(old_head);

    return data;
}

// Parecido com remove_start
void *LinkedList_remove_end(LinkedList *list)
{
    if (list->size == 0)
        return NULL;

    struct _node *old_last = list->last;
    struct _node *new_last = old_last->prev;

    // "next" do last deve ser NULL por definção
    if (new_last != NULL)
        new_last->next = NULL;

    // Mudando a referência da cabeça
    list->last = new_last;
    list->size--;

    if (list->size <= 1)
        list->head = new_last;

    old_last->prev = NULL;

    // Extraindo a informação do nodo e depois liberando ele (importante!)
    void *data = old_last->data;
    free(old_last);

    return data;
}

// Hora de lidar com as operações que fazem referência a um índice arbitrário! Essas são as operações pesadas de LinkedList
// já que devemos contar os elementos para chegar a um index
int LinkedList_add(LinkedList *list, void *item, unsigned int index)
{
    // Índice inválido
    if (index > list->size)
        return 0;

    if (index == 0)
        return LinkedList_add_start(list, item);

    if (index == list->size)
        return LinkedList_add_end(list, item);

    if (list->size == UINT_MAX)
        return 0;

    // Aqui temos certeza que não estamos lidando com "head" ou "last" da lista, o que facilita as coisas!

    struct _node *node_at_index = get_node(*list, index);

    // Criando o novo nodo usando os dados do que estava no seu lugar
    struct _node *new_node_at_index = create_node(item, node_at_index->prev, node_at_index);

    if (new_node_at_index == NULL)
        return 0;

    node_at_index->prev->next = new_node_at_index;
    node_at_index->prev = new_node_at_index;

    list->size++;

    return 1;
}

void *LinkedList_remove(LinkedList *list, unsigned int index)
{
    // Índice inválido
    if (index >= list->size)
        return 0;

    if (index == 0)
        return LinkedList_remove_start(list);

    if (index + 1 == list->size)
        return LinkedList_remove_end(list);

    if (list->size == UINT_MAX)
        return 0;

    // Aqui temos certeza que não estamos lidando com "head" ou "last" da lista, o que facilita as coisas!

    struct _node *node_at_index = get_node(*list, index);

    // O próximo do anterior deve ser o próximo e o anterior do próximo deve ser o anterior
    node_at_index->prev->next = node_at_index->next;
    node_at_index->next->prev = node_at_index->prev;
    node_at_index->next = NULL;
    node_at_index->prev = NULL;

    // Extraindo a informação do nodo e depois liberando ele (importante!)
    void *data = node_at_index->data;
    free(node_at_index);

    list->size--;

    return data;
}

void LinkedList_dealocate(LinkedList *list)
{
    struct _node *p = list->head;

    // Enquanto o ponteiro que usamos para navegar a lista não for NULL, libearmos cada nodo e seus dados
    while (p != NULL)
    {
        free(p->data);

        struct _node *to_free = p;
        p = p->next;

        free(to_free);
    }

    free(list);
    list = NULL;
}

// Somente para testes
int *create_pointer(int value)
{
    int *p = malloc(sizeof(int));

    if (p == NULL)
    {
        printf("Out of memory allocating int pointer\n");
        exit(1);
    }

    *p = value;
    return p;
}

#if 1

int main()
{
    // Criando um LinkedList para ints, note que devemos especificar o tamanho para "int *" e não "int", pois no LinkedList armazenamos os ponteiros, não os valores
    LinkedList *list = LinkedList_create(sizeof(int *));

    // Teste manuais
    LinkedList_add_start(list, create_pointer(2));
    assert(*((int *)LinkedList_get(list, 0)) == 2);

    LinkedList_add_start(list, create_pointer(3));
    assert(*((int *)LinkedList_get(list, 0)) == 3);
    assert(*((int *)LinkedList_get(list, 1)) == 2);

    LinkedList_add_end(list, create_pointer(4));
    assert(*((int *)LinkedList_get(list, 0)) == 3);
    assert(*((int *)LinkedList_get(list, 1)) == 2);
    assert(*((int *)LinkedList_get(list, 2)) == 4);

    LinkedList_add(list, create_pointer(5), 1);
    assert(*((int *)LinkedList_get(list, 0)) == 3);
    assert(*((int *)LinkedList_get(list, 1)) == 5);
    assert(*((int *)LinkedList_get(list, 2)) == 2);
    assert(*((int *)LinkedList_get(list, 3)) == 4);

    LinkedList_remove(list, 2);
    assert(*((int *)LinkedList_get(list, 0)) == 3);
    assert(*((int *)LinkedList_get(list, 1)) == 5);
    assert(*((int *)LinkedList_get(list, 2)) == 4);

    LinkedList_remove_end(list);
    assert(*((int *)LinkedList_get(list, 0)) == 3);
    assert(*((int *)LinkedList_get(list, 1)) == 5);

    LinkedList_remove_start(list);
    assert(*((int *)LinkedList_get(list, 0)) == 5);

    // Liberando o ponteiro para uso posterior
    LinkedList_dealocate(list);

    // Reutilizando o ponteiro
    list = LinkedList_create(sizeof(int *));

    if (list == NULL)
    {
        printf("Out of memory allocating list\n");
        exit(1);
    }

    int test_size = 100;

    for (int i = 0; i < test_size; i++)
    {
        int *item = malloc(sizeof(int));
        if (item == NULL)
        {
            printf("Out of memory allocating new item %d\n", item);
            exit(1);
        }
        *item = i;

        // Sorteando um index para inserir o elemento
        int index = list->size > 0 ? rand() % (list->size) : 0;
        if (!LinkedList_add(list, item, index))
        {
            printf("Out of memory when adding item at index %d\n", index);
            exit(1);
        }
    }

    for (int i = 0; i < list->size; i++)
    {
        // Não vamos checar o item aqui pois sabemos que se a alocação acima funcionou e estaremos sempre acessando um index válido, item nunca será NULL
        int *item = (int *)LinkedList_get(list, i);
        printf("Item at index %d: %d\n", i, *item);
    }

    // Removendo aleatoriamente metade dos itens
    for (int i = 0; i < (test_size >> 1); i++)
    {
        // Sorteando um index para remover o elemento
        int index = rand() % (list->size);
        int *removed_item = LinkedList_remove(list, index);

        if (removed_item != NULL)
        {
            printf("Removed item at index %d: %d\n", index, *removed_item);
            printf("List size: %u\n", list->size);

            // Liberando o item!
            free(removed_item);
        }
        else
        {
            printf("Error removing item at index %d\n", index);
            exit(1);
        }
    }

    for (int i = 0; i < list->size; i++)
    {
        printf("Item at index %d: %d\n", i, *((int *)LinkedList_get(list, i)));
    }

    LinkedList_dealocate(list);

    return 0;
}

#endif
