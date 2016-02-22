#include "arvore.h"


No* novoNo() {                                           //Função que aloca um novo nó da árvore 
    No* n = (No*) malloc(sizeof (No));          
    n->nome = (char*) malloc(100 * sizeof (char));
    n->direita = NULL;
    n->filho = NULL;
    n->pai = NULL;
    return n;
}

//Função para acessar diretórios da árvore
void cd(char *nome) {
    int imp = 0;                                        //variável auxiliar pra imprimir ou não a mensagem "Diretorio não encontrado.\n"
    if (!strcmp(nome, "..")) {                          //se a string nome for igual a "..", então o nó atual passa a ser seu pai
        if (atual->pai != NULL)
            atual = atual->pai;
    } else {
        No *existe = procura(nome);                     //procura de o diretório informado pelo usuário existe, se não encontrado recebe NULL

        if (existe != NULL && existe->tipo == 1)        //diretório encontrado atualiza o nó atual
            atual = existe;
        else {
            if (atual->filho != NULL) {                 //se filho do atual não for nulo executa a procura por sugestões
                No *n = atual->filho;                   //recebe o nó filho do atual
                while (n != NULL) {                     //percorre a lista que é formada pelos filhos de atual
                    int p = 0;                          //variável pra auxiliar na possível impressão da sugestão
                    char *c = n->nome;                  // c recebe a string de n
                    int i= 0;                           
                    while(*(nome+i) != '\0'){           //percorre a string, caracter por caracter, até encontrar o caracter '\0'
                        if(*(nome+i) != *(c+i)){        //compara caracter por caracter do diretório do usuario e o da arvore em busca de desigualdade
                            p =1;                       //se pelo menos um dos caracteres for diferente, altera o valor de p
                            break;                      
                        }
                        i++;                            
                    }
                    if(p == 0){                         //se o valor de p não foi alterado, então existe uma igualdade entre o diretório informado pelo usuário e a parte inicial da string do nó
                        printf("%s\n",n->nome);         //imprime a sugestão
                        imp = 1;                        //altera o valor de imp para não imprimir "Diretorio nao encontrado.\n", pois já foi impressa sugestões
                    }
                    n = n->direita;                     //aponta para o próximo nó da direita
                }
            }
            if(imp == 0)                                //imprime se o diretório e nenhuma sugestão foi encontrada
                printf("Diretorio nao encontrado.\n");
        }
    }
}

void list() {                                           //Lista todos os diretórios e arquivos contidos dentro do nó atual
    No *filho = atual->filho;                           
    if (filho != NULL) {                                //se o diretório não está vazio

        while (filho != NULL) {                         //percorre e imprime os nós ali contidos
            printf("%s\n", filho->nome);
            filho = filho->direita;
        }
    } else                                              //se o diretório não conter nenhum nó a mensagem é impressa
        printf("Diretorio vazio.\n");
}

void rm(char *nome) {                                   

    No *n = procura(nome);                              //procura o nó que será removido caso exista
    
    if (n != NULL) {                                    //se o nó foi encontrado
        No *direita = n->direita;               

        if (atual->filho == n)                          //caso nó a ser removido seja o filho do nó atual, atualiza o atual->filho para ser o atual->filho->direita
            atual->filho = direita;
        else {
            No *ant = atual->filho;                     //laço para encontrar o nó anterior ao que será removido
            while (ant->direita != n)
                ant = ant->direita;
            ant->direita = n->direita;                  //anterior aponta para o próximo nó depois do que será removido

        }

        if (n->tipo == 1)                               //se o tipo era 1, foi removido uma pasta
            printf("Diretorio removido.\n");
        else                                            //se o tipo era 0, foi removido um arquivo
            printf("Arquivo removido.\n");

        n->direita = NULL;                              //anula o ponteiro direita do nó a ser liberado, para não liberar sua direita
        libera(n);                                      //libera o nó n e seus filhos, caso existirem.

    } else
        printf("Diretorio nao encontrado.\n");          //se não encontrou o nó contendo a string do parâmetro
}

