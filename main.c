/*********************************************************************/
/**   Algoritmos e Estruturas de Dados I                            **/
/**   EACH-USP - Segundo Semestre de 2022                           **/
/**   Turma 94 - Prof. Flavio Coutinho                              **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Andreas Hukuhara Christe                   13673110           **/
/**   Bruno Friedrich Raquel                     13672450           **/
/**   Matheus Silva Lopes da Costa               12674680           **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "arvore_binaria.h"
#include "lista_sequencial_ordenada.h"

#define TAMANHO 1000
void print_menu() { puts("uso correto:  ./ep1 (texto).txt (estrutura)"); }
int main(int argc, char **argv) {
  ListaSequencial *lista = cria_lista(1000);
  Arvore *arvore = cria_arvore();

  No *buscando;
  char resposta[20];
  char palavra_buscada[20];

  char texto[8000][TAMANHO + 1];
  FILE *in;
  char *linha;
  char *copia_ponteiro_linha;
  char *quebra_de_linha;
  char *palavra;
  int contador_linha;
  int n = 0; // posicao da busca
  int aux;
  clock_t tsrc;
  clock_t t = clock();
  if (argc == 3 &&
      (!(strcasecmp(argv[2], "lista")) || !(strcasecmp(argv[2], "arvore")))) {
    aux = strcasecmp(argv[2], "arvore");
    in = fopen(argv[1], "r");

    contador_linha = 0;
    linha = (char *)malloc((TAMANHO + 1) * sizeof(char));

    while (in && fgets(linha, TAMANHO, in)) {

      if ((quebra_de_linha = strrchr(linha, '\n')))
        *quebra_de_linha = 0;
      strcpy(texto[contador_linha], linha);

      copia_ponteiro_linha = linha;
      while ((palavra = strsep(&copia_ponteiro_linha, " (),-.?!:/;|\"'"))) {
        if (palavra[0] > 0) {
          aux ? insere(lista, palavra, contador_linha)
              : insere_ord(arvore, palavra, contador_linha);
        }
      }
      contador_linha++;
    }
    t = clock() - t;
    printf("Tipo de indice: '%s'\n", argv[2]);
    printf("Arquivo de texto: '%s'\n", argv[1]);
    printf("Numero de linhas no arquivo: %d\n", contador_linha);
    printf("Tempo para carregar o arquivo e construir o indice: %f ms\n",
           (1000 * ((float)t / CLOCKS_PER_SEC)));

    while (1) {
      printf("> ");
      scanf("%s%*c", resposta);
      if (!strcmp(resposta, "fim"))
        return 0;
      scanf("%s%*c", palavra_buscada);
      if (!strcmp(resposta, "busca")) {
        if (aux) {
          tsrc = clock();
          n = busca(lista, palavra_buscada);
          tsrc = clock() - tsrc;
          if (n >= 0) {
            printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) "
                   "linha(s):\n",
                   lista->lista[n].Total, palavra_buscada);
            for (int i = 0; i < lista->lista[n].linhas.size; i++)
              if (lista->lista[n].linhas.linha[i] !=
                  lista->lista[n].linhas.linha[i + 1]) {
                printf("%05d: %s\n", lista->lista[n].linhas.linha[i] + 1,
                       texto[lista->lista[n].linhas.linha[i]]);
              }
          } else {
            printf("Palavra '%s' nao encontrada.\n", palavra_buscada);
          }
          printf("Tempo de busca: %f ms\n",
                 (1000 * ((float)tsrc / CLOCKS_PER_SEC)));
        } else {
          tsrc = clock();
          buscando = busca_bin(arvore, palavra_buscada);
          tsrc = clock() - tsrc;
          if (buscando) {
            printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) "
                   "linha(s):\n",
                   buscando->Total, palavra_buscada);
            for (int i = 0; i <= buscando->linhas.size; i++)
              printf("%05d: %s\n", buscando->linhas.linha[i] + 1,
                     texto[buscando->linhas.linha[i]]);
          } else {
            printf("Palavra '%s' nao encontrada.\n", palavra_buscada);
          }
          printf("Tempo de busca: %f ms\n",
                 (1000 * ((float)tsrc / CLOCKS_PER_SEC)));
        }
      } else {
        printf("Opcao Invalida!\n");
      }
    }
    return 0;
  }
  print_menu();
  return 0;
}
