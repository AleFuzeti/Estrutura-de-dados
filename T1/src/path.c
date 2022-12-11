
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "system.h"
#include "path.h"
#include "lista.h"

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