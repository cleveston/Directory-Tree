#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char* nome;
    int tipo;
    struct No *pai;
    struct No *filho;
    struct No *direita;
} No;


//Declaração do nó atual como global, possibilitando assim sua utilização em qualquer parte do código.
No *atual;

No* novoNo();
No * procura(char *nome);
No* search(No *a, char* nome);

void executa_comando();
void list();
void rm(char *nome);
void mkdir(char* name, int tipo);
void help();
void cd(char *nome);
void append(char* s, char c);
void libera(No *n);
void limparTela();
void imprimeComandos();
void imprime_no(No *a);
void criaDiretorios(char *caminho);