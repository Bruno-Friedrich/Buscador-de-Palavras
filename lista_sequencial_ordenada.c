#include "lista_sequencial_ordenada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

ListaSequencial *cria_lista(int capacidade) {
  ListaSequencial *lista = (ListaSequencial *)malloc(sizeof(ListaSequencial));
  lista->capacidade = capacidade;
  lista->livre = 0;
  return lista;
}


int busca(ListaSequencial *lista, char *e) {

  // busca binária! ;)

  int ini = 0;
  int fim = lista->livre - 1;
  int meio;

  while (ini <= fim) {

    meio = (ini + fim) / 2;

    if (strcasecmp(e, lista->lista[meio].palavra) == 0)
      return meio;
    if (strcasecmp(e, lista->lista[meio].palavra) < 0)
      fim = meio - 1;
    if (strcasecmp(e, lista->lista[meio].palavra) > 0)
      ini = meio + 1;
  }
  return -1;
}
Boolean insere(ListaSequencial *list, char *e, int linha) {

  int i = busca(list, e);
  if (i >= 0) {
    list->lista[i].linhas.linha[list->lista[i].linhas.size] = linha;
    list->lista[i].linhas.size++;
    list->lista[i].Total++;
  } else if (list->livre < list->capacidade) {

    for (i = list->livre;
         i > 0 && strcasecmp(list->lista[i - 1].palavra, e) > 0; i--) {

      list->lista[i] = list->lista[i - 1];
    }

    strcpy(list->lista[i].palavra, e);
    list->lista[i].Total = 1;
    list->livre++;
    list->lista[i].linhas.size = 0;
    list->lista[i].linhas.linha[list->lista[i].linhas.size++] = linha;
    return TRUE;
  }

  return FALSE;
}
