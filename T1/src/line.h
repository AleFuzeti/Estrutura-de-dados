#ifndef LINE_H
#define LINE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void* Crialinha(int id, char cor[], double x1, double y1, double x2, double y2); //Criar linha
bool checkLine(void* n); //Checar se é linha
void freeLine(void* data); //Liberar linha
void* callocDataL();//aloca memoria suficiente para uma struct de dados
 
//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
int getLineId(void* Sdata); // identificacao
char* getLineCor(void* Sdata); // cor de preenchimento
double getLineX1(void* Sdata);  // coordenada x
double getLineY1(void* Sdata); // coordenada y
double getLineX2(void* Sdata); // coordenada x
double getLineY2(void* Sdata); // coordenada y
double getLineProtec(void* Sdata); // protecao
double getLineArea(void* Sdata); // area
char getLineType(void* Sdata); // tipo
int getLineVida(void* Sdata); // vida
//bloco de set
void setLineId(void* Sdata, int Sid); // identificacao
void setLineCor(void* Sdata, char Scor[]); // cor de preenchimento
void setLineX1(void* Sdata, double Sx1);  // coordenada x
void setLineY1(void* Sdata, double Sy1); // coordenada y
void setLineX2(void* Sdata, double Sx2); // coordenada x
void setLineY2(void* Sdata, double Sy2); // coordenada y
void setLineArea(void* Sdata, double x, double y, double x2, double y2); // area
void setLineProtec(void* Sdata, double Sprotec); // protecao
void setLineType(void* Sdata, char Stype); // tipo
void setLineVida(void* Sdata, int Svida); // vida
#endif