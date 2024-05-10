#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "listas.h"

char tabuleiro[10][50];
int maca[2];
char direcao = 'A', direcaoAux;
int pontos = 0;
char opcao = 'W', tecla = 'X';
int jogoAtivo;

//  PRINCIPAIS OPERAÇÕES DO JOGO
void CriarTabuleiro(char tabuleiro[10][50]){                              // Criar tabuleiro
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 50; j++){
      if (i == 0 || i == 9){
        tabuleiro[i][j] = '#';      // Paredes superiores e inferiores
      } else {
        if (j == 0 || j == 49){
          tabuleiro[i][j] = '#';    // Paredes laterais
        } else{
          tabuleiro[i][j] = ' ';    // Espaços vazios
        }
      }
    }
  }
}
void InserindoCobrinha(LISTA *Cobrinha, char tabuleiro[10][50]){          // Inserir cobrinha no tabuleiro
  for (int i = 0; i < Cobrinha->pos; i++){
    if (i == 0){
      tabuleiro[Cobrinha->arr[i].x][Cobrinha->arr[i].y] = 'O';
    } else {
      tabuleiro[Cobrinha->arr[i].x][Cobrinha->arr[i].y] = 'o';
    }
  }
}
void PosicaoMaca(LISTA *Cobrinha, int *maca) {                            // Gerar posição aleatória para maça
  int contador = 0;
    srand(time(NULL)); // Inicializando nova sequência de números aleatórios
  while (1){
    maca[0] = 1 + rand() % 8;
    maca[1] = 1 + rand() % 48;
    contador = 0;
    while (contador < Cobrinha->pos){
      if (maca[0] == Cobrinha->arr[contador].x && maca[1] == Cobrinha->arr[contador].y) {
          break; // Posição ocupada pela cobrinha, tentar outra posição
      }
      contador++;
    }
    if (contador == Cobrinha->pos){  // Posição encontrada sem colidir com a cobrinha

      break;
    }
  }
}
void InserirMaca(char tabuleiro[10][50], int *maca){                      // Inserir maça no tabuleiro
  tabuleiro[maca[0]][maca[1]] = '@';    // Inserindo maçã no tabuleiro
}
void NovoJogo(LISTA *Cobrinha, char tabuleiro[10][50], int *maca, char *direcao, int *pontos){        // Preparar de ambiente para novo jogo
  Criar(Cobrinha);            // Criando lista 'Cobrinha'
  Inserir(Cobrinha, 5, 35);    // Adicionando cobrinha no centro do tabuleiro
  Inserir(Cobrinha, 5, 36);    // Adicionando cobrinha no centro do tabuleiro
  Inserir(Cobrinha, 5, 37);   // Adicionando cobrinha no centro do tabuleiro
  Inserir(Cobrinha, 5, 38);   // Adicionando cobrinha no centro do tabuleiro
  Inserir(Cobrinha, 5, 39);   // Adicionando cobrinha no centro do tabuleiro
  CriarTabuleiro(tabuleiro);                  // Criando tabuleiro
  InserindoCobrinha(Cobrinha, tabuleiro);    // Inserindo posição inicial da cobrinha
  PosicaoMaca(Cobrinha, maca);  // Inserindo posição inicial da maçã
  InserirMaca(tabuleiro, maca);
  *direcao = 'A';
  *pontos = 0;
}
int Movimentar(LISTA *Cobrinha,  char tabuleiro[10][50], int *maca, char *direcao, int *pontos){    // Movimentar e Verificar de itens
  char casa = ' ';
  if (*direcao == 'W'){                                              // Movimentando para cima
    if (Cobrinha->arr[1].x == Cobrinha->arr[0].x-1)                 // Voltando para trás (inválido)
      return 1;
    casa = tabuleiro[Cobrinha->arr[0].x - 1][Cobrinha->arr[0].y];   // Próxima casa

  } else if (*direcao == 'A'){                                       // Movimentando para esquerda
    if (Cobrinha->arr[1].y == Cobrinha->arr[0].y-1)                 // Voltando para trás (inválido)
      return 1;
    casa = tabuleiro[Cobrinha->arr[0].x][Cobrinha->arr[0].y - 1];   // Próxima casa

  } else if (*direcao == 'S'){                                       // Movimentando para baixo
    if (Cobrinha->arr[1].x == Cobrinha->arr[0].x+1)                 // Voltando para trás (inválido)
      return 1;
    casa = tabuleiro[Cobrinha->arr[0].x + 1][Cobrinha->arr[0].y];   // Próxima casa

  } else if (*direcao == 'D'){                                       // Movimentando para direita
    if (Cobrinha->arr[1].y == Cobrinha->arr[0].y+1)                 // Voltando para trás (inválido)
      return 1;
    casa = tabuleiro[Cobrinha->arr[0].x][Cobrinha->arr[0].y + 1];   // Próxima casa
  }

  if (casa == '#' || casa == 'o'){   // Bateu na parede ou nela mesma
    Apagar(Cobrinha);
    NovoJogo(Cobrinha, tabuleiro, maca, direcao, pontos);
    return 0;
  } else if (casa == '@'){    // Comeu uma maçã
    *pontos += 10; // Adicionando pontuação
    PosicaoMaca(Cobrinha, maca);
    Inserir(Cobrinha, Cobrinha->arr[Cobrinha->pos-1].x, Cobrinha->arr[Cobrinha->pos-1].y);
    for (int i = Cobrinha->pos-1; i > 0; i--){   // Passando elementos e deixando último
      Cobrinha->arr[i].x = Cobrinha->arr[i-1].x;
      Cobrinha->arr[i].y = Cobrinha->arr[i-1].y;
    }
  } else {
    for (int i = Cobrinha->pos; i > 0; i--){    // Passando todos os elementos
      Cobrinha->arr[i].x = Cobrinha->arr[i-1].x;
      Cobrinha->arr[i].y = Cobrinha->arr[i-1].y;
    }
  }
  if (*direcao == 'W'){         // Movendo cabeça
    Cobrinha->arr[0].x--;
  } else if (*direcao == 'A'){  // Movendo cabeça
    Cobrinha->arr[0].y--;
  } else if (*direcao == 'S'){  // Movendo cabeça
    Cobrinha->arr[0].x++;
  } else if (*direcao == 'D'){  // Movendo cabeça
    Cobrinha->arr[0].y++;
  } 
  return 1;
}