void mkdir(char* name, int tipo) {                      //função que cria os diretórios

    No * existe = procura(name);                        //procura para ver se o diretório ou arquivo já existe

    if (!existe) {                                      //se não existir é criado um novo nó 

        No *n = novoNo();

        strcpy(n->nome, name);                          //copia a string name para o nó

        n->tipo = tipo;                                 //recebe o tipo do nó: se tipo= 1 é um diretório, se tipo = 0 é um arquivo
        n->pai = atual;                                 //recebe o apontamento para o seu pai que é o atual

        if (atual->filho == NULL) {                     //insere o nó como sendo filho do atual se atual->filho for nulo
            atual->filho = n;
        } else {                                        //percorre a lista para a direita, até encontrar o final e insere o novo nó lá
            No *aux = atual->filho;     

            while (aux->direita != NULL) {
                aux = aux->direita;
            }
            aux->direita = n;

        }
        if (tipo)                                       //caso tipo=1, diretório
            printf("Diretorio '%s' criado.\n", name);
        else                                            //caso contrário, arquivo
            printf("Arquivo '%s' criado.\n", name);
    } else                                              //se nó existe recebeu um nó não nulo, então o diretório já existe
        printf("Diretorio ja existe.\n");

}

No* search(No *a, char* nome) {                         
    if (a != NULL) {                                                                     //Verifica se o nó nao é nulo
        if (!strcmp(a->nome, nome)) {                                                     //Verifica se a informaçao é a procurada
            imprime_caminho(a);                                                           //Chama a função que imprime o caminho do diretório/arquivo
            return a;                                                    //Retorna o dó com a informação
        } else
            return (search(a->filho, nome) || search(a->direita, nome));                //Chama a função recursivamente
    } else
        return NULL;
}

No* procura(char *nome) {                       //procura um nó a partir de uma string recebida como parametro

    if (atual->filho != NULL) {                 //começa pelo filho do nó atual se ele não for nulo
        No *n = atual->filho;

        while (n != NULL) {                     //percorre somente o nível de atual->filho em busca do nó que contenha string igual a do parametro
            if (!strcmp(n->nome, nome))         //compara as strings
                break;                          //se nó encontrado encerra laço
            n = n->direita;
        }

        return n;                               //retorna nó que contém string igual ao parametro, ou então NULL se forem diferentes ao final da execução do laço
    }
}

void libera(No *n) {                             //libera um nó e seus filhos
    if (n != NULL) {
        libera(n->filho);                        //recursão pra liberar os nós filhos   
        libera(n->direita);                     //recursão pra liberar os nós da direita        
        free(n->nome);                          //libera a string alocada dinamicamente
        free(n);                                //libera o nó recebido como parâmetro
    }
}

void append(char* s, char c) {                  //Função que concatena caracteres em uma string
    while (*(s) != NULL)
        s++;
    *(s++) = c;
    *(s++) = '\0';                              //mantém o '\0' sempre no final da string
}

