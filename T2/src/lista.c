#include "libs.h"
#include "lista.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"
#include "system.h"

typedef void* Item;

typedef struct posic{
    Item data;
    struct posic* next, *prev;
}posic;

typedef struct lista{
    struct posic* head, *tail;
    int capacidade;
    int elementos;
}lista;

Lista createLista(int capacidade){
    lista* list = malloc(sizeof(lista));

    list->head = NULL;
    list->tail = NULL;
    list->capacidade = capacidade;
    list->elementos = 0;
    return list;
}

int length(Lista L){
    lista* list = (lista*) L;
    return list->elementos;
}

int maxLength(Lista L){
    lista* list = (lista*) L;
    return list->capacidade;
}

bool isEmpty(Lista L){
    lista* list = (lista*) L;
    if (list->elementos > 0){
        return false;
    }
    return true;
}

bool isFull(Lista L){
    lista* list = (lista*) L;
    if (list->elementos == list->capacidade){
        return true;
    }
    return false;
}

Posic insert(Lista L, Item info){
    lista* list = (lista*) L;

    if (isFull(list)){
        return NIL;
    }
    posic* newNode = calloc(1,sizeof(posic));

    newNode->data = info;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(list->head == NULL){ //Lista vazia
        list->head = newNode;
        list->tail = newNode;
    } else{
        list->tail->next = newNode;
        newNode->prev = list->tail; 
        list->tail = newNode;
    }
    list->elementos = list->elementos + 1;
    return newNode;
}

Item pop(Lista L){
    lista* list = (lista*) L;
    if (isEmpty(list))
    {
        return NIL;
    }
    Item item = list->head->data;

    posic* aux = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free(aux);

    list->elementos = list->elementos - 1;
    return item;
}

void remover(Lista L, Posic p){
    lista* list = (lista*) L;
    if (isEmpty(list))
    {
        return;
    }
    posic* node = (posic*) p;

    if (node == list->head)//Primeiro elemento
    { 
        list->head = list->head->next;
        list->head->prev = NULL;
        deleteForm(node->data);
        free(node);
    } else if (node->next == NULL)//Ultimo elemento
    { 
        list->tail = list->tail->prev;
        list->tail->next = NIL;
        deleteForm(node->data);
        free(node);
    } else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        deleteForm(node->data);
        free(node);
    }
}

Item get(Lista L, Posic p){
    lista* list = (lista*) L;
    if (isEmpty(list))
    {
        return NIL;
    }
    posic* node = (posic*) p;
    return node->data;
}

Posic insertBefore(Lista L,Posic p, Item info){
    lista* list = (lista*) L;
    if (isEmpty(list))
    {
        return NIL;
    }
    if (isFull(list))
    {
        return NIL;
    }
    posic* node = (posic*) p;
    posic* newNode = calloc(1,sizeof(posic));

    if (node->prev == NULL)//Primeiro elemento
    { 
        newNode->data = info;
        newNode->next = list->head;
        list->head = newNode;
        newNode->prev = NULL;
        newNode->next->prev = newNode;
        
    } else{
        newNode->data = info;
        newNode->next = node->prev->next;
        node->prev->next = newNode;
    }

    list->elementos = list->elementos + 1;
    return newNode;
}
 
Posic insertAfter(Lista L,Posic p, Item info){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    if (isFull(list)){
        return NIL;
    }
    posic* node = (posic*) p;
    posic* newNode = calloc(1,sizeof(posic));
    if (node->next == NULL){ //Ultimo elemento
        newNode->data = info;
        newNode->next = NULL;
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    } else{
        newNode->data = info;
        newNode->next = node->next;
        newNode->prev = node;
        newNode->next->prev = newNode;
        node->next = newNode;
    }

    list->elementos = list->elementos + 1;
    return newNode;
}

Posic getFirst(Lista L){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    return list->head;
}

Posic getNext(Lista L,Posic p){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    posic* node = (posic*) p;
    return node->next;
}

Posic getLast(Lista L){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    return list->tail;
}

Posic getPrevious(Lista L,Posic p){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    posic* node = (posic*) p;
    return node->prev;
}

void killLista(Lista L){
    lista* list = (lista*) L;
    if (isEmpty(list)){
        return;
    }
    posic* node = list->head;
    while(node != NULL){
        posic* aux = node;
        node = node->next;
        deleteForm(aux->data);
        free(aux);
    }
    free(list);
}

void swap ( void* a, void* b ){
    void* t = a; a = b; b = t; 
}

Posic partition(Lista L, posic *l, posic *h){

    double area = getAreaGeral(h);
    
    posic* i = getPrevious(L,l);

    for (posic *j = l; j != h; j = j->next)
    {
        double area2 = getAreaGeral(j);      
        if (area2 <= area)
        {
            i = (i == NULL) ? l : i->next;

            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL) ? l : i->next; 
    swap(&(i->data), &(h->data));
    return i;
}

void _quickSort(Lista L, posic *l, posic *h)
{
    if (l != h && l != NULL && l != h->next)
    {
        posic* p = partition(L, l, h);
        _quickSort(L, l, p->prev);
        _quickSort(L, p->next, h);
    }   
}

void quickSort(Lista L)
{
    
    Lista list = L;
    posic* head = getFirst(list);
    posic* tail = getLast(list);

    // chama a recursiva QuickSort
    _quickSort(L, head, tail);
}
