#include "Produto.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } Cor;

typedef struct RBNode {
    Prod *produto;
    Cor cor;

    struct RBNode *esq;
    struct RBNode *dir;
    struct RBNode *pai;
} RBNode;

typedef struct RBTree {
    struct RBNode *raiz;
    struct RBNode *nil;
} RBTree;

RBTree *initialize();

void inserirNo(RBTree *arvore, char *codProd);
void removerNo(RBTree *arvore, char *codProd);
void alterarProduto(RBTree *arvore, char *codProd);

void rotDir(RBTree *arvore, RBNode *novo);
void rotEsq(RBTree *arvore, RBNode *novo);

Prod *buscar(RBNode *raiz, RBNode *nil, char *codProd);
RBNode *criarRBNode(Prod *produto, RBNode *nil);
RBNode *criarSentinela();

RBNode *min(RBTree *arvore, RBNode *novo);

void emOrdem(RBNode *raiz, RBNode *nil);
void exibirEmOrdem(RBTree *arvore);
void porNivel(RBTree *arvore);
void destroy(RBTree *arvore);