void limparTela() {                                                     //Limpa a tela com uma sequência de '\n'
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void imprimeComandos() {                                                        //imprime os comandos que podem ser utilizados pelo usuário

    limparTela();
    printf("--------------------------COMANDOS------------------------\n\n");
    printf("cd <dir> - Acessa um diretorio\n");
    printf("------------------------------------------------------------\n");
    printf("search <dir/arq> - Procura um diretorio um arquivo\n");
    printf("------------------------------------------------------------\n");
    printf("rm <dir> - Apaga um diretorio\n");
    printf("------------------------------------------------------------\n");
    printf("list - Lista os diretorios e arquivos do diretorio atual\n");
    printf("------------------------------------------------------------\n");
    printf("mkdir - Cria um diretorio novo\n");
    printf("------------------------------------------------------------\n");
    printf("clear - Limpa a tela\n");
    printf("------------------------------------------------------------\n");
    printf("help - Mostra o menu de ajuda\n");
    printf("------------------------------------------------------------\n");
    printf("exit - Sair do programa\n");
    printf("------------------------------------------------------------");

}

void imprime_caminho(No *a) {                                   //imprime o caminho do diretório até a raiz
    if (a != NULL) {
        imprime_caminho(a->pai);                                //uso de recursividade para imprimir primeiro o pai do nó selecionado
        if (a->nome)                                            
            printf("%s", a->nome);                              //imprime o diretório atual
        printf("/");
    }

}

void executa_comando() {                                    //função que lê a instrução, separa em comando e diretório, e chama as funções que executam os comandos
    
    char string[100];                                       
    char comando[100];
    char diretorio[100];
    int sair = 1;                                           //Variável utilizada para encerrar a execução do programa

    do {
        printf("\n < ");                                    //é impresso o diretório atual para o usuário saber onde ele está
        No *n = atual;                                  
        imprime_caminho(n);
        printf(" $> ");

        gets(string);                                       //leitura da string que contém a instrução
        int i = 0;      
        while ((string[i] != ' ') && (string[i] != '\0')) { //Laço que copia o comando da string instrução para a string comando
            comando[i] = string[i];
            i++;
        }
        comando[i] = '\0';                                  //insere o caracter '\0' no final da string comando
        int j = 0;
        if (string[i] != '\0') {
            while (string[i] != '\0') {                     //Laço que copia o diretório da string instrução para a string comando
                i++;
                diretorio[j] = string[i];
                j++;
            }
            diretorio[j] = '\0';                           //insere o caracter '\0' no final da string diretório
        }

        if (!strcmp(comando, "cd")) {                      //se a string comando  for igual a "cd", chama a função cd com a string diretório como parâmetro 
            cd(diretorio);
        } else if (!strcmp(comando, "search")) {           //se a string comando  for igual a "search", chama a função search com a string diretório e o filho do nó atual como parâmetros 
            if (!search(n->filho, diretorio))              //imprime o diretório na própria função search se ele for encontrado
                printf("Diretorio/arquivo '%s' nao encontrado", diretorio);     //caso não encontrado é impressa essa mensagem
        } else if (!strcmp(comando, "rm")) {               //se a string comando  for igual a "rm", chama a função rm com a string diretório como parâmetro 
            rm(diretorio);
        } else if (!strcmp(comando, "list")) {             //se a string comando  for igual a "list", chama a função list       
            list();
        } else if (!strcmp(comando, "mkdir")) {            //se a string comando  for igual a "mkdir", chama a função mkdir com a string diretório e tipo=1, pois será uma pasta, como parâmetros  
            if(diretorio[0] == '\0')
                printf("Diretorio invalido\n");
            else
                mkdir(diretorio, 1);
        } else if (!strcmp(comando, "clear")) {            //se a string comando  for igual a "clear", chama a função clear
            limparTela();       
        } else if (!strcmp(comando, "help")) {             //se a string comando  for igual a "help" chama a função help
            imprimeComandos();
        } else if (!strcmp(comando, "exit")) {             //se a string comando  for igual a "exit"
            No *raiz = atual;
            while (raiz->pai != NULL)                      //atualiza nó atual para ser o raiz
                raiz = raiz->pai;

            libera(raiz);                                  //chama a função que irá liberar toda a árvore
            sair = 0;                                      //altera a variável sair pra encerrar a execução do programa
        } else
            printf("Comando nao encontrado. Digite 'help' para ajuda.\n");


    } while (sair);                                        //executa enquanto sair não for alterado pra 0 por exit
}

void criaDiretorios(char *caminho) {                       //cria o diretório a partir da string caminho informada      

    char *aux = caminho;                                   //Recebe linha do arquivo
    while (*(aux) != NULL) {                               
        char *concatenar = (char*) malloc(100 * sizeof (char));         //Aloca string para concatenação
        *concatenar = NULL;
        
        while (*(aux) != '/' && *(aux) != '\0' && *(aux) != '\n') {     //Enquanto char diferente de '/' ou '\n' ou fim de linha
            append(concatenar, *(aux));                                 //Chama a função que concatena um char no final da string
            aux++;
        }

        No *existe = procura(concatenar);                               //Verifica se o nome já existe
        int tipo = strchr(concatenar, '.') ? 0 : 1;                     //Verifica se existe o char '.' no nome

        if (existe == NULL)                             //Se o diretório já existe
            mkdir(concatenar, tipo);                    //Cria o diretório
        else if (tipo)                                  //Caso contrário 
            cd(concatenar);                             //Acessa o diretório

        aux++;
        free(concatenar);                               //Libera a string
    }

    //Sobe para a raiz
    No *raiz = atual;
    while (raiz->pai != NULL)                           //Sobe até o nó pai
        raiz = raiz->pai;

    atual = raiz;                                      //Atualiza o nó atual
}