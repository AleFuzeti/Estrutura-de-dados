#ifndef _SYSTEM_H
#define _SYSTEM_H
#include "libs.h"

int readParam(int argc, char** argv, void* paths); //le os parametros passados na linha de comando
void readPrintGeo(void* tree, void* paths); //le o .geo
void readQry(void *tree, void* paths); //le o .qry

char checkForm(void* n); //verifica qual forma é
int getFormId(void* n); //retorna o id
double getAreaGeral(void* n); //retorna a area de uma forma
void deleteForm(void* n); //apaga a forma correspondente
bool checkDentro(void* lista, void* n, double x, double y, double r);

   
// get e set da pontuacao
void* createPontos(); 
double getPontos(void* p);
void setPontos(void* p, double pont);
#endif