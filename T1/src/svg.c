#include "system.h"
#include "lista.h"
#include "svg.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"

typedef void* Posic;

void printOnSvg(void*lista, char* file){

    int id;
    double x, x2, y, y2, r, w, h;
    char* corb;
    char* corp;
    char* cor;
    char* txto;

    void* form;
    void* node;

    FILE* svg = fopen(file, "w");

    if(svg == NULL){
        printf("erro ao abrir o .svg\n");
        exit(EXIT_FAILURE);
    }

    fprintf(svg, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    for (node = getFirst(lista); node; node = getNext(lista, node)){
        form = get(lista, node);
        char type = checkForm(form);

        switch (type){
            case 'c':
                form = get(lista, node);
                id = getCircId(form);
                x = getCircX(form);
                y = getCircY(form);
                r = getCircR(form);
                corb = getCircCorC(form);
                corp = getCircCorP(form);
                fprintf(svg, "<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" />\n", id, x, y, r, corb, corp);
                fflush(svg);    
                break;
            case 'r':
                form = get(lista, node);
                id = getRectId(form);
                x = getRectX(form);
                y = getRectY(form);
                w = getRectW(form);
                h = getRectH(form);
                corb = getRectCorC(form);
                corp = getRectCorP(form);
                fprintf(svg, "<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" />\n", id, x, y, w, h, corb, corp);
                fflush(svg);    
                break;
            case 'l':
                form = get(lista, node);
                id = getLineId(form);
                x = getLineX1(form);
                y = getLineY1(form);
                x2 = getLineX2(form);
                y2 = getLineY2(form);
                cor = getLineCor(form);
                fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"1\" />\n", id, x, y, x2, y2, cor);
                fflush(svg);    
                break;
            case 't':
                form = get(lista, node);
                id = getTextId(form);
                x = getTextX(form);
                y = getTextY(form);
                corb = getTextCorC(form);
                corp = getTextCorP(form);
                txto = getTextText(form);
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
                
                fprintf(svg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n", id, x, y, corb, corp, aux, txto);
                break;
                fflush(svg);            
        }
    }
    fprintf(svg, "</svg>\n");
    fclose(svg);
}

void printOnOpen(void* ancoras, void*lista, FILE* qrysvg){
    
    int id;
    double x, x2, y, y2, r, w, h;
    char* corb;
    char* corp;
    char* cor;
    char* txto;

    void* form;
    void* node;

    for (node = getFirst(lista); node; node = getNext(lista, node)){
        form = get(lista, node);
        char type = checkForm(form);

        switch (type){
            case 'c':
                form = get(lista, node);
                id = getCircId(form);
                if (id>0){
                    x = getCircX(form);
                    y = getCircY(form);
                    r = getCircR(form);
                    corb = getCircCorC(form);
                    corp = getCircCorP(form);
                    fprintf(qrysvg, "<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" />\n", id, x, y, r, corb, corp);
                    fflush(qrysvg);
                }  
                break;
            case 'r':
                form = get(lista, node);
                id = getRectId(form);
                x = getRectX(form);
                y = getRectY(form);
                w = getRectW(form);
                h = getRectH(form);
                corb = getRectCorC(form);
                corp = getRectCorP(form);
                fprintf(qrysvg, "<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" />\n", id, x, y, w, h, corb, corp);
                fflush(qrysvg);    
                break;
            case 'l':
                form = get(lista, node);
                id = getLineId(form);
                x = getLineX1(form);
                y = getLineY1(form);
                x2 = getLineX2(form);
                y2 = getLineY2(form);
                cor = getLineCor(form);
                fprintf(qrysvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" fill-opacity=\"0.7\" stroke-width=\"1\" />\n", id, x, y, x2, y2, cor);
                fflush(qrysvg);    
                break;
            case 't':
                form = get(lista, node);
                id = getTextId(form);
                x = getTextX(form);
                y = getTextY(form);
                corb = getTextCorC(form);
                corp = getTextCorP(form);
                txto = getTextText(form);
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
                
                fprintf(qrysvg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.7\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n", id, x, y, corb, corp, aux, txto);
                break;
                fflush(qrysvg);            
        }
    }
    
    for (node = getFirst(ancoras); node; node = getNext(ancoras, node)){
        form = get(lista, node);
        char type = checkForm(form);
        
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