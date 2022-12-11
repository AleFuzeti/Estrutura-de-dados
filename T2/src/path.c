#include "libs.h"

#include "system.h"
#include "path.h"
#include "lista.h"

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


void splitPath(char *fullPath, char *path, int lenPath, char *nomeArq, int lenNomeArq, char *extArq, int lenExtArq){

    if(strchr(fullPath, '/')){ //se tiver barra (completo)
        path = realloc(path, strlen(fullPath));
        strcpy(path,fullPath);
        if(strchr(path, '.')){
            path[strlen(path)-4] = '\0';
        }
        nomeArq = strrchr(fullPath, '/') + 1;
        if(strchr(nomeArq, '.')){
            extArq = strrchr(nomeArq, '.');
            nomeArq[strlen(nomeArq)-4] = '\0';
        } else {
            extArq = "";
        }
        return;
    }
    else{ //se nao tiver barra (so o nome)
        path = "";
        if(strchr(fullPath, '.')){
            nomeArq = fullPath;
            nomeArq[strlen(nomeArq)-4] = '\0';
            extArq = strrchr(fullPath, '.');
        } else {
            nomeArq = fullPath;
            extArq = "";
        }
        return;
    }
    return;
}

void joinFilePath(char *path, char *fileName, char *fullPath, int lenFullPath){
    
    if(strchr(path, '/')){ //se tiver barra (completo)
    strcpy(fullPath, path);
    strcat(fullPath, "/");
    strcat(fullPath, fileName);
    return;
    }   else{ //se nao tiver barra (so o nome)
        strcpy(fullPath, fileName);
        return;
    }
}

void joinAll(char *path, char *fileName, char *ext, char *fullPath, int lenfullPath){
    
    strcpy(fullPath, path);
    if (fullPath[strlen(fullPath)-1] != '/'){ //coloca barra se nao tiver
        strcat(fullPath, "/");
    }
    strcat (fullPath,fileName); 
    strcat (fullPath,ext); 
}

void getFileName(char *fullPath, char *fileName, char *lenFileName){
    if(strchr(fullPath, '/')){ //se tiver barra (completo)
        fileName = strrchr(fullPath, '/') + 1;
        return;
    }
    else{ //se nao tiver barra (so o nome)
        fileName = fullPath;
        return;
    }
}

void getPath(char *fullPath, char *path, int lenPath){
    path = realloc(path, strlen(fullPath));
    strcpy(path, fullPath);
    if(strchr(path, '/')){
    *(strrchr(path, '/') + 1) = '\0'; //tira o nome do arquivo
    }
    else path = "";
}

void normalizePath(char *path, char *normPath, int lenNormPath){
    
    if (path[strlen(path)-1] != '/'){ //se não tem "/" retorna
      normPath = path;
      return;
    }
    else{
    normPath = path;
    *(path + strlen( path )-1)  = '\0';// se tem "/" retira
    return;
    }
}