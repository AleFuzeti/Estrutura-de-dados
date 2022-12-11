#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "circ.h"
#include "rect.h"
#include "text.h"
#include "line.h"
#include "system.h"
#include "paths.h" 
#include "svg.h"
#include "qry.h"
#include "lista.h"

void be(void* anc, void* lista, FILE* qry, FILE* qrysvg, FILE* qrytxt, double agress, void* pont){
    double bex, bey, ber;
    void* list =  lista;
    void* node;
    void* aux;
    fscanf(qry, "%lf %lf %lf", &bex, &bey, &ber);
    
    for (node = getFirst(lista); node; node = getNext(lista, node)){
        
        if (node == getFirst(lista)){
            aux = CriaCirculo(0, "null", "null", 0, 0, 1);
            insertBefore(list, node, aux);
            aux = getPrevious(list, node);
        } else aux = getPrevious(list, node);

        void* form = get(list, node);
        int id;
        double x, x2, y, y2, r, w, h, auxX, auxY, protec;
        char corb[20], corp[20], cor[20];//, txto[100];
        double areab = ber*ber*3.14; 
        //imprime circulo be
        fprintf(qrysvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" stroke-width=\"1\" stroke-dasharray =\"5,3\" fill-opacity=\"0.0\" fill=\"null\" />\n", bex, bey, ber);
        
        char type = checkForm(form);
        switch(type){ //verifica se foram selecionados
            case 'r':
            x = getRectX(form);
            y = getRectY(form);
            w = getRectW(form);
            h = getRectH(form);
            id = getRectId(form);
            protec = getRectProtec(form);
            strcpy(corp, getRectCorP(form));
            strcpy(corb, getRectCorC(form));
            if  (checkDentro(list, form, bex, bey, ber)){
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                fprintf(qrytxt, "be rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, w, h, corb, corp, protec);

                insert(anc, anco);
                protec = protec - (agress*getRectArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0){
                    fprintf(qrytxt, "rect id=%d REMOVIDA, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, w, h, corb, corp, protec);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+90);
                } else setRectProtec(form,protec);
            }
                break;

            case 'c':
            x = getCircX(form);
            y = getCircY(form);
            r = getCircR(form);
            id = getRectId(form);
            protec = getCircProtec(form);
            strcpy(corp, getCircCorP(form));
            strcpy(corb, getCircCorC(form));
            if  (checkDentro(list, form, bex, bey, ber)){
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                if (id!=0)
                fprintf(qrytxt, "be circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, r, corb, corp, protec);
                
                insert(anc, anco);        
                protec = protec - (agress*getCircArea(form)/(areab)); //diminuição do nivel de protecao   
                if (protec <= 0){
                    fprintf(qrytxt, "circ id=%d REMOVIDA, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, r, corb, corp, protec);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+75);
                } else setCircProtec(form,protec);
            }
                break;

            case 'l':
            id = getLineId(form);
            x = getLineX1(form);
            y = getLineY1(form);
            x2 = getLineX2(form);
            y2 = getLineY2(form);
            protec = getLineProtec(form);
            strcpy(cor, getLineCor(form));

            if  (checkDentro(list, form, bex, bey, ber)){
                if (x<x2){
                    auxX = x;
                    auxY = y;
                } else if(x2<x){
                    auxX = x2;
                    auxY = y2;
                } else if(y<y2){
                    auxX = x;
                    auxY = y;
                } else{
                    auxX = x2;
                    auxY = y2;
                }
                void* anco = CriaCirculo(id, "null", "null", auxX, auxY, 1);
                fprintf(qrytxt, "be line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf\n", id, x, y, x2, y2, cor, protec);

                insert(anc, anco);
                protec = protec - (agress*getLineArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0){
                    fprintf(qrytxt, "line id=%d REMOVIDA, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf\n", id, x, y, x2, y2, cor, protec);
                    remover(list, node);
                    node = aux;
                setPontos(pont,getPontos(pont)+50);
                } else setLineProtec(form,protec);
            }
                break;

            case 't':
            id = getTextId(form);
            x = getTextX(form);
            y = getTextY(form);
            protec = getTextProtec(form);
            strcpy(corp, getTextCorP(form));
            strcpy(corb, getTextCorC(form));
            
            if  (checkDentro(list, form, bex, bey, ber)){
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                fprintf(qrytxt, "be text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, corb, corp, protec);

                insert(anc, anco);
                protec = protec - (agress*getTextArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0){
                    fprintf(qrytxt, "text id=%d REMOVIDA, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, corb, corp, protec);
                    remover(list, node);
                    node = aux;
                setPontos(pont,getPontos(pont)+30);
                } else setTextProtec(form,protec);
            }
                break;
            default:
            printf("error ");
            break;  
        }
    }
}

double na(FILE* qry){
    double aux;
    fscanf(qry, "%lf", &aux);
    return aux;
}

void tp(void* anc, void* Lista, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont){
    void* list =  Lista;
    void* node;
    void* aux;
    bool hit = false;
    int i = 0;

    double tpx, tpy;
    fscanf(qry, "%lf %lf", &tpx, &tpy);

    for (node = getFirst(list); node; node = getNext(list,node)){
        
        if (node == getFirst(list)){
            aux = CriaCirculo(0, "null", "null", 0, 0, 1);
            insertBefore(list, node, aux);
            aux = getPrevious(list, node);
        } else aux = getPrevious(list, node);
            
        void* form = get(list, node);
        int id;
        double x, x2, y, y2, r, w, h, auxX, auxY, protec;
        char corb[20], corp[20], cor[20], txto[100] = "*";

        char tipo = checkForm(form);
        switch (tipo){
            case 'r':
            x = getRectX(form);
            y = getRectY(form);
            w = getRectW(form);
            h = getRectH(form);
            id = getRectId(form);
            protec = getRectProtec(form);
            strcpy(corp, getRectCorP(form));
            strcpy(corb, getRectCorC(form));
            if  (tpx >= x && tpx <= x + w && tpy >= y && tpy <= y + h){
                i++;
                int vida = getRectVida(form);
                vida--;
                setRectVida(form, vida);

                if(vida == 0){
                    fprintf(qrytxt, "rect id=%d REMOVIDA, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x, y, w, h, corb, corp, protec, vida);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+(90/((w*h)/5))); //pontos
                } else fprintf(qrytxt, "rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, w, h, corb, corp, protec,vida,3-vida);
                
                hit = true;
            }
            break;
            case 'c':
            x = getCircX(form);
            y = getCircY(form);
            r = getCircR(form);
            id = getRectId(form);
            protec = getCircProtec(form);
            strcpy(corp, getCircCorP(form));
            strcpy(corb, getCircCorC(form));
            
            if  (tpx >= x - r && tpx <= x + r && tpy >= y - r && tpy <= y + r){
                i++;
                int vida = getCircVida(form);
                vida--;
                setCircVida(form, vida);

                if(vida == 0){
                    fprintf(qrytxt, "circ id=%d REMOVIDA, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n, vida=%d", id, x, y, r, corb, corp, protec, vida);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+(75/((r*r*3.14)/5))); //pontos
                } else fprintf(qrytxt, "circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, r, corb, corp, protec,vida,2-vida);
                
                hit = true;
            }
            break;
            case 'l':
            id = getLineId(form);
            x = getLineX1(form);
            y = getLineY1(form);
            x2 = getLineX2(form);
            y2 = getLineY2(form);
            protec = getLineProtec(form);
            strcpy(cor, getLineCor(form));
            
            if(x2<x){
                auxX = x2;
                auxY = y2;
                x2 = x;
                y2 = y;
                x = auxX;
                y = auxY;
            } else if(y2<y){
                auxX = x2;
                auxY = y2;
                x2 = x;
                y2 = y;
                x = auxX;
                y = auxY;
            }

            //equação da reta
            double m = (y2 - y)/(x2 - x);
            // yq - y = m(xq - x)
            
            if (tpy - y == m*(tpx - x) && tpx>= x && tpx <= x2 && tpy >= y && tpy <= y2){
                i++;
                int vida = getLineVida(form);
                vida--;
                setLineVida(form, vida);

                if(vida == 0){
                    fprintf(qrytxt, "line id=%d REMOVIDA, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d\n", id, x, y, x2, y2, cor, protec, vida);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+150); //pontos
                } else fprintf(qrytxt, "line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, x2, y2, cor, protec,vida,1-vida);
                
                hit = true;
            }
            break;
            case 't':
            id = getTextId(form);
            x = getTextX(form);
            y = getTextY(form);
            protec = getTextProtec(form);
            strcpy(corp, getTextCorP(form));
            strcpy(corb, getTextCorC(form));
            
            if (tpx == x && tpy == y){
                i++;
                int vida = getTextVida(form);
                vida--;
                setTextVida(form, vida);

                if(vida == 0){
                    fprintf(qrytxt, "text id=%d REMOVIDA, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x, y, corb, corp, protec, vida);
                    remover(list, node);
                    node = aux;
                    setPontos(pont,getPontos(pont)+500); //pontos
                } else fprintf(qrytxt, "text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, corb, corp, protec,vida,1-vida);
                
                hit = true;
            }
            break;

            default:
            printf("error\n");
            break;
        }

        if (node == getLast(list) ){
            if (hit == false){
                fprintf(qrytxt, "AGUA\n");
                void* aste = CriaTexto (0, "black","black", tpx, tpy, 'm', "*"); 
                insert(anc, aste);
            } else {
                if(i>1){
                    char aux[10];
                    sprintf (aux, "%d", i);
                    strcat(txto, aux);
                }
                void* aste = CriaTexto (0, "red","red", tpx, tpy, 'm', txto);
                insert(anc, aste);
            }
        }
    }

}

void tr(void* anc, void* Lista, FILE* qry, FILE* qrysvg, FILE* qrytxt){
    void* list = Lista;
    void* node;
    bool hit = false;

    double trx, try, dx, dy;
    int id;    
    fscanf(qry, "%lf %lf %lf %lf %d", &trx, &try, &dx, &dy, &id);
    
    for (node = getFirst(list); node; node = getNext(list,node)){
        void* form = get(list, node);
        void* newform;
        double x, x2, y, y2, r, w, h, auxX, auxY, protec;
        int vida;
        char corb[20], corp[20], cor[20], a, txto[100], txt[2] = "@";

        char tipo = checkForm(form);
        switch(tipo){ // verifica se acertou e cria os clones
            case 'r':
            x = getRectX(form);
            y = getRectY(form);
            w = getRectW(form);
            h = getRectH(form);
            protec = getRectProtec(form);
            strcpy(corp, getRectCorP(form));
            strcpy(corb, getRectCorC(form));
            vida = getRectVida(form);
            
            if  (trx >= x && trx <= x + w && try >= y && try <= y + h){
                newform = CriaRetangulo(id, corp, corb, x+dx, y+dy, w, h);
                setRectProtec(newform, protec);
                setRectVida(newform, getRectVida(form));
                
                insert(list, newform);
                
                fprintf(qrytxt, "tr rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), x, y, w, h, corb, corp, protec, vida);
                fprintf(qrytxt, "rect id=%d CLONE, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", id, x+trx, y+try, w+trx, h+try, corp, corb, protec, vida);
                id++;

                hit = true;//interroga
            }
            break;

            case 'c':
            x = getCircX(form);
            y = getCircY(form);
            r = getCircR(form);
            protec = getCircProtec(form);
            strcpy(corp, getCircCorP(form));
            strcpy(corb, getCircCorC(form));
            vida = getCircVida(form);

            if  (trx >= x - r && trx <= x + r && try >= y - r && try <= y + r){
                newform = CriaCirculo(id, corp, corb, x+dx, y+dy, r);
                setCircProtec(newform, protec);
                setCircVida(newform, getCircVida(form));

                insert(list, newform);
                
                fprintf(qrytxt, "tr circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), x, y, r, corb, corp, protec, vida);
                fprintf(qrytxt, "circ id=%d CLONE, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, r, corp, corb, protec, vida);
                id++;

                hit = true;
            }
            break;

            case 'l':
            x = getLineX1(form);
            y = getLineY1(form);
            x2 = getLineX2(form);
            y2 = getLineY2(form);
            protec = getLineProtec(form);
            strcpy(cor, getLineCor(form));
            vida = getLineVida(form);

            if(x2<x){
                auxX = x2;
                auxY = y2;
                x2 = x;
                y2 = y;
                x = auxX;
                y = auxY;
            } else if(y2<y){
                auxX = x2;
                auxY = y2;
                x2 = x;
                y2 = y;
                x = auxX;
                y = auxY;
            }

            //equação da reta
            double m = (y2 - y)/(x2 - x);
            // yq - y = m(xq - x)

            if (try - y == m*(trx - x) && trx>= x && trx <= x2 && try >= y && try <= y2){
                newform = Crialinha(id, cor, x+dx, y+dy, x2+dx, y2+dy);
                setLineProtec(newform, protec);
                setLineVida(newform, getLineVida(form));

                insert(list, newform);
        
                fprintf(qrytxt, "tr line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x, y, x2, y2, cor, protec, vida);
                fprintf(qrytxt, "line id=%d CLONE, x1=%.2lf, y1=%.2lf,  x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, x2+trx, y2+try, cor, protec, vida);
                id++;
                hit = true;
            }
                break;

            case 't':
            x = getTextX(form);
            y = getTextY(form);
            protec = getTextProtec(form);
            a = getTextA(form);
            strcpy(corp, getTextCorP(form));
            strcpy(corb, getTextCorC(form));
            strcpy(txto, getTextText(form));

            char aux[7];
            if (a == 'i'){
                strcpy(aux,"start");
            }
            else if (a == 'm'){
                strcpy(aux,"middle");
            }
            else if (a == 'f'){
                strcpy(aux,"end");
            }
            
            if (x == trx && y == try){
                newform = CriaTexto(id, corp, corb, x+dx, y+dy, a, txto);
                setTextProtec(newform, protec);
                setTextVida(newform, getTextVida(form));

                insert(list, newform);

                fprintf(qrytxt, "tr text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, alinhamento=%s, texto=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), x, y, corb, corp, aux, txto, protec, vida);
                fprintf(qrytxt, "text id=%d CLONE, x=%.2lf, y=%.2lf, corb=%s, corp=%s, a=%c, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, corp, corb, a, protec, vida);
                id++;

                hit = true;

            }
                break;
            default:
            printf("error \n");
        }

        if (node == getLast(list) ){
            if (hit == false){
                void* arro = CriaTexto (0, "black","black", trx, try, 'm', txt); 
                insert(anc, arro);
            } else {
                void* arro = CriaTexto (0, "red","red", trx, try, 'm', txt);
                insert(anc, arro);
            }
        }
    }
}

void se(void* nau, void* list, FILE* qry, FILE* qrysvg, FILE* qrytxt){
    void* Lista = list;
    void* node;
    void* form;
    int id;
    
    fscanf(qry, "%d", &id);

    for (node = getFirst(Lista); node; node=getNext(Lista, node)){
        form = get(Lista, node);
        void* form2;
        char tipo = checkForm(form);
        switch (tipo){
            case 'r':
            if (id == getRectId(form)){
                fprintf(qrytxt, "se rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                form2 = CriaRetangulo(getRectId(form), getRectCorC(form), getRectCorP(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form));
                insert(nau, form2);
            }
            break;
            case 'c':
            if (id == getCircId(form)){
                fprintf(qrytxt, "se circle id=%d, cx=%.2lf, cy=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), getCircX(form), getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                form2 = CriaCirculo(getCircId(form), getCircCorC(form), getCircCorP(form), getCircX(form), getCircY(form), getCircR(form));
                insert(nau, form2);
            }
            break;
            case 'l':
            if (id == getLineId(form)){
                fprintf(qrytxt, "se line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form), getLineCor(form), getLineProtec(form), getLineVida(form));
                form2 = Crialinha(getLineId(form), getLineCor(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form));
                insert(nau, form2);
            }
            break;
            case 't':
            if (id == getTextId(form)){
                fprintf(qrytxt, "se text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, alinhamento=%c, texto=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), getTextX(form), getTextY(form), getTextCorC(form), getTextCorP(form), getTextA(form), getTextText(form), getTextProtec(form), getTextVida(form));
                form2 = CriaTexto(getTextId(form), getTextCorC(form), getTextCorP(form), getTextX(form), getTextY(form), getTextA(form), getTextText(form));
                insert(nau, form2);

            }
            break;
        }
    }
}

void sec (int nausCap[], void* nau, void* list, FILE* qry, FILE* qrysvg, FILE* qrytxt){
    void* Lista = list;
    void* node;
    void* form;
    int id, j;
    
    fscanf(qry, "%d %d", &id, &j);

    for (node = getFirst(Lista);node;node=getNext(Lista, node)){
        form = get(Lista, node);
        void* form2;
        char tipo = checkForm(form);
        switch (tipo){
            case 'r':
            if (id == getRectId(form)){
                fprintf(qrytxt, "sec rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                nausCap[j] = id;
                form2 = CriaRetangulo(getRectId(form), getRectCorC(form), getRectCorP(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form));
                insert(nau, form2);
            }
            break;
            case 'c':
            if (id == getCircId(form)){
                fprintf(qrytxt, "sec circle id=%d, cx=%.2lf, cy=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), getCircX(form), getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                nausCap[j] = id;
                form2 = CriaCirculo(getCircId(form), getCircCorC(form), getCircCorP(form), getCircX(form), getCircY(form), getCircR(form));
                insert(nau, form2);
            }
            break;
            case 'l':
            if (id == getLineId(form)){
                fprintf(qrytxt, "sec line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form), getLineCor(form), getLineProtec(form), getLineVida(form));
                nausCap[j] = id;
                form2 = Crialinha(getLineId(form), getLineCor(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form));
                insert(nau, form2);
            }
            break;
            case 't':
            if (id == getTextId(form)){
                fprintf(qrytxt, "sec text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, alinhamento=%c, texto=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), getTextX(form), getTextY(form), getTextCorC(form), getTextCorP(form), getTextA(form), getTextText(form), getTextProtec(form), getTextVida(form));
                nausCap[j] = id;
                form2 = CriaTexto(getTextId(form), getTextCorC(form), getTextCorP(form), getTextX(form), getTextY(form), getTextA(form), getTextText(form));
                insert(nau, form2);
            }
            break;
        }
    }
    return;
}

void mvv (int nausCap[], void* nau, void* list, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont){
    void* Lista = list;
    void* node,* node2,* form,* form2,* form3;
    int i = 0, j, k;
    char aux;
    double dy;

    fscanf(qry, "%d %d %lf", &j, &k, &dy);
    int id = nausCap[j];

    for(node = getFirst(nau);node;node = getNext(nau,node)){
        form = get(nau, node);
        char tipo = checkForm(form);
        switch (tipo){
            case 'r':
            if (id == getRectId(form)){
                node2 = node;
            }
            break;
            case 'c':
             if (id == getCircId(form)){
                node2 = node;
            }
            break;
            case 'l':
            if (id == getLineId(form)){
                node2 = node;
            }
            break;
            case 't':
            if (id == getTextId(form)){
                node2 = node;
            }
            break;
            default:
                printf("ERRO\n");
            break;
        }
    }

    if (k > 0){
        for(node = node2;node;node=getNext(nau,node)){
            if (i==k){
            node2 = node;
            }
            i++;
        }
    } else {
        for(node = node2;node;node=getPrevious(nau,node)){
            if (i==k){
            node2 = node;
            }
            i--;
        }
    }

    form = get(nau, node2);
    char tipo = checkForm(form);
    int auxid;
    switch (tipo){
        case 'r':
            auxid = getRectId(form);
        break;
        case 'c':
            auxid = getCircId(form);
        break;
        case 'l':
            auxid = getLineId(form);
        break;
        case 't':
            auxid = getTextId(form);
        break;
    }
    void* nodeL;
    for (node = getFirst(Lista);node;node=getNext(Lista, node)){
        form2 = get(Lista, node);
        char type = checkForm(form2);
        switch (type){
            case 'r':
            if (auxid == getRectId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 'c':
            if (auxid == getCircId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 'l':
            if (auxid == getLineId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 't':
            if (auxid == getTextId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
        }
    }
    switch (tipo){
        case 'r':;
            double yr = getRectY(form);
            yr = yr + dy;
            setRectY(form, yr);
            setRectY(form3, yr);
            fprintf(qrytxt, "retangulo movido verticalmente id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), getRectX(form), yr, getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
            aux='r';
        break;
        case 'c':;
            double yc = getCircY(form);
            yc = yc + dy;
            setCircY(form, yc);
            setCircY(form3, yc);
            fprintf(qrytxt, "circ movido verticalmente id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), getCircX(form), yc, getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
            aux='c';
        break;
        case 'l':;
            double y1l = getLineY1(form);
            double y2l = getLineY2(form);
            y1l = y1l + dy;
            y2l = y2l + dy;
            setLineY1(form, y1l);
            setLineY2(form, y2l);
            setLineY1(form3, y1l);
            setLineY2(form3, y2l);
            fprintf(qrytxt, "line movida verticalmente id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), getLineX1(form), y1l, getLineX2(form), y2l, getLineCor(form), getLineProtec(form), getLineVida(form));
            aux='l';
        break;
        case 't':;
            double yt = getTextY(form);
            yt = yt + dy;
            setTextY(form, yt);
            setTextY(form3, yt);
            fprintf(qrytxt, "text movido verticalmente id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), getTextX(form), yt, getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
            aux='t';
        break;
    }
    for(node = getFirst(Lista);node;node=getNext(Lista,node)){
        form2 = get(Lista, node);
        char tipo = checkForm(form2);

        if (tipo == 't'){
            if (strstr(getTextText(form2), "#" ) != NULL){
                double xt = getTextX(form2);
                double yt = getTextY(form2);
                double aux1, aux2;
                double x,y;
                switch (aux){
                    case 'c':;
                        x = getCircX(form);
                        y = getCircY(form);
                        double r = getCircR(form);
                        if (dy>0){
                            aux1 = y;
                            aux2 = y-dy;
                        } else {
                            aux1 = y-dy;
                            aux2 = y;
                        }
                        if (yt >= aux2-r && yt <= aux1+r && xt >= x-r && xt <= x+r){
                            fprintf(qrytxt, "circ destruido id=%d, cx=%.2lf, cy=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), x, y, r, getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(Lista, nodeL);
                            remover(nau, node2);
                            setPontos(pont,getPontos(pont)+(75/((r*r*3.14)/5)));
                            aux = ' ';
                        }
                    break;
                    case 'r':;
                        x = getRectX(form);
                        y = getRectY(form);
                        double w = getRectW(form);
                        double h = getRectH(form);
                        if (dy>0){
                            aux1 = y;
                            aux2 = y-dy;
                        } else {
                            aux1 = y-dy;
                            aux2 = y;
                        }
                        if (yt >= aux2 && yt <= aux1+h && xt >= x && xt <= x+w){
                            fprintf(qrytxt, "rect destruido id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), x, y, w, h, getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+(90/((w*h)/5)));         
                            aux = ' ';
                        }
                    break;
                    case 'l':;
                        double x1 = getLineX1(form);
                        double y1 = getLineY1(form);
                        double x2 = getLineX2(form);
                        double y2 = getLineY2(form);
                        double aux3, aux4;
                        if (dy>0){
                            aux1 = y1;
                            aux2 = y1-dy;
                            aux3 = y2;
                            aux4 = y2-dy;
                        } else {
                            aux1 = y1-dy;
                            aux2 = y1;
                            aux3 = y2-dy;
                            aux4 = y2;
                        }
                        if (((yt >= aux2 && yt <= aux1)||(yt >= aux4 && yt <= aux3)) && (xt >= aux4 && xt <= aux3)){
                            fprintf(qrytxt, "line destruido id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x1, y1, x2, y2, getLineCor(form), getLineProtec(form), getLineVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+150);
                            aux = ' ';
                        }
                    break;
                    case 't':;
                        x = getTextX(form);
                        y = getTextY(form);
                        if (dy>0){
                            aux1 = y;
                            aux2 = y-dy;
                        } else {
                            aux1 = y-dy;
                            aux2 = y;
                        }
                        if (yt >= aux2 && yt <= aux1 && xt >= x && xt <= x){
                            fprintf(qrytxt, "text destruido id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), x, y, getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+500);
                            aux = ' ';
                        }
                    break;
                    default:
                    break;
                } 
            }
        }   
    }
    return;
}

void mvh (int nausCap[], void* nau, void* list, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont){
    void* Lista = list;
    void* node,* node2,* form,* form2,* form3;
    int i = 0, j, k;
    char aux;
    double dx;

    fscanf(qry, "%d %d %lf", &j, &k, &dx);
    int id = nausCap[j];

    for(node = getFirst(nau); node; node = getNext(nau,node)){
        form = get(nau,node); 
        char tipo = checkForm(form);
        switch (tipo){
            case 'c':
                if (id == getCircId(form)){
                node2 = node;
                }
            break;
            case 'r':
                if (id == getRectId(form)){
                node2 = node;
                }
            break;
            case 'l':
                if (id == getLineId(form)){
                node2 = node;
                }
            break;
            case 't':
                if (id == getTextId(form)){
                node2 = node;
                }
            break;
            default:
                printf("erro \n");
            break;
        }
    }
    
    if(k > 0){
        for(node = node2;node;node=getNext(nau,node)){
            if (i==k){
            node2 = node;
            }
            i++;
        }
    } else {
        for(node = node2;node;node=getPrevious(nau,node)){
            if (i==k){
            node2 = node;
            }
            i--;
        }
    }
    form = get(nau,node2);
    char tipo = checkForm(form);
    int auxid;
    switch (tipo){
        case 'r':
            auxid = getRectId(form);
        break;
        case 'c':
            auxid = getCircId(form);
        break;
        case 'l':
            auxid = getLineId(form);
        break;
        case 't':
            auxid = getTextId(form);
        break;
    }
    void* nodeL;
    for (node = getFirst(Lista);node;node=getNext(Lista, node)){
        form2 = get(Lista, node);
        char type = checkForm(form2);
        switch (type){
            case 'r':
            if (auxid == getRectId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 'c':
            if (auxid == getCircId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 'l':
            if (auxid == getLineId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
            case 't':
            if (auxid == getTextId(form2)){
                form3 = form2;
                nodeL = node;
            }
            break;
        }
    }
    switch(tipo){
        case 'r':;
            double xr = getRectX(form);
            xr = xr + dx;
            setRectX(form, xr);
            setRectX(form3, xr);
            fprintf(qrytxt, "rect movido horizontalmente id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), xr, getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
            aux='r';
        break;
        case 'c':;
            double xc = getCircX(form);
            xc = xc + dx;
            setCircX(form, xc);
            setCircX(form3, xc);
            fprintf(qrytxt, "circ movido horizontalmente id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), xc, getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
            aux='c';
        break;
        case 'l':;
            double x1l = getLineX1(form);
            double x2l = getLineX2(form);
            x1l = x1l + dx;
            x2l = x2l + dx;
            setLineX1(form, x1l);
            setLineX2(form, x2l);
            setLineX1(form3, x1l);
            setLineX2(form3, x2l);
            fprintf(qrytxt, "line movido horizontalmente id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x1l, getLineY1(form), x2l, getLineY2(form), getLineCor(form), getLineProtec(form), getLineVida(form));
            aux='l';
        break;
        case 't':;
            double xt = getTextX(form);
            xt = xt + dx;
            setTextX(form, xt);
            setTextX(form3, xt);
            fprintf(qrytxt, "text movido horizontalmente id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), xt, getTextY(form), getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
            aux='t';
        break;
    }
    for(node = getFirst(Lista);node;node=getNext(Lista,node)){
        form2 = get(Lista, node);
        char tipo = checkForm(form2);
    
        if (tipo == 't'){
            if (strstr(getTextText(form2), "#" ) != NULL){
                double xt = getTextX(form2);
                double yt = getTextY(form2);
                double aux1, aux2;
                double x,y;
                switch (aux){
                    case 'c':;
                    x = getCircX(form);
                    y = getCircY(form);
                    double r = getCircR(form);
                    if (dx>0){
                        aux1 = x;
                        aux2 = x-dx;
                    } else {
                        aux1 = x-dx;
                        aux2 = x;
                    }
                    if (yt >= y-r && yt <= y+r && xt >= aux2-r && xt <= aux1+r){
                        fprintf(qrytxt, "circulo destruido id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), x, y, r, getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                        fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                        setTextText(form2, "$");
                        remover(nau, node2); 
                        remover(Lista, nodeL);
                        setPontos(pont,getPontos(pont)+(75/((r*r*3.14)/5)));
                        aux = ' ';
                    }
                    break;
                    case 'r':;
                        x = getRectX(form);
                        y = getRectY(form);
                        double w = getRectW(form);
                        double h = getRectH(form);
                        if (dx>0){
                            aux1 = x;
                            aux2 = x-dx;
                        } else {
                            aux1 = x-dx;
                            aux2 = x;
                        }
                        if (yt >= y && yt <= y+h && xt >= aux2 && xt <= aux1+w){
                            fprintf(qrytxt, "retangulo destruido id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), x, y, w, h, getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+(90/((w*h)/5))); 
                            aux = ' ';
                        }
                    break;
                    case 'l':;
                        double x1 = getLineX1(form);
                        double y1 = getLineY1(form);
                        double x2 = getLineX2(form);
                        double y2 = getLineY2(form);
                        double aux3, aux4;
                        if (dx>0){
                            aux1 = x1;
                            aux2 = x1-dx;
                            aux3 = x2;
                            aux4 = x2-dx;
                        } else {
                            aux1 = x1-dx;
                            aux2 = x1;
                            aux3 = x2-dx;
                            aux4 = x2;
                        }
                        if ((yt >= y1 && yt <= y2) && ((xt >= aux2 && xt <= aux1)||(xt >= aux4 && xt <= aux3))){
                            fprintf(qrytxt, "linha destruida id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x1, y1, x2, y2, getLineCor(form), getLineProtec(form), getLineVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+150);
                            aux = ' ';
                        }
                    break;
                    case 't':;
                        x = getTextX(form);
                        y = getTextY(form);
                        if (dx>0){
                            aux1 = x;
                            aux2 = x-dx;
                        } else {
                            aux1 = x-dx;
                            aux2 = x;
                        }
                        if (yt == y && xt >= aux2 && xt <= aux1){
                            fprintf(qrytxt, "text destruido id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), xt, yt, getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
                            fprintf(qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(form2), xt, yt);  
                            setTextText(form2, "$");
                            remover(nau, node2); 
                            remover(Lista, nodeL);
                            setPontos(pont,getPontos(pont)+500);
                            aux = ' ';
                        }
                    break;
                    default:
                    break;
                }
            }
        }
    }
}