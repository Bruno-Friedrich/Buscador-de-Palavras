#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "arvore_binaria.h"

No * busca_bin_rec(No * no,char * e){

	if(no){

		if(strcasecmp(no->palavra,e) == 0) return no;
		if(strcasecmp(e,no->palavra) < 0) return busca_bin_rec(no->esq, e);
		return busca_bin_rec(no->dir, e);
	}

	return NULL;
}

No * busca_bin(Arvore * arvore, char * e){
	
	return busca_bin_rec(arvore->raiz, e);	
}

Arvore * cria_arvore(){

	Arvore * arvore = (Arvore *) malloc (sizeof(Arvore));
	arvore->raiz = NULL;	
	return arvore;
}

Boolean insere_ord_rec(No * raiz, No * novo){

	if(strcasecmp(novo->palavra,raiz->palavra)){

		if(strcasecmp(novo->palavra,raiz->palavra) < 0){

			if(raiz->esq) return insere_ord_rec(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec(raiz->dir, novo);
			else raiz->dir = novo;
		}
		return TRUE;
	}
	return FALSE;
}

Boolean insere_ord(Arvore * arvore, char * e,int linha){

  No * nome = busca_bin(arvore,e);
  if(nome){
    nome->Total++;
    if(nome->linhas.linha[nome->linhas.size] != linha){
          nome->linhas.size++;
          nome->linhas.linha[nome->linhas.size] = linha;
    }

    return FALSE;
  }
  else{
    No * novo = (No *) malloc(sizeof(No));
    novo->linhas.size = 0;
  	strcpy(novo->palavra,e);
  	novo->esq = novo->dir = NULL;
    novo->linhas.linha[novo->linhas.size] = linha;
    novo->Total = 1;
  	if(arvore->raiz) return insere_ord_rec(arvore->raiz, novo);
  		
  	arvore->raiz = novo;
  	return TRUE;
  }
}

