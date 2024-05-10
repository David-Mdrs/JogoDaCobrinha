// Verifica se o cabeçalho já foi incluído para evitar múltiplas inclusões
#ifndef LISTA_H
#define LISTA_H

// Incluindo a definição da estrutura NO
typedef struct {
    int x, y;
} NO;

// Definindo struct LISTA
typedef struct {
    NO *arr;
    int pos, MAX;
} LISTA;

// Protótipos das funções
void Criar(LISTA *lst);
void Apagar(LISTA *lst);
void Redimensionar(LISTA *lst, int MAX);
void Inserir(LISTA *lst, int x, int y);
void Imprimir(LISTA *lst);

// Fim da verificação de múltiplas inclusões
#endif