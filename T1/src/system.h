#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int readParam(int argc, char** argv, void* paths); //le os parametros passados na linha de comando
void printParam(void* paths); //printa os parametros
void readGeo(void* lista, void* paths); //le o .geo
void readQry(void* naus, void* ancoras, void *lista, void* paths, FILE* qrysvg, FILE* qrytxt, void* pon); //le o .qry
void* createAllPaths(); //cria os paths
char* prepareDir(char* dir); //prepara o diretorio

void freee(void* paths);//da free nos paths
char checkForm(void* n); //verifica qual forma é
void deleteForm(void* n); //apaga a forma correspondente
bool checkDentro(void* lista, void* n, double x, double y, double r);


//a partir daqui, sao os gets e sets de todos os tratamentos especificados no nome
void setQryFull (void* path, char* qryfull);
void setGeoFull (void* path, char* geofull);
void setQryName(void* path, char* qryname);
void setGeoName(void* path, char* geoname);
void setBed (void* path, char* bed);
void setBsd(void* path, char* bsd);
void setGeoArq(void* path, char* geoarq);
void setQryArq(void* path, char* qryarq);
void setBsdGeoSvg(void* path, char* bsdgeosvg);
void setBsdGeoQrySvg(void* path, char* bsdgeoqrysvg);
void setBsdGeoQryTxt(void* path, char* bsdgeoqrytxt);

char* getQryFull(void* path);
char* getGeoFull(void* path);char* getQryName(void* path);
char* getGeoName(void* path);
char* getBed(void* path);
char* getBsd(void* path);
char* getGeoArq(void* path);
char* getQryArq(void* path);
char* getBsdGeoSvg(void* path);
char* getBsdGeoQrySvg(void* path);
char* getBsdGeoQryTxt(void* path);
   
// get e set da pontuacao
void* createPontos(); 
double getPontos(void* p);
void setPontos(void* p, double pont);
#endif