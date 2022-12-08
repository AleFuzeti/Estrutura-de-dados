#include "libs.h"

#include "lista.h"
#include "system.h"
#include "path.h" 
#include "circ.h"
#include "rect.h"
#include "text.h"
#include "line.h"
#include "qry.h"
#include "cpt.h"
#include "svg.h"

typedef struct pontos{
    double pontos;
}   pontos;

int readParam(int argc, char** argv, void* paths) {
    //seta todos as leituras como falsas
    bool readgeo = false; 
    bool readbsd = false; 
    bool readqry = false; 
    
    char* norm;
    int len;
    
    int  opt;
        while ((opt = getopt(argc, argv, "e:f:o:q:")) != -1) { //realiza a leitura dos parametros
            switch (opt) {
            case 'e':; //leitura do path de entrada
                char* bed = calloc(strlen(optarg) + 1, sizeof(char));
                strcpy(bed,optarg);
                len = strlen(bed);
                norm = "";
                normalizePath(bed, norm, len);//tira a barra se tiver
                setBed(paths, bed); 
                break;
            case 'f':; //leitura do nome do arquivo .geo
                char* geoarq = calloc(strlen(optarg)  + 1, sizeof(char)); 
                char* geoname = calloc(strlen(optarg) + 1, sizeof(char)); 
                char* ext = ".geo";
                if (!getBed(paths)){
                    char* bed =  calloc(3, sizeof(char));
                    strcpy(bed, "./");
                    setBed(paths, bed);
                }
                readgeo = true; 
                strcpy(geoarq, optarg); 

                char* geofull = calloc(strlen(geoarq) + strlen(getBed(paths)) + 2, sizeof(char));
                
                joinFilePath(getBed(paths), geoarq, geofull, len); //junta o path de entrada com o nome do arquivo
                                
                strcpy(geoname,geoarq); //copia o nome do arquivo para o nome sem extensao
                if (geoname[strlen(geoname)-4] == '.') //se tiver o .geo, tira
                *(geoname + strlen( geoname )-4)  = '\0';// se tem "/" retira
                //geoname[strlen(geoname)-4] = '\0';
                
                joinAll(getBed(paths),geoname,ext,geofull, len); 

                setGeoName(paths, geoname); 
                setGeoArq(paths, geoarq); 
                setGeoFull(paths, geofull);  
                break;

            case 'o':; //leitura do path de saida
                char* bsd = calloc(strlen(optarg) + 1, sizeof(char)); 
                strcpy(bsd, optarg); 
                readbsd = true; 
                normalizePath(bsd, norm, len);//tira a barra se tiver
                setBsd(paths, bsd);           
                break;
            case 'q':; //leitura do nome do arquivo .qry
                char* qryarq = calloc(strlen(optarg)  + 1, sizeof(char)); 
                char* qryname = calloc(strlen(optarg) + 1, sizeof(char)); 
                if (!getBed(paths)){
                    char* bed =  calloc(3, sizeof(char));
                    strcpy(bed, "./");
                    setBed(paths, bed);
                }
                readqry = true; 
                strcpy(qryarq, optarg); 

                char* qryfull = calloc(strlen(qryarq) + strlen(getBed(paths)) + 2, sizeof(char)); 

                joinFilePath(getBed(paths), qryarq, qryfull, len); //junta o path de entrada com o nome do arquivo
                while (strrchr(qryarq, '/')) {
                qryarq = strrchr(qryarq, '/') + 1; //pega o nome do arquivo
                strcpy(qryname,qryarq); //copia o nome do arquivo para o nome sem extensao
                }
                if (qryname[strlen(qryname)-4] == '.') //se tiver o .qry, tira
                *(qryname + strlen( qryname )-4)  = '\0';// se tem "/" retira
                        
                setQryName(paths, qryname);
                setQryArq(paths, qryarq);
                setQryFull(paths, qryfull);
                break;

            default: /* '?' */
                printf("\nerro lendo parametros\n");
                return -1;
            }
        }

    if (!readbsd || !readgeo){// entrada do .geo 
        printf("\nErro ao ler o .geo ou sem diretorio de saida\n");
        return -1;
    }

    if (readbsd && readgeo){// saida/geoname.svg  
        char* bsdgeosvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + 6, sizeof(char));
        strcpy(bsdgeosvg, getBsd(paths));
        prepareDir(bsdgeosvg);
        strcat(bsdgeosvg, getGeoName(paths));
        strcat(bsdgeosvg, ".svg");
        setBsdGeoSvg(paths, bsdgeosvg);
    }
    if (readbsd && readqry){ // saida/geoname_qryname.svg e bsd/geoname_qryname.txt 
        char* bsdgeoqrysvg = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 7, sizeof(char));
        char* bsdgeoqrytxt = calloc(strlen(getBsd(paths)) + strlen(getGeoName(paths)) + strlen(getQryName(paths)) + 7, sizeof(char));
        strcpy(bsdgeoqrysvg, getBsd(paths));
        prepareDir(bsdgeoqrysvg);
        strcat(bsdgeoqrysvg, getGeoName(paths));
        strcat(bsdgeoqrysvg, "_");
        strcat(bsdgeoqrysvg, getQryArq(paths));
        
        if (bsdgeoqrysvg[strlen(bsdgeoqrysvg)-4] == '.') //se tiver o .qry, tira
            bsdgeoqrysvg[strlen(bsdgeoqrysvg)-4] = '\0';
        
        strcpy(bsdgeoqrytxt, bsdgeoqrysvg);
        strcat(bsdgeoqrysvg, ".svg");
        strcat(bsdgeoqrytxt, ".txt");
        setBsdGeoQrySvg(paths, bsdgeoqrysvg);
        setBsdGeoQryTxt(paths, bsdgeoqrytxt);
    }
    return 0;
} 

