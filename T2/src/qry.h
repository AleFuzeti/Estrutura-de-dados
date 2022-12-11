#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void be(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, double agress, void* pont); //bomba de irradiação
double na(FILE* qry); //nivel de agressividade
void tp(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont); //torpedo
void tr(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt); //torpedo replicante
void se(void* anc, void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt); //seleciona
void sec(int nausCap[], void* ancoras, void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt);  //seleciona capitas
void mvh(int nausCap[],void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont); //mover horizontal
void mvv(int nausCap[],void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont); //mover vertical
void org(void* naus, FILE* qry, FILE* qrytxt);
#endif