#include "arvore.h"

int main() {

    FILE *arquivo;
    atual = novoNo();                                           //Cria a raiz

    char *string = (char*) malloc(100 * sizeof (char));         //Aloca a string que receberá a linha do arquivo

    arquivo = fopen("in.txt", "r");                             //Abre o arquivo
    printf("\n------ TERMINAL DE COMANDOS --------\n\n");
    if (arquivo != NULL) {

        do {
            fgets(string, 100, arquivo);                        //Obtem uma linha do arquivo

            if (*(string) != '\n' && *(string) != '\0')         //Se a linha nao for em branco
                criaDiretorios(string);                         //Chama a função que criará a arvore de diretórios

            *(string) = NULL;

        } while (!feof(arquivo));                               //Repete até o final do arquivo

        fclose(arquivo);                                        //Fecha o arquivo
        free(string);                                           //Libera a string

    } else
        printf("Arquivo nao encontrado. Verifique se o nome é 'in.txt'.\n");

    executa_comando();                                          //Chama a função que escutará os comandos do usuário

    return 0;
}