//  FORMATAÇÃO DA TELA DO JOGO
void TituloCobrinha(){              // Título 'COBRINHA' no canto superior do jogo
  // Limpar terminal
  system("cls");
  printf("###################################################################################################\n");
  printf("|               _______  _______  _______  ______    ___  __    _  __   __  _______               |\n");
  printf("|              |       ||       ||  _    ||    _ |  |   ||  |  | ||  | |  ||   _   |              |\n");
  printf("|              |    _  ||   _   || |_|   ||   | ||  |   ||   |_| ||  |_|  ||  |_|  |              |\n");
  printf("|              |   | |_||  | |  ||       ||   |_||_ |   ||       ||       ||       |              |\n");
  printf("|              |   |    |  |_|  ||  _   | |    __  ||   ||  _    ||       ||       |              |\n");
  printf("|              |   |___ |       || |_|   ||   |  | ||   || | |   ||   _   ||   _   |              |\n");
  printf("|              |_______||_______||_______||___|  |_||___||_|  |__||__| |__||__| |__|              |\n");
  printf("|                                                                                                 |\n");
  printf("|                                                                                                 |\n");
}
void TituloJogar(char opcao){       // Botão 'Jogar' no inicio do jogo
  if (opcao == 'W'){
    printf("|                    __        ______  ______  ______  ______  ____         __                    |\n");
    printf("|           ________\\  \\      |_    _||   _  ||   ___||   _  ||  _ |       /  /________           |\n");
    printf("|          |            \\       |  |  |  | | ||  |  _ |  |_| || |_||_     /            |          |\n");
    printf("|          |________    /     __|  |  |  |_| ||  |_| ||   _  ||  __  |    \\    ________|          |\n");
    printf("|                   /__/     |_____|  |______||______||__| |_||_|  |_|     \\__\\                   |\n");
  } else {
    printf("|                              ______  ______  ______  ______  ____                               |\n");
    printf("|                             |_    _||   _  ||   ___||   _  ||  _ |                              |\n");
    printf("|                               |  |  |  | | ||  |  _ |  |_| || |_||_                             |\n");
    printf("|                             __|  |  |  |_| ||  |_| ||   _  ||  __  |                            |\n");
    printf("|                            |_____|  |______||______||__| |_||_|  |_|                            |\n");
  }
}
void TituloCredito(char opcao){     // Botão 'Crédito' no inicio do jogo
  if (opcao == 'S'){
    printf("|                                           _                                                     |\n");
    printf("|                                          //                                                     |\n");
    printf("|                 __       _____  ____    ____  _____   __  ______  ____       __                 |\n");
    printf("|        ________\\  \\     |  _  ||  _ |  | __ ||  _  | |  ||_    _||  _ |     /  /________        |\n");
    printf("|       |            \\    | | |_|| |_||_ |   _|| | |  ||  |  |  |  | | ||    /            |       |\n");
    printf("|       |________    /    | |___ |  __  ||  |_ | |_|  ||  |  |  |  | |_||    \\    ________|       |\n");
    printf("|                /__/     |_____||_|  |_||____||_____| |__|  |__|  |____|     \\__\\                |\n");
  } else {
    printf("|                                           _                                                     |\n");
    printf("|                                          //                                                     |\n");
    printf("|                          _____  ____    ____  _____   __  ______  ____                          |\n");
    printf("|                         |  _  ||  _ |  | __ ||  _  | |  ||_    _||  _ |                         |\n");
    printf("|                         | | |_|| |_||_ |   _|| | |  ||  |  |  |  | | ||                         |\n");
    printf("|                         | |___ |  __  ||  |_ | |_|  ||  |  |  |  | |_||                         |\n");
    printf("|                         |_____||_|  |_||____||_____| |__|  |__|  |____|                         |\n");
  }
}
void FimTela(){                     // Final da tela do jogo
  printf("|                                                                                                 |\n");
  printf("|                                                                                                 |\n");
  printf("###################################################################################################\n");
}
void Tabuleiro(char tabuleiro[10][50]){                   // Tabuleiro com cobrinha e maçã
  for (int i = 0; i < 10; i++){
    printf("|                       ");
    for (int j = 0; j < 50; j++){
      printf("%c", tabuleiro[i][j]);
    }
    printf("                        |\n");
  }
}                    // Tabuleiro com cobrinha
void TelaInicial(char opcao){       // Tela inicial com título e botões
  TituloCobrinha();
  TituloJogar(opcao);
  TituloCredito(opcao);
  FimTela();
}        // Tela inicial com título e botões
void TelaJogo(char tabuleiro[10][50], int pontos){          // Tela do jogo com título, pontuação e cobrinha
  TituloCobrinha();
  if (pontos < 10)
    printf("|                                           PONTUACAO: %d                                          |\n", pontos);
  else if (pontos >= 10 && pontos < 100)
    printf("|                                           PONTUACAO: %d                                         |\n", pontos);
  else if (pontos >= 100 && pontos < 1000)
    printf("|                                           PONTUACAO: %d                                        |\n", pontos);
  else
    printf("|                                           PONTUACAO: %d                                       |\n", pontos);
  printf("|                                                                                                 |\n");
  Tabuleiro(tabuleiro);
  FimTela();
}          // Tela do jogo com título, pontuação e cobrinha
void TelaGameOver(char *tecla){                // Tela de game over
    TituloCobrinha();
    printf("|                                                                                                 |\n");
    printf("|            _______  _______  __   __  _______     _______  __   __  _______  ______             |\n");
    printf("|           |       ||   _   ||  |_|  ||       |   |       ||  | |  ||       ||    _ |            |\n");
    printf("|           |    ___||  |_|  ||       ||    ___|   |   _   ||  |_|  ||    ___||   | ||            |\n");
    printf("|           |   | __ |       ||       ||   |___    |  | |  ||       ||   |___ |   |_||_           |\n");
    printf("|           |   ||  ||       ||       ||    ___|   |  |_|  ||       ||    ___||    __  |          |\n");
    printf("|           |   |_| ||   _   || ||_|| ||   |___    |       | |     | |   |___ |   |  | |          |\n");
    printf("|           |_______||__| |__||_|   |_||_______|   |_______|  |___|  |_______||___|  |_|          |\n");
    printf("|                                                                                                 |\n");
    printf("|                                                                                                 |\n");
    printf("|                                                                                                 |\n");
    printf("|                     PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU PRINCIPAL                      |\n");
    FimTela();
    
    while (!kbhit()) { /*aguardando*/ }               // Aguarda pressionamento de uma tecla
    fflush(stdin);                                    // Limpa o buffer de entrada do teclado
    getch();                                          // Descarta a tecla pressionada
    *tecla = 'W';                                      // Define a tecla como 'S' para voltar ao menu principal
}
void TelaCredito(char *tecla){                 // Tela de crédito sobre a criação do jogo
  TituloCobrinha();
  printf("|                 ##############################################################                  |\n");
  printf("|                ##                                                            ##                 |\n");
  printf("|               ###           Jogo da cobrinha desenvolvido durante            ###                |\n");
  printf("|              ####         a graduacao em engenharia da computacao no         ####               |\n");
  printf("|             #####    Instituto Federal da Paraiba - Campus Campina Grande    #####              |\n");
  printf("|            ######           como projeto final para a disciplina             ######             |\n");
  printf("|            ######                  de Estrutura de Dados.                    ######             |\n");
  printf("|             #####                                                            #####              |\n");
  printf("|              ####             Criador: David Medeiros Santos                 ####               |\n");
  printf("|               ###   PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU PRINCIPAL   ###                |\n");
  printf("|                ##                                                            ##                 |\n");
  printf("|                 ##############################################################                  |\n");
  FimTela();

    while (!kbhit()) {            // Aguarda pressionamento de uma tecla
      // Espera
    }
    fflush(stdin);                // Limpa o buffer de entrada do teclado
    getch();                      // Descarta a tecla pressionada
    *tecla = 'S';                  // Define a tecla como 'S' para voltar ao menu principal
}                 // Tela de crédito onde explica a criação do jogo

