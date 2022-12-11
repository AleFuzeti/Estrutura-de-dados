#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "rect.h"

typedef struct Rect PrivateRect; 

struct Rect{
    char type;
    int id;
    char corC[20];
    char corP[20];
    double x;
    double y;
    double w;
    double h;
    double area;
    double protec;
    int vida;
};

void* CriaRetangulo(int id, char corC[], char corP[], double x, double y, double w, double h){
    PrivateRect* Rect = callocDataR();
    setRectId(Rect, id);
    setRectType(Rect, 'r');
    setRectCorC(Rect, corC);
    setRectCorP(Rect, corP);
    setRectX(Rect, x);
    setRectY(Rect, y);
    setRectW(Rect, w);
    setRectH(Rect, h);
    setRectProtec(Rect, 60);
    Rect->area = w*h;
    setRectVida(Rect, 3);
    return Rect;
};
bool checkRect(void* n){
    PrivateRect* Rect = (PrivateRect*) n;
    if (Rect->type == 'r'){
        return true;
    } else {
        return false;
    }
} 

void freeRect(void* data){
PrivateRect* forma = data;
free(forma);
}

//aloca memoria suficiente para uma struct de dados
void* callocDataR() {
    PrivateRect* Rect = calloc(1, sizeof(PrivateRect));
    return Rect;
}
//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
int getRectId(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->id;
}
char* getRectCorC(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->corC;
}
char* getRectCorP(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->corP;
}
double getRectX(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->x;
}
double getRectY(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->y;
}
double getRectW(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->w;
}
double getRectH(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->h;
}
char getRectType(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->type;
}
double getRectArea(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->area;
}
double getRectProtec(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->protec;
}
int getRectVida(void* Sdata) {
    PrivateRect* Rect = Sdata;
    return Rect->vida;
}
//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setRectId(void* Sdata, int Sid) {
    PrivateRect* Rect = Sdata;
    Rect->id= Sid;
}
void setRectCorC(void* Sdata, char ScorC[]) {
    PrivateRect* Rect = Sdata;
    //Rect->corC= ScorC;
    strcpy(Rect->corC, ScorC);
}
void setRectCorP(void* Sdata, char ScorP[]) {
    PrivateRect* Rect = Sdata;
    //Rect->corP= ScorP;
    strcpy(Rect->corP, ScorP);

}
void setRectX(void* Sdata, double Sx) {
    PrivateRect* Rect = Sdata;
    Rect->x = Sx;

}
void setRectY(void* Sdata, double Sy) {
    PrivateRect* Rect = Sdata;
    Rect->y = Sy;
}
void setRectW(void* Sdata, double Sw) {
    PrivateRect* Rect = Sdata;
    Rect->w = Sw;
}
void setRectH(void* Sdata, double Sh) {
    PrivateRect* Rect = Sdata;
    Rect->h = Sh;
}
void setRectType(void* Sdata, char Stype){
    PrivateRect* Rect = Sdata;
    Rect->type = Stype;
}
void setRectArea(void* Sdata, double Sarea){
    PrivateRect* Rect = Sdata;
    Rect->area = Sarea;
}
void setRectProtec(void* Sdata, double Sprotec){
    PrivateRect* Rect = Sdata;
    Rect->protec = Sprotec;
}
void setRectVida(void* Sdata, int Svida){
    PrivateRect* Rect = Sdata;
    Rect->vida = Svida;
}