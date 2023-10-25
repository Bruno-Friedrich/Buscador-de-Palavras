#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef int Elemento;
typedef int Boolean;

typedef struct {
  int linha[100000];
  int size;
} linhasecontador;

typedef struct _no_arvore_ {
	linhasecontador linhas;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;
  char palavra[50];
  int Total;
} No;

typedef struct {

	No * raiz;

} Arvore;

Arvore * cria_arvore();
No * busca_bin(Arvore * arvore, char * e);
Boolean insere_ord(Arvore * arvore, char * e,int linha);



