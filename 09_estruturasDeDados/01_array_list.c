#include "01_array_list.h"

/*
    Antes de falar de estruturas de dados, temos que definir a diferença entre estruturas de dados abstratas e suas implementações. Uma estrutura
    de dados abstrata é apenas um conjunto de regras e operações, é como um conceito matemático e não é possível saber o custo computacional de suas
    operações, porque o "como" realiza-las ainda não é sabido! Qualquer implementação de uma estrutura de dados devo obedecer a todas as regras e
    implementar todas as operações para ser válida. A partir daí podemos sim medir o custo computacional (geralmente usando notação grande O, pesquise
    sobre) de suas operações e pontencialmente compará-la com outras estruturas de dados ou outras implementações da mesma estrutura. Tome cuidado!
    a grande maioria dos cálculos de custo computacional não leva em conta o custo de cada operação, apenas o número de operações feitas e, portanto,
    é apenas uma estimativa, se performance é muito importante você deve testar diferentes implementações para o seu caso.

    A estrutura de dados mais simples e fundamental é a Lista, ela é a base para muitas outras estruturas. Uma lista é basicamente um vetor(array),
    porém com tamanho totalmente flexivel, podendo ser iniciada com tamanho 0 e crescendo ou diminuido conforme elementos são inseridos ou retirados
    de forma automática. Assim como vetores começam a ser indexadas no 0 por padrão. Toda lista deve implementar as seguintes operações:
    - Adicionar um item em uma posição arbitrária
    - Remover um item em uma posição arbitrária
    - Retornar o tamanho da lista (número de itens)
    - Retornar um item em uma posição arbitrária

    Essas são as operações básicas, porem podemos adicioar outras para facilitar a vida de quem for usar nossas estruturas, como verificar se existe
    um item na lista, retornar o indice de um item, adicionar um item no início da lista, adicionar um elemento no fim da lista, etc

    A implementação mais comum para uma Lista é chamada de ArrayList. Ela implementa as operações de Lista utilizando arrays estáticos, e, conforme a
    lista precisa crescer, realoca o array estático interno para um maior (geralmente o dobro do tamanho atual) copiando todos os valores antigos.
    Sua performance é muito boa, tendo em vista que para a maioria das operações é tão rápida quanto um array estático, com as únicas operações pesadas
    sendo ao adicionar um item onde é necessário aumentar o tamanho do array interno, adicionar um item sem ser no fim ou remover um elemento sem ser
    no fim, essas operações são O(n).

    Você pode estar se perguntando: "Onde está a definição da estrutura da ArrayList?" Bem, eu decidi que está na hora de falar sobre
    os arquivos headers (.h) e como podemos fazer os nossos. Note no cabeçado do arquivo '#include "02_linked_list.h"', aqui estamos importando o
    nosso próprio header! Note que para .h's não nativos do C temos que utilizar "" e não <> para os incluir.

    Os arquivos .h contém somente definição de constantes, tipos e assinaturas de métodos, deixando a implementação para os arquivos .c. Caso você
    deseje usar as funções e estruturas descritas em um .h não nativo, você deve inclui-lo no seu arquivo .c e, na hora de compilar, adicionar tanto
    o arquivo.h desejado como o .c (de mesmo nome) onde as funções são implementadas como arquivos para serem compilados. Veja o exemplo:

    gcc 01_array_list.h 01_array_list.c <seu_arquivo_aqui>.c -o output

    Isso irá criar um executável "output" corretamente

    Pesquise mais sobre o assunto e também sobre "makefiles", uma forma de automatizar e simplificar esse processo!
*/

// Criando uma ArrayList com um tamanho inicial
ArrayList *ArrayList_create_with_size(int starting_size, size_t item_size)
{
    if (starting_size <= 0)
        return NULL;

    ArrayList *list = malloc(sizeof(ArrayList));
    // Funões que alocam memória podem falhar se o computador estievr sem memória! Nesse caso podemos checar se malloc retornou NULL
    if (list == NULL)
        return NULL;

    // Lista vazia começa com tamanho 0
    list->size = 0;
    list->max_size = starting_size;
    list->item_size = item_size;
    list->items = calloc(starting_size, item_size);

    if (list->items == NULL)
    {
        // Nesse caso conseguimos alocar a lista mas não o array interno, então temos que libeara a lista
        free(list);
        return NULL;
    }

    return list;
}

// Caso o usuário não quiser definir um tamanho inicial, oferecemos essa função que cria uma com tamanho inicial 10 reutilziando o código acima
ArrayList *ArrayList_create(size_t item_size)
{
    return ArrayList_create_with_size(10, item_size);
}

void *ArrayList_get(ArrayList *list, int index)
{
    // Index inválido
    if (index < 0 || index >= list->size)
        return NULL;

    return list->items[index];
}

int ArrayList_add(ArrayList *list, void *item, int index)
{
    // Index inválido, adição falhou
    if (index < 0 || index > list->size)
        return 0;

    // Temos que aumentar o tamanho do array interno!
    if (list->size == list->max_size)
    {
        // Caso o tamanho da lista já seja o valor máximo suportado por "int", não podemos aumentar seu tamanho pois não seria possivel indexa-la
        if (list->size == INT_MAX)
        {
            printf("List too long to be indexed by int");
            return 0;
        }
        // O novo tamanho é o tamanho antigo multiplicado por 2 (procure pelo operador << e >>)
        int new_size = list->size << 1;
        // Um dos motivos de usarmos "int" e não "unsigned int" para indexar o valor é para fazer o check de overflow aqui, se o tamanho máximo atual da
        // lista for maior que o suprotado por int, ele irá dar overflow para um valor negativo (ou 0) e podemos checar aqui
        list->max_size = new_size > 0 ? new_size : INT_MAX;

        // A função realloc realoca um ponteiro para um novo tamanho copiando os valores antigos
        void **newArray = realloc(list->items, list->item_size * list->max_size);

        // acabou a memória!
        if (newArray == NULL)
            return 0;

        list->items = newArray;
    }

    // Adicionamos um item então a lista cresce!
    list->size++;

    // Ao adicionar um item em uma posição qualquer (que não seja a última), devemos mover os items após o índice uma posição para frente
    void *to_be_moved = item;

    for (int i = index; i < list->size; i++)
    {
        void *temp = list->items[i];
        list->items[i] = to_be_moved;
        to_be_moved = temp;
    }

    // Adição feita com sucesso!
    return 1;
}

