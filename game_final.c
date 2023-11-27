/*Este é um jogo de console simples, onde você controla um personagem (P)
em uma caverna representada por uma grade.
Seu objetivo é chegar até a saída (  ) evitando os monstros (M)
que se move aleatoriamente pela caverna.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inclusão da biblioteca para não precisar apertar ENTER.
#include <conio.h>

// tamanho da caverna pré estabelecida
#define MAX_LINHA 20
#define MAX_COLUNA 30

// define a quantidade de monstros no jogo
#define NUM_MONSTROS 5

int main()
{

  // Inicialização das variáveis

  // Gerador de números aleatórios diferentes em momentos diferentes
  srand(time(NULL));

  // Posição da saída do jogador
  int ox = MAX_COLUNA / 2;

  int oy = MAX_LINHA - 2;

  // Posição inicial do jogador.
  int px = 1;

  int py = 1;

  // Posições dos monstros
  int monstros[NUM_MONSTROS][2];

  // Inicializa as posições dos monstros aleatoriamente
  for (int i = 0; i < NUM_MONSTROS; i++)
  {
    monstros[i][0] = rand() % MAX_COLUNA;
    monstros[i][1] = rand() % MAX_LINHA;
  }

  // Variáveis de iteração para percorrer a grade
  int x, y;

  // Variável que armazena o comando digitado pelo jogador.
  char comando;

  // Variável que controla se o movimento do jogador foi realizado.
  int movimentoRealizado;

  // Variável que estabelece o nível de dificuldade inicial do jogo.
  int dificuldade = 1;

  // Loop Principal:
  for (;;)
  {

    // O loop será interrompido quando o jogador atingir a saída ou colidir com o monstro.
    system("CLS");

    // Imprime a caverna
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
            printf("X");
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
            printf(" ");
          }
        }
      }
      printf("\n");
    }

    printf("\nDificuldade: %d\n", dificuldade);

    // Recebe o comando do jogador
    printf("Comando: W (cima)\tD (direita)\tS (baixo)\tA (esquerda)\tX (encerrar)\n");
    printf("Sua vez! Digite um comando: ");
    // Substitui Scanf para reconhecer a tecla assim que digitada.
    comando = _getch();
    // Substitui todos os caracteres para minúsculo.
    comando = tolower(comando);
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

    // botão "x" para encerrar o game.
    case 'x':
      printf("\n\nJogo encerrado pelo jogador.\n");
      return 0;

    default:
      movimentoRealizado = 0;
      printf("Comando inválido!\n");
      printf("Pressione uma tecla para continuar!\n");
      system("PAUSE");
    }
    // Movimento Aleatório do Monstro.
    if (movimentoRealizado == 1)
    {

      // Fator de escala para diminuir a velocidade dos monstros.
      float fatorEscala = 0.5;

      // Movimenta os monstros aleatoriamente.
      // Atualiza a posição dos monstros para perseguir o jogador.
      for (int i = 0; i < NUM_MONSTROS; i++)
      {
        int deltaX = px - monstros[i][0];
        int deltaY = py - monstros[i][1];

        // Move o monstro na direção do jogador com velocidade reduzida.
        monstros[i][0] += (int)(fatorEscala * deltaX);
        monstros[i][1] += (int)(fatorEscala * deltaY);

        // Verifica limites da caverna.
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

        // Verifica se dois monstros estão na mesma posição e ajusta.
        for (int j = 0; j < NUM_MONSTROS; j++)
        {
          if (i != j && monstros[i][0] == monstros[j][0] && monstros[i][1] == monstros[j][1])
          {
            // Se encontrou duas posições iguais, ajusta a posição do monstro.
            monstros[i][0] = rand() % MAX_COLUNA;
            monstros[i][1] = rand() % MAX_LINHA;
          }
        }
      }
    }

    // Verifica condições de vitória e derrota.

    // Verifica se o jogador atingiu a saída (YOU WIN).
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
        // Verifica se o jogador colidiu com o monstro (GAME OVER).
        if (px == monstros[i][0] && py == monstros[i][1])
        {
          printf("\n\nGAME OVER\n");
          return 0;
        }
      }
    }
  }
  // Finalização do Programa.
  system("PAUSE");
  return 0;
}
