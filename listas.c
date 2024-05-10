#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

// Retorna os valores da lista
void Imprimir(LISTA *lst) {
  printf("[");
  for (int i = 0; i < lst->pos; i++) {
    if (i < lst->pos-1)
      printf("[%d, %d], ", lst->arr[i].x, lst->arr[i].y);
    else
      printf("[%d, %d]", lst->arr[i].x, lst->arr[i].y);
  }
  printf("]\n");
}

// Cria um novo registro do tipo "LISTA"
void Criar(LISTA *lst) {
  lst->pos = 0;
  lst->MAX = 1;
  lst->arr = (NO *)(malloc(1 * sizeof(NO)));
  if (lst->arr == NULL)
    printf("Falha na alocação de memória.");
}

// Apaga registro
void Apagar(LISTA *lst) { free(lst->arr); }

// Redimensionar a memória alocada dinamicamente, para mais ou para menos
void Redimensionar(LISTA *lst, int MAX){
  if (lst->pos > MAX){
    printf("Impossível desalocar memória. Elementos presentes na lista.\n");
  } else {
    NO *pAux = (NO *)(realloc(lst->arr, MAX * sizeof(NO))); 
    if (pAux == NULL){
      printf("Falha na realocação de memória\n");
      free(pAux);
      return;
    } else {
      lst->arr = pAux;
      lst->MAX = MAX;
    }
  }
}

// Insere elementos a partir da posição dada
void Inserir(LISTA *lst, int x, int y){
  if (lst->pos < 0){
    printf("Posição inválida!\n");       // Posição menor que a cabeça da cobrinha
    return;
  } else {
    Redimensionar(lst, lst->MAX+1);
    lst->arr[lst->pos].x = x;
    lst->arr[lst->pos].y = y;
    lst->pos++;
   }
  }