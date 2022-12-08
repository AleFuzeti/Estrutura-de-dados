#include "system.h"
#include "lista.h"
#include "svg.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"
#include "cpt.h"

typedef void* Posic;


void printQry(double x, double y, Info i, double xc, double yc, double r, void *extra)
{
    FILE* qrysvg = extra;
    void* form = i;
    char type = checkForm(form);

    switch (type){
        case 'c':;
            int id = getCircId(form);
            if (id>0){
                fprintf(qrysvg, "<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" />\n", id, getCircX(form), getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form));
                fflush(qrysvg);
            }  
        break;
        case 'r':
            fprintf(qrysvg, "<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" />\n", getRectId(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form));
            fflush(qrysvg);    
        break;
        case 'l':
            fprintf(qrysvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"0.7\" stroke-width=\"1\" />\n", getLineId(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form), getLineCor(form));
            fflush(qrysvg);    
        break;
        case 't':;
            char a = getTextA(form);
            char* aux;
            if (a == 'i'){
                aux="start";
            }
            else if (a == 'm'){
                aux="middle";
            }
            else if (a == 'f'){
                aux="end";
            }
            fprintf(qrysvg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n", getTextId(form), getTextX(form), getTextY(form), getTextCorC(form), getTextCorP(form), aux, getTextText(form));
        break;
        fflush(qrysvg);            
    }
}

void printAnco(void* ancoras, FILE* qrysvg)
{
    for (void* node = getFirst(ancoras); node; node = getNext(ancoras, node))
    {
        void* form = get(ancoras, node);
        char type = checkForm(form);
        double x,y;
        char* cor;
        char* txto;

        switch (type){
            case 'c':
                x = getCircX(form);
                y = getCircY(form);
                fprintf(qrysvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1,75\" stroke=\"red\" stroke-width=\"1\" fill-opacity=\"1.0\" fill=\"red\" />\n", x, y);
                fflush(qrysvg);
            break;
            case 't':
                x = getTextX(form);
                y = getTextY(form);
                cor = getTextCorP(form);
                txto = getTextText(form);
                fprintf(qrysvg, "<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"0.4\" fill=\"%s\" text-anchor=\"start\">%s</text>\n", x, y, cor, cor, txto);
            break;
        }
    }   
}