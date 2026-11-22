#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
    char codProd[21];
    char descricaoProd[51];
    double precoProd;
    int qtdEstoqueProd;
} Prod;

Prod *cadastrarProd(char *codProduto);
void destroyProd(Prod *produto);
void exibirProd(Prod *produto);
void alterarProd(Prod *produto);
void limpaBuffer();
