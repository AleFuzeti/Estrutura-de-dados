#include "libs.h"

#include "text.h"

typedef struct Text PrivateText;

typedef struct Text {
    char type;
    int id;
    char corC[20];
    char corP[20];
    double x;
    double y;
    char a;
    char text[100];
    double area;
    double protec;
    int vida;
}Text;

void setFullText(void* Sdata, int Sid, char ScorC[], char ScorP[], double Sx, double Sy, char Sa, char Stext[]){
    setTextId(Sdata, Sid);
    setTextCorC(Sdata, ScorC);
    setTextCorP(Sdata, ScorP);
    setTextX(Sdata, Sx);
    setTextY(Sdata, Sy);
    setTextA(Sdata, Sa);
    setTextText(Sdata, Stext);
    setTextType(Sdata, 't');
    setTextProtec(Sdata, 5);
    setTextVida(Sdata, 1);
}

void* CriaTexto(int id, char corC[], char corP[], double x, double y, char a, char text[]){
    PrivateText* Text = callocDataT();
    setFullText(Text,id,corC,corP,x,y,a,text);
    Text->area = 0.1;
    return Text;
};
bool checkText(void* n){
    PrivateText* Text = (PrivateText*) n;
    if (Text->type == 't'){
        return true;
    } else {
        return false;
    }
}

void freeText(void* data){
PrivateText* forma = data;
free(forma);
}

//aloca memoria suficiente para uma struct de dados
void* callocDataT() {
    PrivateText* Text = calloc(1, sizeof(PrivateText));
    return Text;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
int getTextId(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->id;
}
char* getTextCorC(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->corC;
}
char* getTextCorP(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->corP;
}
double getTextX(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->x;
}
double getTextY(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->y;
}
char getTextA(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->a;
}
char* getTextText(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->text;
}
double getTextArea(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->area;
}
double getTextProtec(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->protec;
}
char getTextType(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->type;
}
int getTextVida(void* Sdata) {
    PrivateText* Text = Sdata;
    return Text->vida;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setTextId(void* Sdata, int Sid) {
    PrivateText* Text = Sdata;
    Text->id= Sid;
}
void setTextCorC(void* Sdata, char ScorC[]) {
    PrivateText* Text = Sdata;
    strcpy(Text->corC, ScorC);
    //Text->corC= ScorC;
}
void setTextCorP(void* Sdata, char ScorP[]) {
    PrivateText* Text = Sdata;
    strcpy(Text->corP, ScorP);

    //Text->corP= ScorP;
}
void setTextX(void* Sdata, double Sx) {
    PrivateText* Text = Sdata;
    Text->x = Sx;
}
void setTextY(void* Sdata, double Sy) {
    PrivateText* Text = Sdata;
    Text->y = Sy;
}
void setTextA(void* Sdata, char Sa) {
    PrivateText* Text = Sdata;
    Text->a = Sa;
}
void setTextText(void* Sdata, char Stext[]) {
    PrivateText* Text = Sdata;
    strcpy(Text->text, Stext);
    //Text->text = Stext;
}
void setTextType(void* Sdata, char Stype){
    PrivateText* Text = Sdata;
    Text->type = Stype;
}
void setTextArea(void* Sdata, double Sarea){
    PrivateText* Text = Sdata;
    Text->area = Sarea;
}
void setTextProtec(void* Sdata, double Sprotec){
    PrivateText* Text = Sdata;
    Text->protec = Sprotec;
}
void setTextVida(void* Sdata, int Svida){
    PrivateText* Text = Sdata;
    Text->vida = Svida;
}