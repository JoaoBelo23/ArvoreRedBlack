#include "TreeRedBlack.h"
#include <string.h>

typedef struct queueNode {
    RBNode *no;
    struct queueNode *prox;
} queueNode;

typedef struct queue {
    queueNode *inicio;
    queueNode *fim;
} Queue;

void initializeQueue(Queue *p) {

    p->inicio = NULL;
    p->fim = NULL;
}

bool isQueueEmpty(Queue *p) { return p->inicio == NULL; }

void enQueue(Queue *p, RBNode *no) {
    queueNode *novo;
    novo = (queueNode *)malloc(sizeof(queueNode));
    if (novo == NULL) return;

    novo->no = no;
    novo->prox = NULL;
    if (isQueueEmpty(p)) {
        p->inicio = novo;
        p->fim = novo;
    } else {
        p->fim->prox = novo;
        p->fim = novo;
    }
}

RBNode *deQueue(Queue *p) {
    queueNode *q;
    RBNode *nozinho;

    if (isQueueEmpty(p)) return NULL;

    q = p->inicio;
    p->inicio = p->inicio->prox;

    nozinho = q->no;
    free(q);
    if (p->inicio == NULL) { p->fim = NULL; }
    return nozinho;
}

RBNode *criarRBNode(Prod *produto, RBNode *nil) {

    RBNode *novoNo = (RBNode *)malloc(sizeof(RBNode));

    if (novoNo == NULL) return NULL;

    novoNo->produto = produto;
    novoNo->cor = RED;
    novoNo->dir = nil;
    novoNo->esq = nil;
    novoNo->pai = nil;

    return novoNo;
}
RBNode *criarSentinela() {

    RBNode *nil = (RBNode *)malloc(sizeof(RBNode));

    if (nil == NULL) return NULL;

    nil->cor = BLACK;
    nil->dir = nil;
    nil->esq = nil;
    nil->pai = nil;
    nil->produto = NULL;

    return nil;
}

RBTree *initialize() {
    RBTree *arvore = (RBTree *)malloc(sizeof(RBTree));

    if (arvore == NULL) return NULL;

    arvore->nil = criarSentinela();

    if (arvore->nil == NULL) {
        free(arvore);
        return NULL;
    }
    arvore->raiz = arvore->nil;

    return arvore;
}

Prod *buscar(RBNode *raiz, RBNode *nil, char *codProd) {
    RBNode *NoBuscar = raiz;

    if (NoBuscar == nil) return NULL;

    if (strcmp(codProd, NoBuscar->produto->codProd) == 0) {
        return NoBuscar->produto;
    } else if (strcmp(codProd, NoBuscar->produto->codProd) < 0) {
        return buscar(NoBuscar->esq, nil, codProd);
    } else {
        return buscar(NoBuscar->dir, nil, codProd);
    }
}

