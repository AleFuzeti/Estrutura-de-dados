#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

#include "lista.h"
#include "system.h"
#include "path.h" 
#include "circ.h"
#include "rect.h"
#include "text.h"
#include "line.h"
#include "qry.h"

typedef struct all_paths
{
    char* bed; //path de entrada dos arquivos
    char* bsd; //path de saida dos arquivos
    char* geoarq; //nome do arquivo .geo
    char* geoname; //nome do arquivo .geo sem a extensao
    char* qryarq; //nome do arquivo .qry
    char* qryname; //nome do arquivo .qry sem a extensao
    char* bsdgeosvg; //path de saida dos arquivos .svg
    char* bsdgeoqrysvg;  //path de saida dos arquivos qry.svg
    char* bsdgeoqrytxt;  //path de saida dos arquivos qry.txt
    char* qryfull; //path completo do arquivo .qry
    char* geofull; //path completo do arquivo .geo

} all_paths;
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

void readGeo(void* lista, void* paths) {
    int id;
    double x, x2, y, y2, r, w, h;
    char type[2], corc[20], corp[20], cor[20], a, txto[100];
    void* newform;
    void* list = lista;
    //printf("Lendo o arquivo .geo\n %s\n\n", getGeoFull(paths));
    FILE* geo = fopen(getGeoFull(paths), "r");
    
    if (geo == NULL) { 
        printf("Erro abrindo o .geo \n");
        exit(EXIT_FAILURE);
    } 

    while (!feof(geo)) { 
        fscanf(geo, "%s", type);
        if (!strcmp(type, "c")){ //Circle 
            fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corc, corp);
            newform = CriaCirculo(id,corc,corp,x,y,r);
            insert(list, newform);
        } 
        else if (!strcmp(type, "r")){ //Rectangle 
            fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corc, corp);
            newform = CriaRetangulo(id,corc,corp,x,y,w,h);
            insert(list, newform);
        } 
        else if (!strcmp(type, "l")) {//Line 
            fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x, &y, &x2, &y2, cor);
            newform = Crialinha(id,cor,x,y,x2,y2);
            insert(list, newform);
        } 
        else if (!strcmp(type, "t")) {//Text 
            fscanf(geo, "%d %lf %lf %s %s %c %s", &id, &x, &y, corc, corp, &a, txto);
            newform = CriaTexto(id,corc,corp,x,y,a,txto);
            insert(list, newform);
        }
        strcpy(type, ""); 
    } 
    fclose(geo);
}

void readQry(void* naus, void* ancoras, void* lista, void* paths, FILE* qrysvg, FILE* qrytxt, void* pon){ 
    int nausCap[10];
    void* nau = naus;
    void* list = lista;
    void* anc = ancoras;
    void* pont = pon;
    double agress = 0;
    char func[8];
    FILE* qry = fopen(getQryFull(paths), "r");

    if (qry == NULL) { 
        printf("Erro abrindo o arquivo.qry\n");
        exit(EXIT_FAILURE);
    } 

    while (!feof(qry)) { 
        fscanf(qry, "%s", func);

        if (!strcmp(func, "na")) 
        { 
            agress = na(qry);
        }
        if (!strcmp(func, "be")) 
        { 
            be(anc, list, qry, qrysvg, qrytxt, agress, pont);
        }
        if (!strcmp(func, "tp")) 
        { 
            tp(anc, list, qry, qrysvg, qrytxt, pont);
        } 
        if (!strcmp(func, "tr")) 
        { 
            tr(anc, list, qry, qrysvg, qrytxt);
        }
        if (!strcmp(func, "se")) 
        { 
            se(nau, list, qry, qrysvg, qrytxt);
        }
        if (!strcmp(func, "sec")) 
        { 
            sec(nausCap, nau, list, qry, qrysvg, qrytxt);
        }
        if (!strcmp(func, "mvh")) 
        { 
            mvh(nausCap, nau, list, qry, qrysvg, qrytxt, pont);
        }
        if (!strcmp(func, "mvv")) 
        { 
            mvv(nausCap, nau, list, qry, qrysvg, qrytxt, pont);
        }
        strcpy(func," ");

    } 
    fclose(qry);
}


char* prepareDir(char* dir){// coloca barra se não tiver
    if (dir[strlen(dir)-1] != '/'){
        strcat(dir, "/");
        return dir;
    }
    else return dir;
}

