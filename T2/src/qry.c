#include "libs.h"

#include "circ.h"
#include "rect.h"
#include "text.h"
#include "line.h"

#include "qry.h"
#include "system.h"
#include "lista.h"
#include "cpt.h"

// searchId usado em algumas funcoes
void searchId(double x, double y, Info i, double xc, double yc, double r, void *extra)
{
    void** returnArray = extra;
    if (getFormId(i) == *(int*)returnArray[0])
    {
        returnArray[1] = i;
    }    
}

void si(double x, double y, Info i, double xc, double yc, double r, void *extra){}

// na  
double na(FILE* qry)
{
    double aux;
    fscanf(qry, "%lf", &aux);
    return aux;
}

// be
struct BE
{
    void *tree, *anc, *pont;
    double agress;
    void* nausCap;
    double bex, bey, ber; 
    FILE* qrytxt, *qrysvg;
};

void checkBE(double xx, double yy, Info i, double xc, double yc, double rr, void *extra)
{
    struct BE* BE = extra;
    void *aux, *anc = BE->anc, *pont = BE->pont;
    double bex = BE->bex;
    double bey = BE->bey;
    double ber = BE->ber;
    double agress = BE->agress;
    FILE* qrysvg = BE->qrysvg, *qrytxt = BE->qrytxt;

    void* form = i;

    int id;
    double x, x2, y, y2, r, w, h, auxX, auxY, protec;
    char corb[20], corp[20], cor[20];
    double areab = ber*ber*3.14; 
    
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
            if  (checkDentro(form, bex, bey, ber))
            {
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                fprintf(qrytxt, "be rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, w, h, corb, corp, protec);

                insert(anc, anco);
                protec = protec - (agress*getRectArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0)
                {
                    fprintf(qrytxt, "rect id=%d REMOVIDA, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, w, h, corb, corp, protec);
                    removeCPT(BE->tree, x, y, i, si, si, NULL);
                    setPontos(pont,getPontos(pont)+90);
                } 
                else setRectProtec(form,protec);
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
            if  (checkDentro(form, bex, bey, ber))
            {
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                if (id!=0)
                fprintf(qrytxt, "be circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, r, corb, corp, protec);
                
                insert(anc, anco);        
                protec = protec - (agress*getCircArea(form)/(areab)); //diminuição do nivel de protecao   
                if (protec <= 0)
                {
                    fprintf(qrytxt, "circ id=%d REMOVIDA, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, r, corb, corp, protec);
                    removeCPT(BE->tree, x, y, i, si, si, NULL);
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

            if  (checkDentro(form, bex, bey, ber))
            {
                if (x<x2)
                {
                    auxX = x;
                    auxY = y;
                } 
                else if(x2<x)
                {
                    auxX = x2;
                    auxY = y2;
                } 
                else if(y<y2)
                {
                    auxX = x;
                    auxY = y;
                } 
                else
                {
                    auxX = x2;
                    auxY = y2;
                }
                void* anco = CriaCirculo(id, "null", "null", auxX, auxY, 1);
                fprintf(qrytxt, "be line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf\n", id, x, y, x2, y2, cor, protec);

                insert(anc, anco);
                protec = protec - (agress*getLineArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0)
                {
                    fprintf(qrytxt, "line id=%d REMOVIDA, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf\n", id, x, y, x2, y2, cor, protec);
                    removeCPT(BE->tree, x, y, i, si, si, NULL);
                    setPontos(pont,getPontos(pont)+50);
                } 
                else setLineProtec(form,protec);
            }
        break;
        case 't':
            id = getTextId(form);
            x = getTextX(form);
            y = getTextY(form);
            protec = getTextProtec(form);
            strcpy(corp, getTextCorP(form));
            strcpy(corb, getTextCorC(form));
            
            if  (checkDentro(form, bex, bey, ber))
            {
                void* anco = CriaCirculo(id, "null", "null", x, y, 1);
                fprintf(qrytxt, "be text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, corb, corp, protec);

                insert(anc, anco);
                protec = protec - (agress*getTextArea(form)/(areab)); //diminuição do nivel de protecao
                if (protec <= 0)
                {
                    fprintf(qrytxt, "text id=%d REMOVIDA, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n", id, x, y, corb, corp, protec);
                    removeCPT(BE->tree, x, y, i, si, si, NULL);
                    setPontos(pont,getPontos(pont)+30);
                } else setTextProtec(form,protec);
            }
        break;
        default:
        printf("error ");
        break;  
    }
}

void be(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, double agress, void* pont)
{
    double bex, bey, ber;
    fscanf(qry, "%lf %lf %lf", &bex, &bey, &ber);
    fprintf(qrysvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" stroke-width=\"1\" stroke-dasharray =\"5,3\" fill-opacity=\"0.0\" fill=\"null\" />\n", bex, bey, ber);
    
    struct BE* BE = calloc(1, sizeof(struct BE));
    BE->bex = bex;
    BE->bey = bey;
    BE->ber = ber;
    BE->qrysvg = qrysvg;
    BE->qrytxt = qrytxt;
    BE->agress = agress;
    BE->pont = pont;
    BE->tree = tree;
    BE->anc = anc;
    dfs(tree, checkBE, BE);    
}

//se e sec
void sel(void* form, void* list, void* anc, FILE* qrytxt, char* aux)
{
    void *form2, *anco;
    char tipo = checkForm(form);
    switch (tipo)
    {
        case 'r':
            fprintf(qrytxt, "%s rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", aux, getRectId(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
            form2 = CriaRetangulo(getRectId(form), getRectCorC(form), getRectCorP(form), getRectX(form), getRectY(form), getRectW(form), getRectH(form));
            anco = CriaCirculo(getRectId(form), "red", "red", getRectX(form), getRectY(form), 1);
        break;
        case 'c':
            fprintf(qrytxt, "%s circle id=%d, cx=%.2lf, cy=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", aux, getCircId(form), getCircX(form), getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
            form2 = CriaCirculo(getCircId(form), getCircCorC(form), getCircCorP(form), getCircX(form), getCircY(form), getCircR(form));
            anco = CriaCirculo(getRectId(form), "red", "red", getRectX(form), getRectY(form), 1);
        break;
        case 'l':
            fprintf(qrytxt, "%s line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", aux, getLineId(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form), getLineCor(form), getLineProtec(form), getLineVida(form));
            form2 = Crialinha(getLineId(form), getLineCor(form), getLineX1(form), getLineY1(form), getLineX2(form), getLineY2(form));
            anco = CriaCirculo(getRectId(form), "red", "red", getRectX(form), getRectY(form), 1);
        break;
        case 't':
            fprintf(qrytxt, "%s text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, alinhamento=%c, texto=%s, nivel de energia=%lf, vida= %d\n", aux, getTextId(form), getTextX(form), getTextY(form), getTextCorC(form), getTextCorP(form), getTextA(form), getTextText(form), getTextProtec(form), getTextVida(form));
            form2 = CriaTexto(getTextId(form), getTextCorC(form), getTextCorP(form), getTextX(form), getTextY(form), getTextA(form), getTextText(form));
            anco = CriaCirculo(getRectId(form), "red", "red", getRectX(form), getRectY(form), 1);
        break;
    }
    insert(list, form2);
    insert(anc, anco);
}

void se(void*anc, void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt)
{
    int id;
    
    fscanf(qry, "%d", &id);

    void* pArray[2] = {&id, NULL};
    dfs(tree, searchId, pArray);
    if(pArray[1])
    {
        sel(pArray[1], nau, anc, qrytxt, "se");
    }
}

void sec(int nausCap[], void* anc, void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt)
{
    int id,j;
    
    fscanf(qry, "%d %d", &id, &j);

    void* pArray[2] = {&id, NULL};
    dfs(tree, searchId, pArray);
    if(pArray[1])
    {
        sel(pArray[1], anc, nau, qrytxt, "sec");
        nausCap[j] = getFormId(pArray[1]);
    }
    
}

// org
void org(void* naus, FILE* qry,FILE* qrytxt)
{
    fprintf(qrytxt, "id depois da ordenação: |");
    quickSort(naus);    

    for(void* node = getFirst(naus); node; node = getNext(naus,node))
    {
        void* form = get(naus,node);
        int id = getFormId(form);
        double area = getAreaGeral(form);
        fprintf(qrytxt, " id=%d, area=%lf | ", id, area);
    }
    fprintf(qrytxt, "\n");
}

//mvv e mvh
struct MV
{   
    void* list, *tree, *form, *pont, *L;
    char* text;
    char type, xy;
    double dxy;
    void* nausCap;
    FILE* qrytxt;
};

void checkMine(double xx, double yy, Info i, double xc, double yc, double r, void *extra)
{
    struct MV* mv = extra;
    if (strstr(getTextText((i)), mv->text))
    {
        void* pont = mv->pont;
        void* form = mv->form;
        double xt = getTextX(i);
        double yt = getTextY(i);
        double x,y;
        double auxX1, auxX2, auxY1, auxY2;
    
        switch (mv->type)
        {
            case 'c':;
                x = getCircX(form);
                y = getCircY(form);
                double r = getCircR(form);
                if(mv->xy == 'y')
                {
                    if (mv->dxy > 0)
                    {
                        auxY2 = y;
                        auxY1 = y - mv->dxy;
                        auxX1 = x;
                        auxX2 = x;
                    } 
                    else 
                    {
                        auxY2 = y - mv->dxy;
                        auxY1 = y;
                        auxX1 = x;
                        auxX2 = x;
                    }
                }
                else if(mv->xy == 'x')
                {
                    if (mv->dxy > 0){
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x;
                        auxX1 = x - mv->dxy;
                    } else {
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x - mv->dxy;
                        auxX1 = x;
                    }
                }
                if (yt >= auxY1-r && yt <= auxY2+r && xt >= auxX1-r && xt <= auxX2+r)
                {
                    fprintf(mv->qrytxt, "circ destruido id=%d, cx=%.2lf, cy=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), getCircX(form), getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                    fprintf(mv->qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(i), xt, yt);  
                    setTextText(i, "$");
                    removeCPT(mv->tree, x, y, form, NULL, NULL, NULL); 
                    remover(mv->list, mv->L);
                    setPontos(pont,getPontos(pont)+(75/((r*r*3.14)/5)));
                    mv->type = ' ';
                }
            break;
            case 'r':;
                x = getRectX(form);
                y = getRectY(form);
                double w = getRectW(form);
                double h = getRectH(form);
                if(mv->xy == 'y')
                {
                    if (mv->dxy > 0)
                    {
                        auxY2 = y;
                        auxY1 = y - mv->dxy;
                        auxX1 = x;
                        auxX2 = x;
                    } 
                    else 
                    {
                        auxY2 = y - mv->dxy;
                        auxY1 = y;
                        auxX1 = x;
                        auxX2 = x;
                    }
                }
                else if(mv->xy == 'x')
                {
                    if (mv->dxy > 0){
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x;
                        auxX1 = x - mv->dxy;
                    } else {
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x - mv->dxy;
                        auxX1 = x;
                    }
                }
                if (yt >= auxY1 && yt <= auxY2+h && xt >= auxX1 && xt <= auxX2+w)
                {
                    fprintf(mv->qrytxt, "retangulo destruido id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), x, y, w, h, getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                    fprintf(mv->qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(i), xt, yt);  
                    setTextText(i, "$");
                    removeCPT(mv->tree, x, y, form, NULL, NULL, NULL); 
                    remover(mv->list, mv->L);
                    setPontos(pont,getPontos(pont)+(90/((w*h)/5))); 
                    mv->type = ' ';
                }
            break;
            case 'l':;
            break;
            case 't':;
                x = getTextX(form);
                y = getTextY(form);
                if(mv->xy == 'y')
                {
                    if (mv->dxy > 0)
                    {
                        auxY2 = y;
                        auxY1 = y - mv->dxy;
                        auxX1 = x;
                        auxX2 = x;
                    } 
                    else 
                    {
                        auxY2 = y - mv->dxy;
                        auxY1 = y;
                        auxX1 = x;
                        auxX2 = x;
                    }
                }
                else if(mv->xy == 'x')
                {
                    if (mv->dxy > 0){
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x;
                        auxX1 = x - mv->dxy;
                    } else {
                        auxY1 = y;
                        auxY2 = y;
                        auxX2 = x - mv->dxy;
                        auxX1 = x;
                    }
                }      
                if (yt >= auxY1 && yt <= auxY2 && xt >= auxX1 && xt <= auxX2)
                {
                    fprintf(mv->qrytxt, "text destruido id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), x, y, getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
                    fprintf(mv->qrytxt, "mina destruida, id=%d x=%lf y=%lf \n", getTextId(i), xt, yt);  
                    setTextText(i, "$");
                    removeCPT(mv->tree, x, y, form, NULL, NULL, NULL); 
                    remover(mv->list, mv->L);
                    setPontos(pont,getPontos(pont)+500);
                    mv->type = ' ';
                }
            break;
            default:
            break;
        }
    }
}

void moveXY(bool mv, void* Mv, char op)
{
    struct MV* MV = Mv;
    char type = checkForm(MV->form);
    void* form = MV->form;
    void* tree = MV->tree;
    FILE* qrytxt = MV->qrytxt;

    MV->text = "#";
    MV->xy = op;

    if (op == 'y')
    {
        switch (type)
        {
            case 'r':;
                double yr = getRectY(form);
                yr = yr + MV->dxy;
                setRectY(form, yr);
                if(mv)
                {
                    fprintf(qrytxt, "retangulo movido verticalmente id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), getRectX(form), yr, getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                } 
                else
                {
                    MV->type = 'r';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 'c':;
                double yc = getCircY(form);
                yc = yc + MV->dxy;
                setCircY(form, yc);
                if(mv)
                {
                    fprintf(qrytxt, "circ movido verticalmente id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), getCircX(form), yc, getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                } 
                else
                {   
                    MV->type = 'c';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 'l':;
                double y1l = getLineY1(form);
                double y2l = getLineY2(form);
                y1l = y1l + MV->dxy;
                y2l = y2l + MV->dxy;
                setLineY1(form, y1l);
                setLineY2(form, y2l);
                if(mv)
                {
                    fprintf(qrytxt, "line movida verticalmente id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), getLineX1(form), y1l, getLineX2(form), y2l, getLineCor(form), getLineProtec(form), getLineVida(form));
                } 
                else
                {   
                    MV->type = 'l';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 't':;
                double yt = getTextY(form);
                yt = yt + MV->dxy;
                setTextY(form, yt);
                if(mv)
                {
                    fprintf(qrytxt, "text movido verticalmente id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), getTextX(form), yt, getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
                } 
                else
                {   
                    MV->type = 't';
                    dfs(tree, checkMine, MV);
                }
            break;        
        }
    } 
    else if(op == 'x')
    {
        switch(type)
        {
            case 'r':;
                double xr = getRectX(form);
                xr = xr + MV->dxy;
                setRectX(form, xr);
                if(mv)
                {
                fprintf(qrytxt, "rect movido horizontalmente id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), xr, getRectY(form), getRectW(form), getRectH(form), getRectCorC(form), getRectCorP(form), getRectProtec(form), getRectVida(form));
                } 
                else
                {
                    MV->type = 'r';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 'c':;
                double xc = getCircX(form);
                xc = xc + MV->dxy;
                setCircX(form, xc);
                if(mv){
                fprintf(qrytxt, "circ movido horizontalmente id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), xc, getCircY(form), getCircR(form), getCircCorC(form), getCircCorP(form), getCircProtec(form), getCircVida(form));
                } 
                else
                {    
                    MV->type = 'c';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 'l':;
                double x1l = getLineX1(form);
                double x2l = getLineX2(form);
                x1l = x1l + MV->dxy;
                x2l = x2l + MV->dxy;
                setLineX1(form, x1l);
                setLineX2(form, x2l);
                if(mv){
                fprintf(qrytxt, "line movido horizontalmente id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x1l, getLineY1(form), x2l, getLineY2(form), getLineCor(form), getLineProtec(form), getLineVida(form));
                } 
                else
                {    
                    MV->type = 'l';
                    dfs(tree, checkMine, MV);
                }
            break;
            case 't':;
                double xt = getTextX(form);
                xt = xt + MV->dxy;
                setTextX(form, xt);
                if(mv){
                fprintf(qrytxt, "text movido horizontalmente id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), xt, getTextY(form), getTextCorC(form), getTextCorP(form), getTextProtec(form), getTextVida(form));
                } 
                else
                {    
                    MV->type = 't';
                    dfs(tree, checkMine, MV);
                }
            break;
        }
    }   

}

void mvv (int nausCap[], void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont)
{
    void* node;
    int k, i=0;
    double dy;

    fscanf(qry, "%d %lf", &k, &dy);

    struct MV* MV = calloc(1, sizeof(struct MV));
    MV->tree = tree;
    MV->pont = pont;
    MV->list = nau;
    MV->nausCap = nausCap;
    MV->qrytxt = qrytxt;

    if(k>0)
    {
        for(node = getFirst(nau);(i<k);node = getNext(nau,node))
        {
            if (!node)
            {
                printf("\nNão tem mais elementos na lista!!\n");
                return;
            }            
            void* form = get(nau, node);
            int id = getFormId(form);
            MV->form = form;
            MV->L = form;
            MV->dxy = dy;
            moveXY(true, MV, 'y');
            i++;

            void* pArray[2] = {&id, NULL};
            dfs(tree, searchId, pArray);
            if(pArray[1])
            {
                MV->form = pArray[1];
                moveXY(false, MV, 'y');
            }
        }
    } 
    else if(k<0)
    {
        for(node = getLast(nau);(i>k); node = getPrevious(nau,node))
        {
            if (!node)
            {
                ("Não tem mais elementos na lista!!! encerrando programa");
                return;
            }
            void* form = get(nau, node);
            int id = getFormId(form);
            MV->form = form;
            MV->L = form;
            MV->dxy = dy;
            moveXY(true, MV, 'y');
            i--;

            void* pArray[2] = {&id, NULL};
            dfs(tree, searchId, pArray);
            if(pArray[1])
            {
                moveXY(false, MV, 'y');
            }
        }
    }
}

void mvh (int nausCap[], void* nau, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont)
{
    void* node;
    int k, i=0;
    double dx;

    fscanf(qry, "%d %lf", &k, &dx);

    struct MV* MV = calloc(1, sizeof(struct MV));
    MV->tree = tree;
    MV->pont = pont;
    MV->list = nau;
    MV->nausCap = nausCap;
    MV->qrytxt = qrytxt;
    if(k>0)
    {
        for(node = getFirst(nau);(i<k);node = getNext(nau,node))
        {
            if (!node)
            {
                printf("\nNão tem mais elementos na lista!!\n");
                return;
            } 
            void* form = get(nau, node);
            int id = getFormId(form);
            MV->form = form;
            MV->L = form;
            MV->dxy = dx;
            moveXY(true, MV, 'x');
            i++;

            void* pArray[2] = {&id, NULL};
            dfs(tree, searchId, pArray);
            if(pArray[1])
            {
                MV->form = pArray[1];
                moveXY(false, MV, 'x');
            }
        }
    } 
    else
    {
        for(node = getLast(nau);(i>k);node = getPrevious(nau,node))
        {
            if (!node)
            {
                printf("\nNão tem mais elementos na lista!!\n");
                return;
            } 
            void* form = get(nau, node);
            int id = getFormId(form);
            MV->form = form;
            MV->L = form;
            MV->dxy = dx;
            moveXY(true, MV, 'x');
            i--;

            void* pArray[2] = {&id, NULL};
            dfs(tree, searchId, pArray);
            if(pArray[1])
            {
                moveXY(false, MV, 'x');
            }
        }
    }
}

//tp 
struct TP
{
    void *tree, *pont;
    double tpx, tpy;
    int i;
    bool hit;
    FILE* qrytxt, *qrysvg; 
};

void checkHit(double xx, double yy, Info i, double xc, double yc, double rr, void *extra)
{
    struct TP* TP = extra;
    double tpx = TP->tpx;
    double tpy = TP->tpy;
    FILE* qrysvg = TP->qrysvg;
    FILE* qrytxt = TP->qrytxt;
    void* tree = TP->tree; 
    void *form = i;

    int id;
    double x, x2, y, y2, r, w, h, auxX, auxY, protec;
    char corb[20], corp[20], cor[20];

    char tipo = checkForm(form);
    switch (tipo)
    {
        case 'r':
            x = getRectX(form);
            y = getRectY(form);
            w = getRectW(form);
            h = getRectH(form);
            id = getRectId(form);
            protec = getRectProtec(form);
            strcpy(corp, getRectCorP(form));
            strcpy(corb, getRectCorC(form));
            if  (tpx >= x && tpx <= x + w && tpy >= y && tpy <= y + h)
            {
                TP->i++;
                int vida = getRectVida(form);
                vida--;
                setRectVida(form, vida);

                if(vida == 0)
                {
                    fprintf(qrytxt, "rect id=%d REMOVIDA, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x, y, w, h, corb, corp, protec, vida);
                    removeCPT(tree, x, y, form, NULL, NULL, NULL);
                    setPontos(TP->pont, getPontos(TP->pont)+(90/((w*h)/5))); //pontos
                } else fprintf(qrytxt, "rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, w, h, corb, corp, protec,vida,3-vida);
                
                TP->hit = true;
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
            
            if  (tpx >= x - r && tpx <= x + r && tpy >= y - r && tpy <= y + r)
            {
                TP->i++;
                int vida = getCircVida(form);
                vida--;
                setCircVida(form, vida);

                if(vida == 0)
                {
                    fprintf(qrytxt, "circ id=%d REMOVIDA, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf\n, vida=%d", id, x, y, r, corb, corp, protec, vida);
                    removeCPT(tree, x, y, form, NULL, NULL, NULL);
                    setPontos(TP->pont,getPontos(TP->pont)+(75/((r*r*3.14)/5))); //pontos
                } else fprintf(qrytxt, "circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, r, corb, corp, protec,vida,2-vida);
                
                TP->hit = true;
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
                TP->i++;
                int vida = getLineVida(form);
                vida--;
                setLineVida(form, vida);

                if(vida == 0)
                {
                    fprintf(qrytxt, "line id=%d REMOVIDA, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d\n", id, x, y, x2, y2, cor, protec, vida);
                    removeCPT(tree, x, y, form, NULL, NULL, NULL);
                    setPontos(TP->pont,getPontos(TP->pont)+150); //pontos
                } else fprintf(qrytxt, "line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, x2, y2, cor, protec,vida,1-vida);
                
                TP->hit = true;
            }
        break;
        case 't':
            id = getTextId(form);
            x = getTextX(form);
            y = getTextY(form);
            protec = getTextProtec(form);
            strcpy(corp, getTextCorP(form));
            strcpy(corb, getTextCorC(form));
            
            if (tpx == x && tpy == y)
            {
                TP->i++;
                int vida = getTextVida(form);
                vida--;
                setTextVida(form, vida);

                if(vida == 0)
                {
                    fprintf(qrytxt, "text id=%d REMOVIDA, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x, y, corb, corp, protec, vida);
                    removeCPT(tree, x, y, form, NULL, NULL, NULL);
                    setPontos(TP->pont,getPontos(TP->pont)+500); //pontos
                } else fprintf(qrytxt, "text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d, atingido %d vezes\n", id, x, y, corb, corp, protec,vida,1-vida);
                
                TP->hit = true;
            }
        break;
        default:
            printf("error\n");
        break;
    }

}

void tp(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt, void* pont)
{
    char txto[100] = "*";
    double tpx, tpy;
    fscanf(qry, "%lf %lf", &tpx, &tpy);

    struct TP* TP = calloc(1, sizeof(struct TP));
    TP->hit = false;
    TP->i = 0;
    TP->tpx = tpx;
    TP->tpy = tpy;
    TP->pont = pont;
    TP->qrytxt = qrytxt;
    TP->qrysvg = qrysvg;
    TP->tree = tree;

    dfs(tree, checkHit, TP);
    
    if (TP->hit == false)
    {
        fprintf(qrytxt, "AGUA\n");
        void* aste = CriaTexto (0, "black","black", tpx, tpy, 'm', "*"); 
        insert(anc, aste);
    } else {
        if(TP->i>1){
            char aux[10];
            sprintf (aux, "%d", TP->i);
            strcat(txto, aux);
        }
        void* aste = CriaTexto (0, "red","red", tpx, tpy, 'm', txto);
        insert(anc, aste);
    } 
}

//tr
struct TR
{
    void *tree;
    double trx, try, dx, dy;
    int i, id;
    bool hit;
    FILE* qrytxt, *qrysvg; 
};

void checkRep(double xx, double yy, Info i, double xc, double yc, double rr, void *extra)
{
    struct TR* TR = extra;
    double trx = TR->trx, try = TR->try;
    double dx = TR->dx, dy = TR->dy;
    int id = TR->id;
    FILE* qrysvg = TR->qrysvg;
    FILE* qrytxt = TR->qrytxt;
    void* tree = TR->tree; 

    void* form = i, *newform;
    double x, x2, y, y2, r, w, h, auxX, auxY, protec;
    int vida;
    char corb[20], corp[20], cor[20], a, txto[100];

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
                void * extra[2] = {&id, NULL}; 
                insertCPT(TR->tree, x+dx, y+dy, newform, si, si, extra);
                
                fprintf(qrytxt, "tr rect id=%d, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getRectId(form), x, y, w, h, corb, corp, protec, vida);
                fprintf(qrytxt, "rect id=%d CLONE, x=%.2lf, y=%.2lf, w=%.2lf, h=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", id, x+trx, y+try, w+trx, h+try, corp, corb, protec, vida);
                id++;

                TR->hit = true;//interroga
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

            if  (trx >= x - r && trx <= x + r && try >= y - r && try <= y + r)
            {
                newform = CriaCirculo(id, corp, corb, x+dx, y+dy, r);
                setCircProtec(newform, protec);
                setCircVida(newform, getCircVida(form));

                insertCPT(TR->tree, x+dx, y+dy, newform, si, si, NULL);
                
                fprintf(qrytxt, "tr circ id=%d, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida= %d\n", getCircId(form), x, y, r, corb, corp, protec, vida);
                fprintf(qrytxt, "circ id=%d CLONE, x=%.2lf, y=%.2lf, r=%.2lf, corb=%s, corp=%s, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, r, corp, corb, protec, vida);
                id++;

                TR->hit = true;
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

            insertCPT(TR->tree, x+dx, y+dy, newform, si, si, si);
    
            fprintf(qrytxt, "tr line id=%d, x1=%.2lf, y1=%.2lf, x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida= %d\n", getLineId(form), x, y, x2, y2, cor, protec, getLineVida(form));
            fprintf(qrytxt, "line id=%d CLONE, x1=%.2lf, y1=%.2lf,  x2=%.2lf, y2=%.2lf, cor=%s, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, x2+trx, y2+try, cor, protec, getLineVida(form));
            id++;
            TR->hit = true;
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

            insertCPT(TR->tree, x+dx, y+dy, newform, si, si, si);

            fprintf(qrytxt, "tr text id=%d, x=%.2lf, y=%.2lf, corb=%s, corp=%s, alinhamento=%s, texto=%s, nivel de energia=%lf, vida= %d\n", getTextId(form), x, y, corb, corp, aux, txto, protec, getTextVida(form));
            fprintf(qrytxt, "text id=%d CLONE, x=%.2lf, y=%.2lf, corb=%s, corp=%s, a=%c, nivel de energia=%lf, vida=%d\n", id, x+trx, y+try, corp, corb, a, protec, getTextVida(form));
            id++;

            TR->hit = true;

        }
            break;
        default:
        printf("error \n");
    }
}

void tr(void* anc, void* tree, FILE* qry, FILE* qrysvg, FILE* qrytxt)
{
    void* Tree = tree;
    void* node;
    bool hit = false;

    char txt[2] = "@";
    double trx, try, dx, dy;
    int id;    
    fscanf(qry, "%lf %lf %lf %lf %d", &trx, &try, &dx, &dy, &id);
    
    struct TR* TR = calloc(1, sizeof(struct TR));
    TR->hit = false;
    TR->i = 0;
    TR->trx = trx;
    TR->try = try;
    TR->dx = dx;
    TR->dy = dy;
    TR->id = id;
    TR->qrytxt = qrytxt;
    TR->qrysvg = qrysvg;
    TR->tree = Tree;
    
    dfs(tree, checkRep, TR);

    if (TR->hit == false)
    {
        void* arro = CriaTexto (0, "black","black", trx, try, 'm', txt); 
        insert(anc, arro);
    } 
    else 
    {
        void* arro = CriaTexto (0, "red","red", trx, try, 'm', txt);
        insert(anc, arro);
    }
}
