#ifndef TEXT_H
#define TEXT_H

#include "libs.h"

#define TEXT_SVG "<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" text-anchor=\"%s\"><![CDATA[%s]]></text>\n"

void* CriaTexto(int id, char corC[], char corP[], double x, double y, char a, char text[]);//cria um texto
bool checkText(void* n);//verifica se o objeto é um texto
void freeText(void* data);//libera a memoria alocada para o texto
void* callocDataT();//aloca memoria suficiente para uma struct de dados

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
int getTextId(void* Sdata); //retorna o id do texto
char* getTextCorC(void* Sdata); //retorna a cor de contorno do texto
char* getTextCorP(void* Sdata); //retorna a cor de preenchimento do texto
double getTextX(void* Sdata); //retorna a coordenada x do texto
double getTextY(void* Sdata); //retorna a coordenada y do texto
char getTextA(void* Sdata); //retorna a alinhamento do texto
char* getTextText(void* Sdata); //retorna o texto
char getTextType(void* Sdata); //retorna o tipo do objeto
double getTextProtec(void* Sdata); //retorna a proteção do objeto
int getTextVida(void* Sdata); //retorna a vida do objeto
double getTextArea(void* Sdata); //retorna a area do objeto

//bloco de set
void setTextId(void* Sdata, int Sid);   //identificacao
void setTextCorC(void* Sdata, char ScorC[]); //cor de contorno
void setTextCorP(void* Sdata, char ScorP[]); //cor de preenchimento
void setTextX(void* Sdata, double Sx); //coordenada x
void setTextY(void* Sdata, double Sy); //coordenada y
void setTextA(void* Sdata, char Sa); //alinhamento
void setTextText(void* Sdata, char Stext[]); //texto
void setTextType(void* Sdata, char Stype); //tipo do objeto
void setTextProtec(void* Sdata, double Sprotec); //proteção do objeto
void setTextArea(void* Sdata, double Sarea); //area do objeto
void setTextVida(void* Sdata, int Svida); //vida do objeto
#endif