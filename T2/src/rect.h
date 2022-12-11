#ifndef RECT_H
#define RECT_H
 
#include "libs.h"

#define RECT_SVG "<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" fill-opacity=\"75%%\"/>\n"

void* CriaRetangulo(int id, char corC[], char corP[], double x, double y, double w, double h);//cria um retangulo
bool checkRect(void* n);//verifica se o elemento é um retangulo
void freeRect(void* data);//libera a memoria alocada para o retangulo
void* callocDataR();//aloca memoria suficiente para uma struct de dados

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
int getRectId(void* Sdata); // identificacao
char* getRectCorC(void* Sdata); // cor de preenchimento
char* getRectCorP(void* Sdata); // cor de borda
double getRectX(void* Sdata);   // coordenada x
double getRectY(void* Sdata);   // coordenada y
double getRectW(void* Sdata);   // largura
double getRectH(void* Sdata);   // altura
double getRectArea(void* Sdata); // area
char getRectType(void* Sdata); // tipo
double getRectProtec(void* Sdata); // protecao
int getRectVida(void* Sdata); // vida

//bloco de set
void setRectId(void* Sdata, int Sid);      // identificacao
void setRectCorC(void* Sdata, char ScorC[]);    // cor de preenchimento
void setRectCorP(void* Sdata, char ScorP[]);    // cor de borda
void setRectX(void* Sdata, double Sx);   // coordenada x
void setRectY(void* Sdata, double Sy);   // coordenada y
void setRectW(void* Sdata, double Sw);   // largura
void setRectH(void* Sdata, double Sh);   // altura
void setRectType(void* Sdata, char Stype); // tipo
void setRectProtec(void* Sdata, double Sprotec); // protecao
void setRectVida(void* Sdata, int Svida); // vida
#endif