
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int NUM_OF_PLAYERS;
int WIDTH;
int HEIGHT;

int GetField(int x, int y);
int GetScore(int id);


void ShowData()
{
  int i, j, faza;
  int a = HEIGHT;
  if (HEIGHT % 2 != 0)
    {
      a = HEIGHT + 1;
    }
  else
    {
      a = HEIGHT;
    }
  faza = 0;
  //printing
  for (j = 0; j < a / 2; ++j)
    {
        //phase 0 prints /\/\/\
        
      if (faza == 0)
	{
	  for (i = 0; i < WIDTH; i++)
	    {
	      printf ("/   \\   ");
	      faza = 1;
	    }
	  if (j != 0)
	    printf ("/");
	  printf ("\n");
	}

      if (faza == 1)
	{
	  for (i = 0; i < WIDTH; i++)
	    {
	        if(GetField(i, j)>=0){
	            printf("| ");
	        }else
	        {
	            printf("|");
	        }
	      printf ("%d |   ", GetField(i, j));
	    }
	  printf ("\n");
	  faza = 2;
	}

      if (faza == 2& j != HEIGHT / 2)
	{
	  for (i = 0; i < WIDTH; i++)
	    {
	      printf ("\\   /   ");
	    }
	  printf ("\\ \n");
	faza=3;
	}
      if (faza == 3 & j != HEIGHT / 2)
	{
	  printf ("    ");
	  for (i = 0; i < WIDTH; i++)
	    {
	         if(GetField(i, j)>=0){
	            printf("| ");
	        }else
	        {
	            printf("|");
	        }
	      printf ("%d |   ", GetField(i, j));
	    }
	  printf ("\n");
	  faza = 0;
	}
      if (j == a / 2 - 1)
	{
	  if (HEIGHT % 2 == 0)
	    {
	      printf ("    ");
	    }
	  for (i = 0; i < WIDTH; i++)
	    {
	      printf ("\\   /   ");
	    }
	}
	printf("\n");
    }
    printf("Scores: \n\n");
	for (i = 1; i <= NUM_OF_PLAYERS; i++) 
	{
		printf("Player %d: %d ", i, GetScore(i));
		printf("\n");
	}

}

