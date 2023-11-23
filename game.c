#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// tamanho da caverna(aumentada)
#define MAX_LINHA 20
#define MAX_COLUNA 30

/*Este é um jogo de console simples, onde você controla um personagem (P)
em uma caverna representada por uma grade.
Seu objetivo é chegar até a saída (@) evitando um monstro (M)
que se move aleatoriamente pela caverna.*/

int main()
{

  // Inicialização das variáveis
  srand(time(NULL));

  // ox, oy: Posição da saída
  int ox = MAX_COLUNA / 2, oy = MAX_LINHA - 2;

  // px, py: Posição inicial do jogador.
  int px = 1, py = 1;

  // mx, my: Posição inicial do monstro.
  int mx = (int)(MAX_COLUNA * 0.7), my = (int)(MAX_LINHA * 0.7);

  // x, y: Variáveis de iteração para percorrer a grade.
  int x, y;

  // comando: Armazena o comando digitado pelo jogador.
  char comando;

  // movimentoRealizado: Controla se o movimento do jogador foi realizado com
  int movimentoRealizado;

  // dificuldade: Nível de dificuldade inicial do jogo.
  int dificuldade = 1;

  // Loop Principal:
  for (;;)
  {

    // O loop será interrompido quando o jogador atingir a saída ou colidir com o monstro.
    system("CLS");

    //imprime a caverna
    printf("Caverna X - dificuldade: %d\n\n", dificuldade);

    //imprime a caverna
    for (y = 0; y < MAX_LINHA; y++)
    {
      for (x = 0; x < MAX_COLUNA; x++)
      {
        if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
          printf("#");
        else if (x == px && y == py)
          printf("P");
        else if (x == mx && y == my)
          printf("M");
        else if (x == ox && y == oy)
          printf("@");
        else
          printf(".");
      }
      printf("\n");
    }
    printf("\n");

    // Entrada do Jogador:
    printf("Comando: C (cima)\tD (direita)\tB (baixo)\tE (esquerda)\n");
    printf("Sua vez!. Digite um comando: ");
    scanf(" %c", &comando);
    // Movimento do Jogador:
    movimentoRealizado = 1;
    switch (comando)
    {
    case 'c':
      py -= 1;
      if (py < 1)
      {
        py = 1;
        movimentoRealizado = 0;
      }
      break;

    case 'b':
      py += 1;
      if (py >= MAX_LINHA - 1)
      {
        py = MAX_LINHA - 2;
        movimentoRealizado = 0;
      }
      break;

    case 'e':
      px -= 1;
      if (px < 1)
      {
        px = 1;
        movimentoRealizado = 0;
      }
      break;

    case 'd':
      px += 1;
      if (px >= MAX_COLUNA - 1)
      {
        px = MAX_COLUNA - 2;
        movimentoRealizado = 0;
      }
      break;

    default:
      movimentoRealizado = 0;
      printf("Comando invalido!\n");
      printf("Pressione uma tecla para continuar!\n");
      system("PAUSE");
    }

    // Movimento Aleatório do Monstro:
    if (movimentoRealizado == 1)
    {
      int direcao = rand() % 4;
      switch (direcao)
      {
      case 0:
        my -= dificuldade;
        if (my < 1)
        {
          my = 1;
        }
        break;

      case 1:
        my += dificuldade;
        if (my >= MAX_LINHA - 1)
        {
          my = MAX_LINHA - 2;
        }
        break;

      case 2:
        mx -= dificuldade;
        if (mx < 1)
        {
          mx = 1;
        }
        break;

      case 3:
        mx += dificuldade;
        if (mx >= MAX_COLUNA - 1)
        {
          mx = MAX_COLUNA - 2;
        }
        break;
      }
    }

    // Verificação de Condições de Jogo:
    // Verifica se o jogador colidiu com o monstro (GAME OVER) ou se atingiu a saída (YOU WIN).
    // Se o jogador vencer, a dificuldade aumenta, e as posições são resetadas.
    if (px == mx && py == my)
    {
      printf("\n\nGAME OVER\n");
      break;
    }
    else if (px == ox && py == oy)
    {
      printf("\n\nYOU WIN\n");
      system("PAUSE");

      dificuldade++;

      px = 1;
      py = 1;
      mx = (int)(MAX_COLUNA * 0.7);
      my = (int)(MAX_LINHA * 0.7);
    }
  }
  // Finalização do Programa:
  system("PAUSE");
  return 0;
}