void* createAllPaths(){
    all_paths* aux = calloc(1, sizeof(all_paths));
    return aux;
}

void freee(void* paths){
    all_paths* aux = paths;
        free(aux->bed);  
        free(aux->bsd);  
        free(aux->geoarq);
        free(aux->geoname);
        free(aux->bsdgeosvg);
        free(aux->bsdgeoqrysvg);
        free(aux->bsdgeoqrytxt);   
        free(aux->qryname);
        free(aux->geofull);
        free(aux->qryfull);
        //free(aux->qryarq);
        free(paths);
}

void printParam(void* paths) {
    printf("\nentrada dos arquivos: %s", getBed(paths));
    printf("\nsaida dos arquivos: %s", getBsd(paths));    
    printf("\n---------------.geo:------------------- ");
    printf("\nentrada do .geo: %s", getGeoFull(paths));
    printf("\narquivo .geo: %s", getGeoArq(paths));
    printf("\nnome do .geo: %s", getGeoName(paths));
    printf("\n---------------.qry:------------------- ");
    printf("\nentrada do .qry: %s", getQryFull(paths));
    printf("\narquivo .qry: %s", getQryArq(paths));
    printf("\nnome do .qry: %s", getQryName(paths));
    printf("\n---------------.svg .txt:--------------- ");
    printf("\nsaida/geoname.svg: %s", getBsdGeoSvg(paths));
    printf("\nsaida/geoname_qryname.svg: %s", getBsdGeoQrySvg(paths));
    printf("\nsaida/geoname_qryname.txt: %s\n", getBsdGeoQryTxt(paths));
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

void setGeoFull (void* path, char* geofull){
    all_paths* paths = (all_paths*)path;
    paths->geofull = geofull;    
}
void setQryFull (void* path, char* qryfull){
    all_paths* paths = (all_paths*)path;
    paths->qryfull = qryfull;    
}
char* getQryFull(void* path){
    all_paths* paths = path;
    return paths->qryfull;
}
char* getGeoFull(void* path){
    all_paths* paths = path;
    return paths->geofull;
}
void setBed (void* path, char* bed){
    all_paths* paths = (all_paths*)path;
    paths->bed = bed;    
}
void setBsd(void* path, char* bsd){
    all_paths* paths = path;
    paths->bsd = bsd;
}
void setGeoArq(void* path, char* geoarq){
    all_paths* paths = path;
    paths->geoarq = geoarq;
}
void setGeoName(void* path, char* geoname){
    all_paths* paths = path;
    paths->geoname = geoname;
}
void setQryArq(void* path, char* qryarq){
    all_paths* paths = path;
    paths->qryarq = qryarq;
}
void setQryName(void* path, char* qryname){
    all_paths* paths = path;
    paths->qryname = qryname;
}
void setBsdGeoSvg(void* path, char* bsdgeosvg){
    all_paths* paths = path;
    paths->bsdgeosvg = bsdgeosvg;
}
void setBsdGeoQrySvg(void* path, char* bsdgeoqrysvg){
    all_paths* paths = path;
    paths->bsdgeoqrysvg = bsdgeoqrysvg;
}
void setBsdGeoQryTxt(void* path, char* bsdgeoqrytxt){
    all_paths* paths = path;
    paths->bsdgeoqrytxt = bsdgeoqrytxt;
}
char* getBed(void* path){
    all_paths* paths = path;
    return paths->bed;
}
char* getBsd(void* path){
    all_paths* paths = path;
    return paths->bsd;
}
char* getGeoArq(void* path){
    all_paths* paths = path;
    return paths->geoarq; 
}
char* getGeoName(void* path){
    all_paths* paths = path;
    return paths->geoname;
} 
char* getQryArq(void* path){
    all_paths* paths = path;
    return paths->qryarq;
} 
char* getQryName(void* path){
    all_paths* paths = path;
    return paths->qryname;
} 
char* getBsdGeoSvg(void* path){
    all_paths* paths = path;
    return paths->bsdgeosvg;
} 
char* getBsdGeoQrySvg(void* path){
    all_paths* paths = path;
    return paths->bsdgeoqrysvg;
} 
char* getBsdGeoQryTxt(void* path){
    all_paths* paths = path;
    return paths->bsdgeoqrytxt;
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