void emOrdem(RBNode *raiz, RBNode *nil) {
    if (raiz != nil) {
        emOrdem(raiz->esq, nil);
        exibirProd(raiz->produto);
        printf("Cor do no: %s\n", raiz->cor == RED ? "RED" : "BLACK");
        emOrdem(raiz->dir, nil);
    }
}
void exibirEmOrdem(RBTree *arvore) {
    if (arvore->raiz == arvore->nil) {
        printf("Arvore esta vazia");
    } else {
        emOrdem(arvore->raiz, arvore->nil);
    }
}
RBNode *min(RBTree *arvore, RBNode *novo) {
    while (novo->esq != arvore->nil) { novo = novo->esq; }

    return novo;
}
void destroy(RBTree *arvore) {
    RBNode *No;
    Queue filaNo;
    if (arvore->raiz == arvore->nil) {
        printf("Arvore vazia");
    } else {
        initializeQueue(&filaNo);
        No = arvore->raiz;
        enQueue(&filaNo, No);
        while (!isQueueEmpty(&filaNo)) {
            No = deQueue(&filaNo);
            if (No->esq != arvore->nil) { enQueue(&filaNo, No->esq); }
            if (No->dir != arvore->nil) { enQueue(&filaNo, No->dir); }
            destroyProd(No->produto);
            free(No);
        }
    }
    free(arvore->nil);
    free(arvore);
}
void porNivel(RBTree *arvore) {
    RBNode *No;
    Queue filaNo;
    if (arvore->raiz == arvore->nil) {
        printf("Arvore vazia");
    } else {
        initializeQueue(&filaNo);
        No = arvore->raiz;
        enQueue(&filaNo, No);
        while (!isQueueEmpty(&filaNo)) {
            No = deQueue(&filaNo);
            if (No == arvore->nil) {
                printf("null\n");
            } else {
                enQueue(&filaNo, No->esq);
                enQueue(&filaNo, No->dir);
                exibirProd(No->produto);
                printf("Cor do no: %s\n", No->cor == RED ? "RED" : "BLACK");
            }
        }
        printf("\n");
    }
}
void rotEsq(RBTree *arvore, RBNode *x) {
    RBNode *y = x->dir;

    x->dir = y->esq;

    if (y->esq != arvore->nil) y->esq->pai = x;

    y->pai = x->pai;

    if (x->pai == arvore->nil) arvore->raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

void rotDir(RBTree *arvore, RBNode *y) {
    RBNode *x = y->esq;

    y->esq = x->dir;

    if (x->dir != arvore->nil) x->dir->pai = y;

    x->pai = y->pai;

    if (y->pai == arvore->nil) arvore->raiz = x;
    else if (y == y->pai->esq)
        y->pai->esq = x;
    else
        y->pai->dir = x;

    x->dir = y;
    y->pai = x;
}

void inserirAjuste(RBTree *arvore, RBNode *novo) {
    while (novo->pai->cor == RED) {
        if (novo->pai == novo->pai->pai->esq) {
            RBNode *tio = novo->pai->pai->dir;
            if (tio->cor == RED) {
                novo->pai->cor = BLACK;
                tio->cor = BLACK;
                novo->pai->pai->cor = RED;
                novo = novo->pai->pai;
            } else {
                if (novo == novo->pai->dir) {
                    novo = novo->pai;
                    rotEsq(arvore, novo);
                }
                novo->pai->cor = BLACK;
                novo->pai->pai->cor = RED;
                rotDir(arvore, novo->pai->pai);
            }
        } else {
            RBNode *tio = novo->pai->pai->esq;
            if (tio->cor == RED) {
                novo->pai->cor = BLACK;
                tio->cor = BLACK;
                novo->pai->pai->cor = RED;
                novo = novo->pai->pai;
            } else {
                if (novo == novo->pai->esq) {
                    novo = novo->pai;
                    rotDir(arvore, novo);
                }
                novo->pai->cor = BLACK;
                novo->pai->pai->cor = RED;
                rotEsq(arvore, novo->pai->pai);
            }
        }
    }
    arvore->raiz->cor = BLACK;
}

void alterarProduto(RBTree *arvore, char *codProd) {
    if (arvore->raiz == arvore->nil) return;

    RBNode *mudarNo = arvore->raiz;
    alterarProd(buscar(mudarNo, arvore->nil, codProd));
}

void inserirNo(RBTree *arvore, char *codProduto) {
    RBNode *novo = arvore->raiz;
    RBNode *pai = arvore->nil;

    while (novo != arvore->nil) {
        pai = novo;
        if (strcmp(codProduto, novo->produto->codProd) == 0) {
            printf("Produto ja existe\n");
            return;
        } else if (strcmp(codProduto, novo->produto->codProd) < 0) {
            novo = novo->esq;
        } else {
            novo = novo->dir;
        }
    }
    Prod *Produto = cadastrarProd(codProduto);

    if (Produto == NULL) {
        printf("Produto nao foi criado\n");
        return;
    }

    RBNode *novoNo = criarRBNode(Produto, arvore->nil);

    if (novoNo == NULL) {
        destroyProd(Produto);
        printf("No nao foi criado\n");
        return;
    }

    novoNo->pai = pai;

    if (pai == arvore->nil) {
        arvore->raiz = novoNo;
        novoNo->cor = BLACK;
    } else if (strcmp(codProduto, pai->produto->codProd) < 0) {
        pai->esq = novoNo;
    } else {
        pai->dir = novoNo;
    }

    inserirAjuste(arvore, novoNo);
}

void transplante(RBTree *arvore, RBNode *u, RBNode *v) {
    if (u->pai == arvore->nil) {
        arvore->raiz = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }

    v->pai = u->pai;
}

void removerAjuste(RBTree *arvore, RBNode *novo) {
    while (novo != arvore->raiz && novo->cor == BLACK) {
        if (novo == novo->pai->esq) {
            RBNode *irmao = novo->pai->dir;

            if (irmao->cor == RED) {
                irmao->cor = BLACK;
                novo->pai->cor = RED;
                rotEsq(arvore, novo->pai);
                irmao = novo->pai->dir;
            }

            if (irmao->esq->cor == BLACK && irmao->dir->cor == BLACK) {
                irmao->cor = RED;
                novo = novo->pai;
            } else {
                if (irmao->dir->cor == BLACK) {
                    irmao->esq->cor = BLACK;
                    irmao->cor = RED;
                    rotDir(arvore, irmao);
                    irmao = novo->pai->dir;
                }

                irmao->cor = novo->pai->cor;
                novo->pai->cor = BLACK;
                irmao->dir->cor = BLACK;
                rotEsq(arvore, novo->pai);
                novo = arvore->raiz;
            }
        } else {
            RBNode *irmao = novo->pai->esq;

            if (irmao->cor == RED) {
                irmao->cor = BLACK;
                novo->pai->cor = RED;
                rotDir(arvore, novo->pai);
                irmao = novo->pai->esq;
            }

            if (irmao->dir->cor == BLACK && irmao->esq->cor == BLACK) {
                irmao->cor = RED;
                novo = novo->pai;
            } else {
                if (irmao->esq->cor == BLACK) {
                    irmao->dir->cor = BLACK;
                    irmao->cor = RED;
                    rotEsq(arvore, irmao);
                    irmao = novo->pai->esq;
                }

                irmao->cor = novo->pai->cor;
                novo->pai->cor = BLACK;
                irmao->esq->cor = BLACK;
                rotDir(arvore, novo->pai);
                novo = arvore->raiz;
            }
        }
    }

    novo->cor = BLACK;
}
void removerNo(RBTree *arvore, char *codProduto) {
    RBNode *z = arvore->raiz;
    while (z != arvore->nil && strcmp(codProduto, z->produto->codProd) != 0) {
        if (strcmp(codProduto, z->produto->codProd) < 0) {
            z = z->esq;
        } else {
            z = z->dir;
        }
    }

    if (z == arvore->nil) {
        printf("Produto nao existe\n");
        return;
    }

    RBNode *y = z;
    RBNode *x;
    Cor corOriginal = y->cor;

    if (z->esq == arvore->nil) {
        x = z->dir;
        transplante(arvore, z, z->dir);
    } else if (z->dir == arvore->nil) {
        x = z->esq;
        transplante(arvore, z, z->esq);
    } else {
        y = min(arvore, z->dir);

        corOriginal = y->cor;
        x = y->dir;

        if (y->pai == z) {
            x->pai = y;
        } else {
            transplante(arvore, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }

        transplante(arvore, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    destroyProd(z->produto);
    free(z);

    if (corOriginal == BLACK) { removerAjuste(arvore, x); }
}
