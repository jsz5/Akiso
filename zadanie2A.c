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
  for(int i=0; i<=64; i++)
  {
    signal(i, signalHandler);
  }
  int pid=getpid();
  for(int i=1; i<=64; i++)
  {
    kill(getpid(),i);
    printf("Wysłano sygnał %d\n", i);
    sleep(1);
  }
  return 0;
}