/*readPrintGeo*/
void savePrintCirc(CPTree tree, FILE* geo, FILE* svg)
{
    int id;
    double x, y, r;
    char corb[20], corp[20];
    fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
    void* newform = CriaCirculo(id,corb,corp,x,y,r);
    void *vfindo = NULL, *vfvoltando = NULL;
    void * extra[2] = {&id, NULL}; 
    insertCPT(tree, x, y, newform, vfindo, vfvoltando, extra);
    fprintf(svg, CIRC_SVG, id, x, y, r, corb, corp);

}

void savePrintRect(CPTree tree, FILE* geo, FILE* svg)
{
    int id;
    double x, y, w, h;
    char corb[20], corp[20];
    fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
    void* newform = CriaRetangulo(id,corb,corp,x,y,w,h);
    void *vfindo = NULL, *vfvoltando = NULL;
    void * extra[2] = {&id, NULL}; 
    insertCPT(tree, x, y, newform, vfindo, vfvoltando, extra);
    fprintf(svg, RECT_SVG, id, x, y, w, h, corb, corp);
}

void savePrintLine(CPTree tree, FILE* geo, FILE* svg)
{
    int id;
    double x, y, x2, y2;
    char cor[20];
    fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x, &y, &x2, &y2, cor);
    void* newform = Crialinha(id,cor,x,y,x2,y2);
    void *vfindo = NULL, *vfvoltando = NULL;
    void * extra[2] = {&id, NULL}; 
    insertCPT(tree, x, y, newform, vfindo, vfvoltando, extra);
    fprintf(svg, LINE_SVG, id, x, y, x2, y2, cor);
}

void savePrintText(CPTree tree, FILE* geo, FILE* svg)
{
    int id;
    double x, y;
    char corb[20], corp[20], a, txto[100];
    fscanf(geo, "%d %lf %lf %s %s %c %[^\n]s", &id, &x, &y, corb, corp, &a, txto);
    void* newform = CriaTexto(id,corb,corp,x,y,a,txto);
    void *vfindo = NULL, *vfvoltando = NULL;
    void * extra[2] = {&id, NULL}; 
    insertCPT(tree, x, y, newform, vfindo, vfvoltando, extra);
    
    char* aux;
    if (a == 'i')
    {
        aux="start";
    }
    else if (a == 'm')
    {
        aux="middle";
    }
    else if (a == 'f')
    {
        aux="end";
    }
    
    fprintf(svg, TEXT_SVG, id, x, y, corb, corp, aux, txto);
}