void *ArrayList_remove(ArrayList *list, int index)
{
    void *removed = ArrayList_get(list, index);

    // Index inválido, remoção falhou
    if (removed == NULL)
        return NULL;

    // Ao remover um item em uma posição qualquer, devemos mover os items a partir do indice uma posição para tras
    for (int i = index; i < list->size; i++)
    {
        list->items[i] = list->items[i + 1];
    }

    // Removemos um item então a lista diminui!
    list->size--;

    return removed;
}

// Como esses métodos opcionais são úteis e de fácil implementação, vamos implementar!
int ArrayList_add_start(ArrayList *list, void *item)
{
    return ArrayList_add(list, item, 0);
}

int ArrayList_add_end(ArrayList *list, void *item)
{
    return ArrayList_add(list, item, list->size);
}

void *ArrayList_remove_start(ArrayList *list)
{
    return ArrayList_remove(list, 0);
}

void *ArrayList_remove_end(ArrayList *list)
{
    return ArrayList_remove(list, list->size - 1);
}

// Como ArrayList é uma struct compelxa, temos que liberar seus elementos
void ArrayList_dealocate(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        // Liberando cada item
        free(list->items[i]);
    }
    // Liberando o array
    free(list->items);
    // Finalmente podemos libeara a lista
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

// Como vamos a ideia é improtar esse aquivo e o .h para utilizar ArrayList em outros lugares, esse aquivo não pode ter um main, para tal basta mudar
// o 1 após "#if" que todo o código até o "#endif" será desconsiderado
#if 1

int main()
{
    srand(time(NULL));

    // Criando um ArrayList para ints, note que devemos especificar o tamanho para "int *" e não "int", pois no ArrayList armazenamos os ponteiros, não os valores
    ArrayList *list = ArrayList_create(sizeof(int *));

    // Teste manuais
    ArrayList_add_start(list, create_pointer(2));
    assert(*((int *)ArrayList_get(list, 0)) == 2);

    ArrayList_add_start(list, create_pointer(3));
    assert(*((int *)ArrayList_get(list, 0)) == 3);
    assert(*((int *)ArrayList_get(list, 1)) == 2);

    ArrayList_add_end(list, create_pointer(4));
    assert(*((int *)ArrayList_get(list, 0)) == 3);
    assert(*((int *)ArrayList_get(list, 1)) == 2);
    assert(*((int *)ArrayList_get(list, 2)) == 4);

    ArrayList_add(list, create_pointer(5), 1);
    assert(*((int *)ArrayList_get(list, 0)) == 3);
    assert(*((int *)ArrayList_get(list, 1)) == 5);
    assert(*((int *)ArrayList_get(list, 2)) == 2);
    assert(*((int *)ArrayList_get(list, 3)) == 4);

    ArrayList_remove(list, 2);
    assert(*((int *)ArrayList_get(list, 0)) == 3);
    assert(*((int *)ArrayList_get(list, 1)) == 5);
    assert(*((int *)ArrayList_get(list, 2)) == 4);

    ArrayList_remove_end(list);
    assert(*((int *)ArrayList_get(list, 0)) == 3);
    assert(*((int *)ArrayList_get(list, 1)) == 5);

    ArrayList_remove_start(list);
    assert(*((int *)ArrayList_get(list, 0)) == 5);

    // Liberando o ponteiro para uso posterior
    ArrayList_dealocate(list);

    // Reutilizando o ponteiro
    list = ArrayList_create(sizeof(int *));

    int test_size = 100;

    for (int i = 0; i < test_size; i++)
    {
        int *item = create_pointer(i);

        // Sorteando um index para inserir o elemento
        int index = list->size > 0 ? rand() % (list->size) : 0;
        if (ArrayList_add(list, item, index))
        {
            printf("List size: %d\n", list->size);
            printf("List max size: %d\n\n", list->max_size);
        }
        else
        {
            printf("Out of memory when adding item at index %d\n", index);
            exit(1);
        }
    }

    for (int i = 0; i < list->size; i++)
    {
        // Não vamos checar o item aqui pois sabemos que se a alocação acima funcionou e estaremos sempre acessando um index válido, item nunca será NULL
        int *item = (int *)ArrayList_get(list, i);
        printf("Item at index %d: %d\n", i, *item);
    }

    // Removendo aleatoriamente metade dos itens
    for (int i = 0; i < (test_size >> 1); i++)
    {
        // Sorteando um index para remover o elemento
        int index = rand() % (list->size);
        int *removed_item = ArrayList_remove(list, index);

        if (removed_item != NULL)
        {
            printf("Removed item at index %d: %d\n", index, *removed_item);
            printf("List size: %d\n", list->size);
            printf("List max size: %d\n\n", list->max_size);

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
        printf("Item at index %d: %d\n", i, *((int *)ArrayList_get(list, i)));
    }

    ArrayList_dealocate(list);

    return 0;
}

#endif
