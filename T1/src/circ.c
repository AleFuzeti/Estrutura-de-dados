#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "circ.h"

typedef struct Circ PrivateCirc;

struct Circ{
    char type;
    int id;
    char corC[20];
    char corP[20];
    double x;
    double y;
    double r;
    double area;
    double protec;
    int vida;
    bool cap;
};

void* CriaCirculo(int id, char corC[], char corP[], double x, double y, double r){
    PrivateCirc* Circ = callocDataC();
    setCircId(Circ, id);
    setCircType(Circ, 'c');
    setCircCorC(Circ, corC);
    setCircCorP(Circ, corP);
    setCircX(Circ, x);
    setCircY(Circ, y);
    setCircR(Circ, r);
    setCircProtec(Circ, 60);
    Circ->area = 3.14*r*r;
    setCircVida(Circ, 2);
    return Circ;
};

bool checkCirc(void* n){
    PrivateCirc* Circ = (PrivateCirc*) n;
    if (Circ->type == 'c'){
        return true;
    } else {
        return false;
    }
}

void freeCirc(void* data){
PrivateCirc* forma = data;
free(forma);
}

void* callocDataC() {//aloca memoria suficiente para uma struct de dados
    PrivateCirc* Circ = calloc(1, sizeof(PrivateCirc));
    return Circ;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
int getCircId(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->id;
}
char* getCircCorC(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->corC;
}
char* getCircCorP(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->corP;
}
double getCircX(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->x;
}
double getCircY(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->y;
}
double getCircR(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->r;
} 
char getCircType(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->type;
}
double getCircArea(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->area;
}
double getCircProtec(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->protec;
}
int getCircVida(void* Sdata) {
    PrivateCirc* Circ = Sdata;
    return Circ->vida;
}
//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setCircId(void* Sdata, int Sid) {
    PrivateCirc* Circ = Sdata;
    Circ->id= Sid;
}
void setCircCorC(void* Sdata, char ScorC[]) {
    PrivateCirc* Circ = Sdata;
    //Circ->corC= ScorC;
    strcpy(Circ->corC, ScorC);
}
void setCircCorP(void* Sdata, char ScorP[]) {
    PrivateCirc* Circ = Sdata;
    //Circ->corP= ScorP;
    strcpy(Circ->corP, ScorP);
}
void setCircX(void* Sdata, double Sx) {
    PrivateCirc* Circ = Sdata;
    Circ->x = Sx;
}
void setCircY(void* Sdata, double Sy) {
    PrivateCirc* Circ = Sdata;
    Circ->y = Sy;
}
void setCircR(void* Sdata, double Sr) {
    PrivateCirc* Circ = Sdata;
    Circ->r = Sr;
}
void setCircType(void* Sdata, char Stype){
    PrivateCirc* Circ = Sdata;
    Circ->type = Stype;
}
void setCircArea(void* Sdata, double Sarea){
    PrivateCirc* Circ = Sdata;
    Circ->area = Sarea;
}
void setCircProtec(void* Sdata, double Sprotec){
    PrivateCirc* Circ = Sdata;
    Circ->protec = Sprotec;
}
void setCircVida(void* Sdata, int Svida){
    PrivateCirc* Circ = Sdata;
    Circ->vida = Svida;
}