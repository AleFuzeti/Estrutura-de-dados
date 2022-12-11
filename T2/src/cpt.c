#include "libs.h"
#include "cpt.h"
#include "lista.h"

typedef void *Info;

typedef struct Node{
      //ancoras
      double x,y;
      //ponteiros
      struct Node *left, *right, *pai;
      //info
      Info info;
      //circulo minimo da figura
      double xc,yc,r;
      //circulo minimo subarvores
      double subxc,subyc,subr;
}Node; 

typedef struct Tree{
      Node *raiz;
      int size;
      double epsilon;
}Tree;

typedef void (*VisitaNo)(double x, double y, Info info, double xc, double yc, double r, void *extra);

//calculando a circunferencia que envolve o no'
void getCircSub(Node* n, double* xc, double* yc, double* r)
{
      Node* node = n;
      if (!node->left || !node->right)
      {
            *xc = node->xc;
            *yc = node->yc;
            *r = node->r;
      }
      else
      {
            *xc = node->subxc;
            *yc = node->subyc;
            *r = node->subr;
      }
}

void uneCirc(double x1, double y1, double r1,  double x2, double y2, double r2, double* x3, double* y3, double* r3)
{
    double r = r1 > r2 ? r1 : r2;
    *x3 = (x1 + x2)/2;
    *y3 = (y1 + y2)/2;
    *r3 = sqrt(pow(2,x1-x2)+pow(2,y1-y2))/2 + r;

}

void corrigeCircSubArv(Node* node)
{
      Node* p = node;
      do
      {
            double x1, y1, r1, x2, y2, r2, x3, y3, r3;
            if (p->left){
                  getCircSub(p->left, &x1, &y1, &r1);
            }
            else{
                  getCircSub(p, &x1, &y1, &r1);
            }
            if (p->right){
                  getCircSub(p->right, &x2, &y2, &r2);
            }
            else{
                  getCircSub(p, &x2, &y2, &r2);
            }
            uneCirc(x1, y1, r1, x2, y2, r2, &x3, &y3, &r3);
            uneCirc(x3, y3, r3, p->x, p->y, p->r, &p->subxc, &p->subyc, &p->subr);
            p = p->pai;
      } while (p);
}

//funcoes auxiliares

Node* minimumNode(Node* x)
{
      while (x->left)
      {
            x = x->left;
      }
      return x;
}

void leftRotate(CPTree t, Node* x)
{
    Node* y = x->right;
    x->right = NULL;
    if (y)
    {
        if (y->left)
        {
            x->right = y->left;
        }
        if (y->left)
        {
            y->left->pai = x;
        }
        y->pai = x->pai;
        if (!x->pai)
        {
            Tree* tre = t;
            tre->raiz = y;
        }
        else if (x == x->pai->left)
        {
            x->pai->left = y;
        }
        else
        {
            x->pai->right = y;
        }
        y->left = x;
        x->pai = y;
    }
}

void rightRotate(CPTree t, Node* x)
{
    Node* y = x->left;
    x->left = NULL;
    if (y)
    {
        if (y->right)
        {
            x->left = y->right;
        }
        if (y->right)
        {
            y->right->pai = x;
        }
        y->pai = x->pai;
        if (!x->pai)
        {
            Tree* tre = t;
            tre->raiz = y;
        }
        else if (x == x->pai->right)
        {
            x->pai->right = y;
        }
        else
        {
            x->pai->left = y;
        }
        y->right = x;
        x->pai = y;
    }
}   

int achaAltura(Node* n)
{
      Node* node = n;
      if (!node)  return 0;
    
      int left = achaAltura(node->left);
      int right = achaAltura(node->right);
      if (left > right)
      {
            return left + 1;
      }
      else
      {
            return right + 1;
      }
}

void levelOrder(Node* n, int level, VisitaNo vf, void* extra){     
      Node* node = n;
      if (!node) return;

      if (level == 1)
      {
            vf(node->x, node->y, node->info, node->xc, node->yc, node->r, extra);
      } else if (level > 1){
            levelOrder(node->left, level - 1, vf, extra);
            levelOrder(node->right, level - 1, vf, extra);
      }
}

void recursiveSimetrico(Node* node, VisitaNo fVisita, void* extra)
{
      if (node)
      {
            void* right = node->right;
            recursiveSimetrico(node->left, fVisita, extra);
            fVisita(node->x, node->y, node->info, node->xc, node->yc, node->r, extra);
            recursiveSimetrico(right, fVisita, extra);
      }
      else return;
}

void recursiveProfundidade(Node* node, VisitaNo vf, void* extra)
{
      if (node)
      {
            void* left = node->left;
            void* right = node->right;
            vf(node->x, node->y, node->info, node->xc, node->yc, node->r, extra);
            recursiveProfundidade(left, vf, extra);
            recursiveProfundidade(right, vf, extra);
      }
      else return;
}

void recursiveFree(Node* node)
{
      if (!node) return;

      free(node->info);

      recursiveFree(node->left);
      recursiveFree(node->right);

      free(node);
}

bool recursiveSearch(Node* raiz, double x, double y, Info *info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra)
{
      if(!raiz) return false;
      
      vfindo(raiz->x, raiz->y, raiz->info, raiz->xc, raiz->yc, raiz->r, extra);

      if(x < raiz->x || y < raiz->y)
      {
            recursiveSearch(raiz->left, x, y, *info, vfindo, vfvoltando, extra);
      } 
      else if(x > raiz->x || y > raiz->y)
      {
            recursiveSearch(raiz->right, x, y, *info, vfindo, vfvoltando, extra);
      } 
      else
      {
            *info = raiz->info;
            return true;
      }
}

