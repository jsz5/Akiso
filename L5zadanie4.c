#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
int **matrix1, **transposition, **multiplied, **multiplied2;
int height2, width2,height1;

int multiply_rows(int * row1, int *row2, int size)
{
    int suma=0;
    for(int i=0; i<size; i++)
    {
      suma+=row1[i]*row2[i];
    }
    return suma;
}

int main()
{
  printf("Podaj szerokość macierzy pierwszej: ");
  int width1;
  scanf("%d", &width1);
  printf("Podaj długość macierzy pierwszej: ");
  scanf("%d", &height1);
  printf("Podaj szerokość macierzy drugiej: ");
  scanf("%d", &width2);
  printf("Podaj długość macierzy drugiej: ");
  scanf("%d", &height2);

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
          r=rand()%9;
          matrix1[i][j]=r;
        }
    }
    for(int i=0; i<height2; i++)
    {
      for(int j=0; j<width2; j++)
      {
        r=rand()%9;
        matrix2[i][j]=r;
      }
    }

    struct timeval tvalBefore, tvalAfter, tvalBeforeTrans, tvalAfterTrans;
   gettimeofday (&tvalBefore, NULL);
    /**
    *BEZ TRANSPOZYCJI
    */
    multiplied2=malloc(height1*sizeof(int*));
    for(int i=0; i<height1; i++)
      multiplied2[i]=malloc(width2*sizeof(int));
    for(int i=0; i<height1; i++)
    {
      for(int j=0; j<width2; j++)
      {
        int w=0;
        for(int row=0; row<height2; row++)
        {
          w+=matrix1[i][row]*matrix2[row][j];
        }
        multiplied2[i][j]=w;
      }
    }
    gettimeofday (&tvalAfter, NULL);
    gettimeofday (&tvalBeforeTrans, NULL);

    /**
    *TRANSPOZYCJA
    */
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
    for(int k=0; k<height1; k++)
    {
      for(int j=0; j<width2; j++)
      {
          multiplied[k][j] = multiply_rows(matrix1[k], transposition[j], height2);
      }
    }
    gettimeofday(&tvalAfterTrans, NULL);
    long long time_without = (tvalAfter.tv_sec-tvalBefore.tv_sec)*1000000LL + tvalAfter.tv_usec-tvalBefore.tv_usec;
    printf("Czas %lld\n",time_without );
    long long time_transposition = (tvalAfterTrans.tv_sec-tvalBeforeTrans.tv_sec)*1000000LL + tvalAfterTrans.tv_usec-tvalBeforeTrans.tv_usec;
    printf("Czas %lld\n",time_transposition);


  }
  else
  {
            printf("Nie można pomnożyć\n");
  }

    return 0;
}
