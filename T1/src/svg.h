#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void printOnSvg(void* lista, char* file); //printa no svg
void printOnOpen(void* ancoras, void* lista, FILE* qrysvg); //printa no svg depois de ler o qry

#endif