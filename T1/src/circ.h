#ifndef CIRC_H
#define CIRC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef void* Circ;

void* CriaCirculo(int id, char corC[], char corP[], double x, double y, double r);//cria um circulo

bool checkCirc(void* n);//verifica se o elemento é um circulo
void freeCirc(void* data); //desaloca memoria de um circulo
void* callocDataC();//aloca memoria suficiente para uma struct de dados

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
int getCircId(void* Sdata); // identificacao
char* getCircCorC(void* Sdata); // cor de preenchimento
char* getCircCorP(void* Sdata); // cor de borda
double getCircX(void* Sdata);   // coordenada x
double getCircY(void* Sdata);   // coordenada y
double getCircR(void* Sdata);   // raio
double getCircArea(void* Sdata); // area
double getCircProtec(void* Sdata); // protecao
char getCircType(void* Sdata); // tipo
int getCircVida(void* Sdata); // vida
//bloco de set 
void setCircId(void* Sdata, int Sid); // identificacao
void setCircCorC(void* Sdata, char ScorC[]); // cor de preenchimento
void setCircCorP(void* Sdata, char ScorP[]); // cor de borda
void setCircX(void* Sdata, double Sx); // coordenada x
void setCircY(void* Sdata, double Sy); // coordenada y
void setCircR(void* Sdata, double Sr); // raio
void setCircProtec(void* Sdata, double Sprotec); // protecao
void setCircType(void* Sdata, char Stype); // tipo
void setCircArea(void* Sdata, double Sarea); // area
void setCircVida(void* Sdata, int Svida); // vida
#endif 