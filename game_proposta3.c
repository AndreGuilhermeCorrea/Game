#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Inclusão da biblioteca para não precisar apertar ENTER.

// tamanho da caverna pré estabelecida
#define MAX_LINHA 20
#define MAX_COLUNA 30
#define NUM_MONSTROS 5

int main()
{
  srand(time(NULL));
  int ox = MAX_COLUNA / 2, oy = MAX_LINHA - 2;
  int px = 1, py = 1;
  int monstros[NUM_MONSTROS][2];
  // Inicializa as posições dos monstros aleatoriamente
  for (int i = 0; i < NUM_MONSTROS; i++)
  {
    monstros[i][0] = rand() % MAX_COLUNA;
    monstros[i][1] = rand() % MAX_LINHA;
  }

  int x, y;
  char comando;
  int movimentoRealizado;
  int dificuldade = 1;

  for (;;)
  {
    system("CLS");

    // imprime a caverna
    for (y = 0; y < MAX_LINHA; y++)
    {
      for (x = 0; x < MAX_COLUNA; x++)
      {
        if (y == 0 || x == 0 || x == MAX_COLUNA - 1 || y == MAX_LINHA - 1)
        {
          if (y == MAX_LINHA - 1 && x >= (MAX_COLUNA / 2 - 1) && x <= (MAX_COLUNA / 2))
          {
            printf("  "); // Dois espaços vazios no meio da parede
            x++;          // Avança mais uma posição para compensar o segundo espaço
          }
          else
          {
            printf("#");
          }
        }
        else if (x == px && y == py)
        {
          printf("P");
        }
        else
        {
          int ehMonstro = 0;
          for (int i = 0; i < NUM_MONSTROS; i++)
          {
            if (x == monstros[i][0] && y == monstros[i][1])
            {
              ehMonstro = 1;
              printf("M");
              break;
            }
          }
          if (!ehMonstro)
          {
            printf(".");
          }
        }
      }
      printf("\n");
    }

    printf("\nDificuldade: %d\n", dificuldade);

    // Recebe o comando do jogador
    printf("Comando: C (cima)\tD (direita)\tB (baixo)\tE (esquerda)\tX (encerrar)\n");
    printf("Sua vez! Digite um comando: ");
    comando = _getch(); // Substitui Scanf para reconhecer a tecla assim que digitada.

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
    // botão "x" para encerrar o game
    case 'x':
      printf("\n\nJogo encerrado pelo jogador.\n");
      return 0;

    default:
      movimentoRealizado = 0;
      printf("Comando inválido!\n");
      printf("Pressione uma tecla para continuar!\n");
      system("PAUSE");
    }

    if (movimentoRealizado == 1)
    {

      // Fator de escala para diminuir a velocidade dos monstros
      float fatorEscala = 0.5;

      // Movimenta os monstros aleatoriamente
      // Atualiza a posição dos monstros para perseguir o jogador
      for (int i = 0; i < NUM_MONSTROS; i++)
      {
        int deltaX = px - monstros[i][0];
        int deltaY = py - monstros[i][1];

        // Move o monstro na direção do jogador com velocidade reduzida
        monstros[i][0] += (int)(fatorEscala * deltaX);
        monstros[i][1] += (int)(fatorEscala * deltaY);

        // Verifica limites da caverna
        if (monstros[i][0] < 1)
        {
          monstros[i][0] = 1;
        }
        else if (monstros[i][0] >= MAX_COLUNA - 1)
        {
          monstros[i][0] = MAX_COLUNA - 2;
        }

        if (monstros[i][1] < 1)
        {
          monstros[i][1] = 1;
        }
        else if (monstros[i][1] >= MAX_LINHA - 1)
        {
          monstros[i][1] = MAX_LINHA - 2;
        }

        // Verifica se dois monstros estão na mesma posição e ajusta
        for (int j = 0; j < NUM_MONSTROS; j++)
        {
          if (i != j && monstros[i][0] == monstros[j][0] && monstros[i][1] == monstros[j][1])
          {
            // Se encontrou duas posições iguais, ajusta a posição do monstro i
            monstros[i][0] = rand() % MAX_COLUNA;
            monstros[i][1] = rand() % MAX_LINHA;
          }
        }
      }
    }

    // Verifica condições de vitória e derrota
    if ((px == ox && py == oy) || (px == ox + 1 && py == oy) || (px == ox - 1 && py == oy))
    {
      printf("\n\nYOU WIN\n");
      system("PAUSE");

      dificuldade++;

      px = 1;
      py = 1;

      for (int i = 0; i < NUM_MONSTROS; i++)
      {
        monstros[i][0] = rand() % MAX_COLUNA;
        monstros[i][1] = rand() % MAX_LINHA;
      }
    }
    else
    {
      for (int i = 0; i < NUM_MONSTROS; i++)
      {
        if (px == monstros[i][0] && py == monstros[i][1])
        {
          printf("\n\nGAME OVER\n");
          return 0;
        }
      }
    }
  }

  system("PAUSE");
  return 0;
}