void recursiveFind(Node* raiz, double xc, double yc, double r, void* lista, bool found)
{
      if(raiz){
      if(raiz->x < xc + r && raiz->x > xc - r && raiz->y > yc - r && raiz->y < yc + r)
      {
            insert(lista,raiz->info);
            found = true;
            printf("\n\n\nfound\n\n\n");
      }
      recursiveFind(raiz->left, xc, yc, r, lista, found);
      recursiveFind(raiz->right, xc, yc, r, lista, found);
      } else return;
}

Node* searchNode(Node* node, double pXa, double pYa, double epsilon)
{
      if (node)
      {
      Node* result = NULL;
      if (fabs(node->x - pXa) <= epsilon && fabs(node->y - pYa) <= epsilon)
      {
      result = node;
      }
      else
      {
      if (pXa < node->x || (pXa == node->x && pYa < node->y))
      {
            result = searchNode(node->left, pXa, pYa, epsilon);
      }
      else
      {
            result = searchNode(node->right, pXa, pYa, epsilon);
      }
      }
      return result;
      }
      else
      {
            return NULL;
      }
}

void transplantCPT(CPTree t, Node* u, Node* v)
{
    Tree* tre = t;
    if (!u->pai)
    {
        tre->raiz = v;
    }
    else if (u == u->pai->left)
    {
        u->pai->left = v;
    }
    else
    {
        u->pai->right = v;
    }
    if (v)
    {
        v->pai = u->pai;
    }
}

//Funcoes do cpt.h
 
CPTree createCPT(double epsilon)
{
      Tree* tree = calloc(1, sizeof(Tree));
      if (tree)
      {
            tree->raiz = NULL;
            tree->size = 0;
            tree->epsilon = epsilon;
            return tree;
      } 
      else return NULL;
}

bool insertCPT(CPTree b, double x, double y, Info info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra)
{
      Tree* tree = b;
      if(tree == NULL) return false;

      Node* aux = NULL;
      Node* root = tree->raiz;
      Node* node = calloc(1, sizeof(Node));
      node->x = x;
      node->y = y;
      node->xc = x;
      node->yc = y;
      node->r = 1;
      node->info = info;
      node->left = NULL;
      node->right = NULL;
      node->pai = NULL;

      while(root != NULL){
            aux = root;
            vfindo(aux->x,aux->y, info, aux->xc, aux->yc, aux->r, extra);
            
            if(node->x < root->x) root = root->left;
            else if(node->x > root->x) root = root->right;
            else if(node->y < root->y) root = root->left;
            else if(node->y > root->y) root = root->right;
            else return false;
      }

      node->pai = aux;

      if(aux == NULL) tree->raiz = node;
      else if(node->x < aux->x) aux->left = node;
      else if(node->x > aux->x) aux->right = node;
      else if(node->y < aux->y) aux->left = node;
      else if(node->y > aux->y) aux->right = node;
      else return false;

      tree->size++;

      corrigeCircSubArv(node);
      return true;
}

bool searchCPT(CPTree b, double x, double y, Info *info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra)
{
      Tree* tree = (Tree*)b;
      if (tree->raiz)
      {
            return recursiveSearch(tree->raiz, x, y, *info, vfindo, vfvoltando, extra);
      }

      return false;
}

bool removeCPT(CPTree b, double x, double y, Info *info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra)
{
      Tree* tree = b;
      Node* z = searchNode(tree->raiz, x, y, tree->epsilon);
      Node* v = z;
      Node* u = NULL;

      if(!z)
      {
            return NULL;
      }

      if (!z->left)
      {
            u = z->right;
            transplantCPT(b, z, z->right);
      }
      else if (!z->right)
      {
            u = z->left;
            transplantCPT(b, z, z->left);
      }
      else
      {
            v = minimumNode(z->right);
            u = v->right;
            if (v->pai == z)
            {
                  if (x)
                  {
                        u->pai = v;
                  }
            }
            else
            {
                  transplantCPT(b, v, v->right);
                  v->right = z->right;
                  v->right->pai = v;
            }
            transplantCPT(b, z, v);
            v->left = z->left;
            v->left->pai = v;
      }
      tree->size--;

      corrigeCircSubArv(z);
      
      info = z->info;
      free(z);
      return true;            

}

bool findInRegionCPT(CPTree b, double xc, double yc, double r, Lista lres)
{
      Tree* tree = (Tree*)b;
      if(tree == NULL) return false;

      Node* aux = tree->raiz;
      bool res = false;
      recursiveFind(aux, xc, yc, r, lres, res);
      return res;
}

Info getInfoCPT(CPTree b, TreeNode n)
{
      Node* node = (Node*)n;
      if(node == NULL) return NULL;
      return node->info;
}

void getCircCPT(CPTree b, TreeNode n, double *x, double *y, double *r)
{
      Node* node = (Node*)n;
      *x = node->xc;
      *y = node->yc;
      *r = node->r;
      return;
}

void percursoSimetrico(CPTree b, VisitaNo vf, void *extra)
{
      Tree* tree = (Tree*)b;
      recursiveSimetrico(tree->raiz, vf, extra);

}

void dfs(CPTree b, VisitaNo vf, void *extra)
{
      Tree* tree = b;
      recursiveProfundidade(tree->raiz, vf, extra); 
}

void bfs(CPTree b, VisitaNo vf, void *extra)
{
      Tree* tree = b;
      int h = achaAltura(tree->raiz);
      for (int i = 0; i <= h; i++)
      {
            levelOrder(tree->raiz, i, vf, extra);
      } 

}

void killCPT(CPTree b)
{
      Tree* tree = (Tree*)b;
      if(tree == NULL) return;
      recursiveFree(tree->raiz);
      free(tree);
}

