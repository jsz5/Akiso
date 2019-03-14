#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <pthread.h>
int **matrix1, **transposition, **multiplied;
pthread_t *threads_table;
int height2, width2,height1;
int k=0;

int multiply_rows(int * row1, int *row2, int size)
{
    for(int i=0; i<size; i++)
    {
      if(row1[i]==1 && row2[i]==1)
        return 1;
    }
    return 0;
}
void multiply(int k)
{
      for(int j=0; j<width2; j++) {
          multiplied[k][j] = multiply_rows(matrix1[k], transposition[j], height2);
      }
}
void *rows(void *id)
{
  int *myid = (int *)id;
  while(k<height1)
  {
      k++;
      printf("Numer wątku %d, numer wiersza %d\n",*myid, k);
      multiply(k-1);
  }
  return NULL;
}
int main()
{
  printf("Podaj szerokość macierzy pierwszej: ");
  int width1, threads;
  scanf("%d", &width1);
  printf("Podaj długość macierzy pierwszej: ");
  scanf("%d", &height1);
  printf("Podaj szerokość macierzy drugiej: ");
  scanf("%d", &width2);
  printf("Podaj długość macierzy drugiej: ");
  scanf("%d", &height2);
  printf("Podaj ilość wątków: ");
   scanf("%d", &threads);
  if(width1==height2)
  {
    int ** matrix2;
    matrix1=malloc(height1*sizeof(int*)); // size sztuk elementów każdy z których jest tablicą bool czyli bool *
    matrix2=malloc(height2*sizeof(int*));
    for(int i=0;i<height1;i++)
      matrix1[i]=malloc(width1*sizeof(int));
    for(int i=0;i<height2;i++)
      matrix2[i]=malloc(width2*sizeof(int));
    int r;
    srand( time( NULL ) );
    for(int i=0; i<height1; i++)
    {
        for(int j=0; j<width1; j++)
        {
          r=rand()%2;
          matrix1[i][j]=r;
        }
    }
    for(int i=0; i<height2; i++)
    {
      for(int j=0; j<width2; j++)
      {
        r=rand()%2;
        matrix2[i][j]=r;
      }
    }
    multiplied=malloc(height1*sizeof(int*));
    for(int i=0; i<height1; i++)
      multiplied[i]=malloc(width2*sizeof(int));
    transposition=malloc(width2*sizeof(int*));
    for(int i=0; i<width2; i++)
      transposition[i]=malloc(height2*sizeof(int));
    for(int i=0; i<width2; i++)
    {
      for(int j=0; j<height2; j++)
      {
        transposition[i][j]=matrix2[j][i];
      }
    }
    threads_table = (pthread_t *)malloc(threads * sizeof(pthread_t));
    for (int i=0; i < threads; i++){
     pthread_t t;
     threads_table[i]=t;
  }
      pthread_t thread0;
      for (int i = 0; i < threads; i++){
             pthread_create(&threads_table[i], NULL, rows, (void *)&threads_table[i]);

      }
      // for(int i=0; i<threads; i++)
      // {
      //   pthread_join(threads_table[i], NULL);
      // }

    printf("pierwsza czy pisze\n" );
    for(int i=0; i<height1; i++)
    {
      for(int j=0; j<width1; j++)
      {
        printf("%d ",matrix1[i][j]);

      }
      printf("\n" );
    }
    printf("\n" );
    for(int i=0; i<height2; i++)
    {
      for(int j=0; j<width2; j++)
      {
        printf("%d ",matrix2[i][j]);

      }
      printf("\n" );
    }
    printf("transpozycja\n" );
    for(int i=0; i<width2; i++)
    {
      for(int j=0; j<height2; j++)
      {
        printf("%d ",transposition[i][j]);

      }
      printf("\n" );
    }
    printf("pomonozone\n" );
    for(int i=0; i<height1; i++)
    {
      for(int j=0; j<width2; j++)
      {
        printf("%d ",multiplied[i][j]);

      }
      printf("\n" );
    }
    printf("\n" );
    pthread_exit(0);

  }
  else
  {
            printf("Nie można pomnożyć\n");
  }

    return 0;
}
