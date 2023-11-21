#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#endif

#define MAX_LINHA 10
#define MAX_COLUNA 10

#ifdef _WIN32
void setColor(int color)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
#define setColor(color) printf(color)
#endif

int main()
{
  srand(time(NULL));
  int ox = MAX_COLUNA / 2, oy = MAX_LINHA - 2;
  int px = 1, py = 1;
  int mx = (int)(MAX_COLUNA * 0.7), my = (int)(MAX_LINHA * 0.7);
  int x, y;
  char comando;
  int movimentoRealizado;
  int dificuldade = 1;

  int obstaculos[MAX_LINHA][MAX_COLUNA] = {0};

  for (;;)
  {
    system("CLS");

    for (y = 0; y < MAX_LINHA; y++)
    {
      for (x = 0; x < MAX_COLUNA; x++)
      {
        if (obstaculos[y][x] == 1)
        {
          setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
          printf("O");
          setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
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
    printf("\nDificuldade: %d\n", dificuldade);

    printf("Comando: C (cima)\tD (direita)\tB (baixo)\tE (esquerda)\n");
    printf("Sua vez! Digite um comando: ");
    scanf(" %c", &comando);

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
      printf("Comando inválido!\n");
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

  system("PAUSE");
  return 0;
}