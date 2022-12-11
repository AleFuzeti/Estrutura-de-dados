#include "libs.h"

#include "line.h"

typedef struct Line PrivateLine;

// função que seta todos os dados da struct
void setFullLine(void* Sdata, int Sid, char Scor[], double Sx1, double Sy1, double Sx2, double Sy2){
    setLineId(Sdata, Sid);
    setLineCor(Sdata, Scor);
    setLineX1(Sdata, Sx1);
    setLineY1(Sdata, Sy1);
    setLineX2(Sdata, Sx2);
    setLineY2(Sdata, Sy2);
    setLineType(Sdata, 'l');
    setLineProtec(Sdata, 50);
    setLineArea(Sdata, Sx1, Sy1, Sx2, Sy2);
    setLineVida(Sdata, 1);
}

struct Line {
    char type;
    int id;
    char cor[20];
    double x1;
    double y1;
    double x2;
    double y2;
    double area;
    double protec;
    int vida;
};
void* Crialinha(int id, char cor[], double x1, double y1, double x2, double y2){
    PrivateLine* Line = callocDataL();
    setFullLine(Line,id,cor,x1,y1,x2,y2);
    return Line;
};

bool checkLine(void* n){
    PrivateLine* Line = (PrivateLine*) n;
    if (Line->type == 'l'){
        return true;
    }
    return false;
} 

void freeLine(void* data){
PrivateLine* forma = data;
free(forma);
}

//aloca memoria suficiente para uma struct de dados
void* callocDataL(){
    PrivateLine* Line = calloc(1, sizeof(PrivateLine));
    return Line;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
int getLineId(void* Sdata) {
    PrivateLine* Line = (PrivateLine*)Sdata;
    return Line->id;
} 
char* getLineCor(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->cor;
}
double getLineX1(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->x1;
}
double getLineY1(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->y1;
}
double getLineX2(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->x2;
}
double getLineY2(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->y2;
}
double getLineProtec(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->protec;
}
char getLineType(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->type;
}
double getLineArea(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->area;
}
int getLineVida(void* Sdata) {
    PrivateLine* Line = Sdata;
    return Line->vida;
}
//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setLineId(void* Sdata, int Sid) {
    PrivateLine* Line = Sdata;
    Line->id = Sid;
}
void setLineCor(void* Sdata, char Scor[]) {
    PrivateLine* Line = Sdata;
    strcpy(Line->cor, Scor);
    //Line->cor = Scor;
}
void setLineX1(void* Sdata, double Sx1) {
    PrivateLine* Line = Sdata;
    Line->x1 = Sx1;
}
void setLineY1(void* Sdata, double Sy1) {
    PrivateLine* Line = Sdata;
    Line->y1 = Sy1;
}
void setLineX2(void* Sdata, double Sx2) {
    PrivateLine* Line = Sdata;
    Line->x2 = Sx2;
}
void setLineY2(void* Sdata, double Sy2) {
    PrivateLine* Line = Sdata;
    Line->y2 = Sy2;
}
void setLineType(void* Sdata, char Stype){
    PrivateLine* Line = Sdata;
    Line->type = Stype;
}
void setLineProtec(void* Sdata, double Sprotec){
    PrivateLine* Line = Sdata;
    Line->protec = Sprotec;
}
void setLineArea(void* Sdata, double x, double y, double x2, double y2){
    PrivateLine* Line = Sdata;
    double pitag = pow(x-x2,2)+pow(y-y2,2);
    double area = 0.1 * sqrt(pitag);
    Line->area = area;
}
void setLineVida(void* Sdata, int vida){
    PrivateLine* Line = Sdata;
    Line->vida = vida;
}