#ifndef SVG_H
#define SVG_H

#include "libs.h"
#include "cpt.h"

void printQry(double x, double y, Info i, double xc, double yc, double r, void *extra);
void printAnco(void* ancoras, FILE* qrysvg);

#endif