int main(){
  LISTA Cobrinha;                                     // Iniciando novo registro do tipo LISTA
  NovoJogo(&Cobrinha, tabuleiro, maca, &direcao, &pontos);               // Criando ambiente para

  while(1){                                           // Looping game
    // TELA INICIAL
    TelaInicial(opcao);                               // Tela de inicial
    while (!kbhit()) {/*aguardando*/}                 // Aguardando acionamento de uma tecla
    fflush(stdin);                                    // Limpa o buffer de entrada do teclado
    tecla = getch();                                  // Descarta a tecla pressionada
    tecla = toupper(tecla);                           // Convertendo para maiúsculo
    if (tecla == 27){return 0;}                       // Fechando jogo 'ESC'
    if (tecla == 'W' || tecla == 'S'){                // Mudando de opcao no menu principal
      opcao = tecla;                                  // Define a tecla como 'S' para voltar ao menu principal
    }

    // TELA JOGO
    if (opcao == 'W' && tecla == 13){                 // Usuário selecionou 'ENTER' em 'Jogar'
      jogoAtivo = 1;
      while(1) {
        TelaJogo(tabuleiro, pontos);                             // Atualizando tela de jogo

        while (!kbhit()) {                            // Enquanto nenhuma tecla for pressionada
          if (Movimentar(&Cobrinha, tabuleiro, maca, &direcao, &pontos) == 0){ // Movendo cobrinha
            TelaGameOver(&tecla);                           // Game over
            jogoAtivo = 0;                            // Zerando estado da variável de controle
            break;
          }
          CriarTabuleiro(tabuleiro);                  // Atualizando tabuleiro
          InserirMaca(tabuleiro, maca);                     // Atualizando tabuleiro
          InserindoCobrinha(&Cobrinha, tabuleiro);    // Atualizando tabuleiro
          Sleep(200);                                 // Velocidade da cobrinha
          TelaJogo(tabuleiro, pontos);                           // Atualizando tela de jogo
        }
        if (jogoAtivo){
          fflush(stdin);                              // Limpando buffer de entrada do teclado
          direcaoAux = getch();                       // Lendo próxima direção da cobrinha
          direcaoAux = toupper(direcaoAux);           // Convertendo para maiúsculo
          if (direcaoAux == 27){ return 0; }          // Fechando jogo 'ESC'
          if (direcaoAux == 'W' || direcaoAux == 'A' || direcaoAux == 'S' || direcaoAux == 'D'){
            direcao = direcaoAux;                     // Usuário inseiu direção válida
          }
        } else { break; }                             // Saindo da tela de jogo
      }

    // TELA CRÉDITO
    } else if (opcao == 'S' && tecla == 13) {         // Usuário selecionou 'ENTER' em 'Crédito'
      TelaCredito(&tecla);                                  // Tela de crédito
    }
  }
}