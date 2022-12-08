#include "libs.h"

#include "lista.h"
#include "circ.h"
#include "rect.h"
#include "line.h"
#include "text.h"
#include "system.h"
#include "path.h" 
#include "svg.h"
#include "qry.h"
#include "cpt.h"

int main (int argc, char** argv){
    
    //cria os paths todos
    void* paths = createAllPaths();
    if(readParam(argc, argv, paths) == -1)// le os parametros
    {
        return 0;
    } 
    
    CPTree tree = createCPT(0.5) ;
    readPrintGeo(tree, paths);// le o .geo
    
    if(getQryArq(paths))
    {   
        readQry(tree, paths); //le o .qry
    }
    
    killCPT(tree);
    freee(paths);
    return 0;
}