#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"
#include "system.h"

typedef struct Lista PLista;
typedef struct Posic PPosic;
typedef void* Item;

struct Posic{
    Item data;
    PPosic* next;
};

struct Lista{
    PPosic* head;
    PPosic* tail;
    int capacidade;
    int elementos;
};

Lista createLista(int capacidade){
    PLista* list = (PLista*) malloc(sizeof(PLista));

    list->head = NULL;
    list->tail = NULL;
    list->capacidade = capacidade;
    list->elementos = 0;
    return list;
}

int length(Lista L){
    PLista* list = (PLista*) L;
    return list->elementos;
}

int maxLength(Lista L){
    PLista* list = (PLista*) L;
    return list->capacidade;
}

bool isEmpty(Lista L){
    PLista* list = (PLista*) L;
    if (list->elementos > 0){
        return false;
    }
    return true;
}

bool isFull(Lista L){
    PLista* list = (PLista*) L;
    if (list->elementos == list->capacidade){
        return true;
    }
    return false;
}

Posic insert(Lista L, Item info){
    PLista* list = (PLista*) L;

    if (isFull(list)){
        return NIL;
    }
    PPosic* newNode = calloc(1,sizeof(PPosic));

    newNode->data = info;
    newNode->next = NULL;
    if(list->head == NULL){ //Lista vazia
        list->head = newNode;
        list->tail = newNode;
    } else{
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->elementos = list->elementos + 1;
    return newNode;
}

Item pop(Lista L){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    Item item = list->head->data;

    PPosic* aux = list->head;
    list->head = list->head->next;
    free(aux);

    list->elementos = list->elementos - 1;
    return item;
}

void remover(Lista L, Posic p){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return;
    }
    PPosic* node = (PPosic*) p;
    PPosic* aux = getPrevious(list, node);

    if (node == list->head){ //Primeiro elemento
        list->head = list->head->next;
        deleteForm(node->data);
        free(node);
    } else if (node->next == NULL){ //Ultimo elemento
        list->tail = aux;
        list->tail->next = NIL;
        deleteForm(node->data);
        free(node);
    } else{
        aux->next = node->next;
        deleteForm(node->data);
        free(node);
    }
}

Item get(Lista L, Posic p){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    PPosic* node = (PPosic*) p;
    return node->data;
}

Posic insertBefore(Lista L,Posic p, Item info){//arrumar
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    if (isFull(list)){
        return NIL;
    }
    PPosic* node = (PPosic*) p;

    PPosic* aux = getPrevious(list, node);
    PPosic* newNode = calloc(1,sizeof(PPosic));
    if (aux == NULL){ //Primeiro elemento
        newNode->data = info;
        newNode->next = list->head;
        list->head = newNode;
    } else{
        newNode->data = info;
        newNode->next = aux->next;
        aux->next = newNode;
    }

    list->elementos = list->elementos + 1;
    return newNode;
}
 
Posic insertAfter(Lista L,Posic p, Item info){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    if (isFull(list)){
        return NIL;
    }
    PPosic* node = (PPosic*) p;
    PPosic* aux = getNext(list, node);
    PPosic* newNode = calloc(1,sizeof(PPosic));
    if (aux == NULL){ //Ultimo elemento
        newNode->data = info;
        newNode->next = NULL;
        list->tail->next = newNode;
        list->tail = newNode;
    } else{
        newNode->data = info;
        newNode->next = aux;
        node->next = newNode;
    }

    list->elementos = list->elementos + 1;
    return newNode;
}

Posic getFirst(Lista L){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    return list->head;
}

Posic getNext(Lista L,Posic p){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    PPosic* node = (PPosic*) p;
    return node->next;
}

Posic getLast(Lista L){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    return list->tail;
}

Posic getPrevious(Lista L,Posic p){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return NIL;
    }
    if(p == list->head){
        return NIL;
    }
    PPosic* aux = list->head;
    while (aux->next != p){
        aux = getNext(list, aux);
    }
    return aux;
}

void killLista(Lista L){
    PLista* list = (PLista*) L;
    if (isEmpty(list)){
        return;
    }
    PPosic* node = list->head;
    while(node != NULL){
        PPosic* aux = node;
        node = node->next;
        deleteForm(aux->data);
        free(aux);
    }
    free(list);
}