void readPrintGeo(void* tree, void* paths) {
    
    FILE* geo = fopen(getGeoFull(paths), "r");
    
    if (geo == NULL) { 
        printf("Erro abrindo o .geo \n");
        exit(EXIT_FAILURE);
    } 
    FILE* svg = fopen(getBsdGeoSvg(paths), "w");
    fprintf(svg, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    if(svg){
        char type[2];
        while (!feof(geo)) { 
            fscanf(geo, "%s", type);
            if (!strcmp(type, "c")){ //Circle 
                savePrintCirc(tree, geo, svg);
            } 
            else if (!strcmp(type, "r")){ //Rectangle 
                savePrintRect(tree, geo, svg);
            } 
            else if (!strcmp(type, "l")){ //Line 
                savePrintLine(tree, geo, svg);
            } 
            else if (!strcmp(type, "t")){ //Text 
                savePrintText(tree, geo, svg);
            }
            strcpy(type, ""); 
        } 
        fprintf(svg, "</svg>\n");
        fclose(svg);
    } else{
            printf("Error opening the first .svg file.\n");
            exit(EXIT_FAILURE);
        }
        
        fclose(geo);
    }

void readQry(void* tree, void* paths){ 
    
    FILE* qry = fopen(getQryFull(paths), "r");

    if (qry == NULL) { 
        printf("Erro abrindo o arquivo.qry\n");
        exit(EXIT_FAILURE);
    } 

    FILE* qrysvg = fopen(getBsdGeoQrySvg(paths), "w");
    FILE* qrytxt = fopen(getBsdGeoQryTxt(paths), "w");
    fprintf(qrysvg, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    
    int nausCap[1000];
    Lista naus = createLista(-1);  //cria a lista de naus
    Lista ancoras = createLista(-1); //cria a lista de ancoras
    void* pon = createPontos(); //cria pontos
    setPontos(pon, 0); //seta os pontos para 0

    double agress = 0;
    char func[8];

    while (!feof(qry)) { 
        fscanf(qry, "%s", func);

        if (!strcmp(func, "na")) 
        { 
            agress = na(qry);
        }
        else if (!strcmp(func, "be")) 
        { 
            be(ancoras, tree, qry, qrysvg, qrytxt, agress, pon);
        }
        else if (!strcmp(func, "tp")) 
        { 
            tp(ancoras, tree, qry, qrysvg, qrytxt, pon);
        } 
        else if (!strcmp(func, "tr")) 
        { 
            tr(ancoras, tree, qry, qrysvg, qrytxt);
        }
        else if (!strcmp(func, "se")) 
        { 
            se(ancoras, tree, qry, qrysvg, qrytxt);
        }
        else if (!strcmp(func, "sec")) 
        { 
            sec(nausCap, naus, tree, qry, qrysvg, qrytxt);
        }
        else if (!strcmp(func, "org"))
        {
            org(naus, qry, qrytxt);
        }
        else if (!strcmp(func, "mvh")) 
        { 
            mvh(nausCap, naus, tree, qry, qrysvg, qrytxt, pon);
        }
        else if (!strcmp(func, "mvv")) 
        { 
            mvv(nausCap, naus, tree, qry, qrysvg, qrytxt, pon);
        }
        strcpy(func," ");

    } 
    fclose(qry);

    //printOnOpen(ancoras, tree, qrysvg); //printa no svg
    dfs(tree, printQry, qrysvg);
    printAnco(ancoras, qrysvg);

    fprintf(qrysvg, "</svg>\n");

    fprintf(qrytxt, "\nPontuacao maxima:%.2lf\n",getPontos(pon));
    fclose(qrysvg);
    fclose(qrytxt);

    killLista(ancoras); // mata a lista de ancoras
    killLista(naus); // mata a lista de naus
    free(pon); // mata os pontos
}

char checkForm(void* n){
    void* aux = n;
    if(checkCirc(aux)){
        return 'c';
    } else if(checkLine(aux)){
        return 'l';
    } else if(checkRect(aux)){
        return 'r';
    } else if(checkText(aux)){
        return 't';
    }
    return ' ';
}
int getFormId(void* n){
    char type = checkForm(n);
    if(type == 'c'){
        return getCircId(n);
    } else if(type == 'r'){
        return getRectId(n);
    } else if(type == 'l'){
        return getLineId(n);
    } else if(type == 't'){
        return getTextId(n);
    } 
    return 0;
}

double getAreaGeral(void* n){
    void* aux = n;
    char type = checkForm(n);
    if(type == 'c'){
        return getCircArea(aux);
    } else if(type == 'r'){
        return getRectArea(aux);
    } else if(type == 'l'){
        return getLineArea(aux);
    } else if(type == 't'){
        return getTextArea(aux);
    } 
    return 0;
}
void deleteForm(void* n){
    void* aux = n;
    if(checkCirc(aux)){
        freeCirc(aux);
    } else if(checkLine(aux)){
        freeLine(aux);
    } else if(checkRect(aux)){
        freeRect(aux);
    } else if(checkText(aux)){
        freeText(aux);
    }
}
bool checkDentro(void* lista, void* n, double x, double y, double r){
    void* data = n;
    char type = checkForm(data);
    //void* data = get(lista, aux);
    if(type == 'c'){
        double x1 = getCircX(data);
        double y1 = getCircY(data);
        if(sqrt(pow(x1-x,2)+pow(y1-y,2)) <= r){
            return true;
        }

    } else if(type == 'r'){
        double x1 = getRectX(data);
        double y1 = getRectY(data);
        double w1 = getRectW(data);
        double h1 = getRectH(data);
        if(sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)) <= r && sqrt(pow(x1 + w1 - x, 2) + pow(y1 - y, 2)) <= r && sqrt(pow(x1 - x, 2) + pow(y1 + h1 - y, 2)) <= r && sqrt(pow(x1 + w1 - x, 2) + pow(y1 + h1 - y, 2)) <= r){
            return true;
        }
    } else if(type == 'l'){
        double x1 = getLineX1(data);
        double y1 = getLineY1(data);
        double x2 = getLineX2(data);
        double y2 = getLineY2(data);
        if(sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)) <= r && sqrt(pow(x2 - x, 2) + pow(y2 - y, 2)) <= r){
            return true;
        }
    } else if(type == 't'){
        double x1 = getTextX(data);
        double y1 = getTextY(data);
        
        if(sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)) <= r){
            return true;
        }
    }
    type = ' ';
    return false;
}

void* createPontos(){
    pontos* p = calloc(1, sizeof(pontos));
    return p;
}
double getPontos(void* p){
    pontos* pont = p;
    return pont->pontos;
}
void setPontos(void* p, double pont){
    pontos* pontos = p;
    pontos->pontos = pont;
}