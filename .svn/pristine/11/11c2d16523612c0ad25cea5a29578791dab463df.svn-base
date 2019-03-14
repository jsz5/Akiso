#include<stdio.h>
#include<stdlib.h>
#include <signal.h>
#include <unistd.h>
void signalHandler(int signum)
{
  printf("Złapano sygnał %d\n", signum);
}
int main()
{
  for(int i=0; i<10; i++)
  {
    signal(SIGUSR1, signalHandler);
  }

  for(int i=1; i<=64; i++)
  {

    printf("Wysłano sygnał %d\n", i);
    kill(getpid(),i);

  }
  return 0;
}
