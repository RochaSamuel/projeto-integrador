#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//Nomeando o ponteiro para a struct como 'ptr_elemento'
typedef struct list_item *ptr_elemento;

//Definindo um item da lista de adjacência
struct list_item{
    int id;  // Nome do vértice
    int value;  // Valor do vértice
    int weight;  // Peso da conexão ao vértice
    ptr_elemento next; // Ponteiro pro próximo vértice na lista
    ptr_elemento previous;  // Ponteiro pro vértice anterior na lista
};


// Chamando a struct com a 'cabeça' da lista de adjacência de 'ptr_cabecalho_LL'
typedef struct linked_list *ptr_cabecalho_LL;

// Definindo a cabeça da lista de adjacência
struct linked_list{
    int number_of_elements;  // Tamanho da lista
    int sum_of_weights; // Soma de todos os pesos no Grafo
    int id;  // Nome do vértice a que a lista se refere
    ptr_elemento start;  // Vértice inicial da lista
    ptr_elemento end;  // Vértice final da lista
};


// Vamos àsfunções

ptr_cabecalho_LL criarCabecalho(void)
{
    // Essa função retorna um ponteiro para uma lista ligada de adjacência
    ptr_cabecalho_LL L = (ptr_cabecalho_LL)malloc(sizeof(*L));  // Alocação de memória
    L->number_of_elements = 0;  // Tamanho da lista
    L->sum_of_weights = 0;  // Soma de todos os pesos
    L->id = 0;  // Nome do vértice a que a lista se refere
    L->start = NULL; // Endereço do primeiro vértice da lista de adjacência
    L->end = NULL;  // Endereço do último vértice da lista de adjacência
    return L;
}

ptr_elemento criarElemento(void)
{
    // Cria um vértice para lista de adjacẽncia
    ptr_elemento new_item = (ptr_elemento)malloc(sizeof(*new_item));  // Alocação de memória
    new_item->next = NULL; // Ponteiro para o próximo vértice na lista de adjacẽnca
    new_item->previous = NULL;  // Ponteiro para o vértice anterior na lista de adjacência
    new_item->id = 0;  // Nome do vértice
    new_item->value = 0;  // Valor do vértice
    new_item->weight = 0;  // Peso para conexão a este vértice nessa lista
    return new_item;
}

void mostrarElementos(ptr_cabecalho_LL L)
{
    // Mostra os elementos da lista de adjacência
    printf("L: -");
    ptr_elemento current = criarElemento();  // Cria um vértice local para receber os valores
    for(current = L->start; current != NULL; current = current->next)
    // For loop que itera sobre a lista toda
    // esse loop é usado diversas vezes.
    {
        // Printa 3-upla para cada item, com id, value e weight
        printf("(%d,%d,%d)-",current->id, current->value, current->weight);
    }
    printf("\n");
}

int popElemento(int target_id, ptr_cabecalho_LL L)
{
    // Remove o item de id 'target_id' da lista de adjacência
    ptr_elemento current = criarElemento();
    // Testando para o caso no qual o primeiro ptr_elemento da lista já é nosso alvo
    if(L->start->value == target_id)
    {
        L->sum_of_weights -= L->start->weight;
        ptr_elemento temp = criarElemento();
        temp = L->start;
        L->start = temp->next;
        L->number_of_elements--;  // Diminui o comprimento da lista em 1
        free(temp);  // Libera espaço de temp na memória
        return 0;
    }
    // Itera sobre a lista para buscar item a ser removido
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->next->value == target_id)
        {
            L->sum_of_weights -= L->start->weight;
            ptr_elemento temp = criarElemento();
            temp = current->next;
            current->next = current->next->next;
            L->number_of_elements--;
            free(temp);
            return 0;
        }
    }
    printf("Item not on list");
    return 0;
}

int pushElemento(int new_id, int new_value, int new_weight, ptr_cabecalho_LL L)
{
    // Adiciona vértice à lista de adjacência
    int i;
    ptr_elemento new_item = criarElemento();  // Cria novo vértice....
    new_item->value = new_value;
    new_item->id = new_id;
    new_item->weight = new_weight;  // ... e preenche os valores informados
    new_item->next = L->start;
    new_item->previous = NULL;
    if(L->number_of_elements > 0) // Só precisa reescrever o 'anterior' do primeiro item se houver um primeiro item
    {
        L->start->previous = new_item;
    }
    L->start = new_item;  // E adiciona ele ao início da fila
    L->sum_of_weights += new_item->weight;
    L->number_of_elements++;
    return 0;
}

int is_adjacent_to(int id, ptr_cabecalho_LL L)
{
    // Testa se 'id' é pertencente a essa lista de adjacência
    ptr_elemento current = criarElemento();
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->id == id) return 1;
    }
    return 0;
}