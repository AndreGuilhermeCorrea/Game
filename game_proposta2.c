#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Inclusão da biblioteca para não precisar apertar ENTER para reconhecer a função e também reconhecer as teclas direcionais.

#define MAX_LINHA 15
#define MAX_COLUNA 25

int main()
{
  srand(time(NULL));
  int px = 1, py = 1;
  int x, y;
  char comando;
  int movimentoRealizado;
  int dificuldade = 1;
  int mx, my, ox, oy;

  // Inicialização das posições iniciais de M e @ para ser randomizadas e não coincidir de cair na mesma localização dentro da matriz.
  mx = rand() % (MAX_COLUNA - 2) + 1;
  my = rand() % (MAX_LINHA - 2) + 1;

  do
  {
    ox = rand() % (MAX_COLUNA - 2) + 1;
    oy = rand() % (MAX_LINHA - 2) + 1;
  } while ((ox == px && oy == py) || (ox == mx && oy == my));

  for (;;)
  {
    system("CLS");

    printf("Caverna X - dificuldade: %d\n\n", dificuldade);
    for (y = 0; y < MAX_LINHA; y++)
    {
      for (x = 0; x < MAX_COLUNA; x++)
      {

        if (y == 0 || y == MAX_LINHA - 1)
          printf("-");
        else if (x == 0 || x == MAX_COLUNA - 1)
          printf("X");
        else if (x == px && y == py)
          printf("P");
        else if (x == mx && y == my)
          printf("M");
        else if (x == ox && y == oy)
          printf("@");
        else
          printf(" ");
      }
      printf("\n");
    }
    printf("\n");

    printf("Comando: W (cima)\tD (direita)\tS (baixo)\tA (esquerda)\n");
    printf("Sua vez!. Digite um comando: ");
    comando = _getch();         // Substitui Scanf para reconhecer a tecla assim que digitada.
    comando = tolower(comando); // Substitui todos os caracteres para minúsculo.

    movimentoRealizado = 1;
    switch (comando)
    {
    case 'w':
      py -= 1;
      if (py < 1)
      {
        py = 1;
        movimentoRealizado = 0;
      }
      break;

    case 's':
      py += 1;
      if (py >= MAX_LINHA - 1)
      {
        py = MAX_LINHA - 2;
        movimentoRealizado = 0;
      }
      break;

    case 'a':
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

    if (px == mx && py == my)
    {
      printf("\n\nGAME OVER\n");
      system("PAUSE");

      dificuldade++;

      px = 1;
      py = 1;
      mx = rand() % (MAX_COLUNA - 2) + 1; // Randomiza a localização do Monstro a cada jogo.
      my = rand() % (MAX_LINHA - 2) + 1;
      do
      {
        ox = rand() % (MAX_COLUNA - 2) + 1;
        oy = rand() % (MAX_LINHA - 2) + 1;
      } while ((ox == px && oy == py) || (ox == mx && oy == my));
    }
    else if (px == ox && py == oy)
    {
      printf("\n\nYOU WIN\n");
      system("PAUSE");

      dificuldade++;

      px = 1;
      py = 1;
      mx = rand() % (MAX_COLUNA - 2) + 1; // Randomiza a localização do Monstro a cada jogo.
      my = rand() % (MAX_LINHA - 2) + 1;
      do
      {
        ox = rand() % (MAX_COLUNA - 2) + 1;
        oy = rand() % (MAX_LINHA - 2) + 1;
      } while ((ox == px && oy == py) || (ox == mx && oy == my));
    }
  }

  system("PAUSE");
  return 0;
}
