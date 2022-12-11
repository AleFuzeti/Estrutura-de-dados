#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lista.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"
#include "system.h"
#include "path.h" 
#include "svg.h"
#include "qry.h"

typedef void* Lista;

int main (int argc, char** argv){
    
    //cria os paths todos
    void* paths = createAllPaths();
    if(readParam(argc, argv, paths) == -1){// le os parametros
        return 0;
    } 
    Lista lista = createLista(-1); //cria a lista
    readGeo(lista, paths);// le o .geo
    printOnSvg(lista, getBsdGeoSvg(paths)); //printa no svg

    if(getQryArq(paths)){   
        FILE* qrysvg = fopen(getBsdGeoQrySvg(paths), "w");
        fprintf(qrysvg, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");
        FILE* qrytxt = fopen(getBsdGeoQryTxt(paths), "w");

        Lista naus = createLista(-1);  //cria a lista de naus
        Lista ancoras = createLista(-1); //cria a lista de ancoras
        void* pon = createPontos(); //cria pontos
        setPontos(pon, 0); //seta os pontos para 0

        readQry(naus, ancoras, lista, paths, qrysvg, qrytxt, pon); //le o .qry
        printOnOpen(ancoras, lista, qrysvg); //printa no svg
        fprintf(qrysvg, "</svg>\n");

        fprintf(qrytxt, "\nPontuacao maxima:%.2lf\n",getPontos(pon));
        //printf("\nPontuacao maxima: %.2lf\n",getPontos(pon));
        fclose(qrysvg);
        fclose(qrytxt);

        killLista(ancoras); // mata a lista de ancoras
        killLista(naus); // mata a lista de naus
        free(pon); // mata os pontos
    }
        killLista(lista); // mata a lista

    freee(paths);
    return 0;
}