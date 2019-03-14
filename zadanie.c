#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>


int lsh_cd(char **args);
int lsh_exit(char **args);
char *command_names[] = {"cd", "exit"};
int (*command_function[]) (char **) =
{
  &lsh_cd,
  &lsh_exit
};
int commands_size()
{
  return sizeof(command_names) / sizeof(char *);
}

int lsh_cd(char **args)
{
  if (args[1] == NULL)
  {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  }
  else
  {
    if (chdir(args[1]) != 0)  perror("lsh");
  }
  return 1;
}

int lsh_exit(char **args)
{
    exit(EXIT_SUCCESS);
}
char *lsh_read_line()
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}
int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;
  pid = fork();
  if (pid == 0)
  {
    if (execvp(args[0], args) <0)
    {
      printf("Wystąpił błąd\n");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    printf("Nie udało się utworzyć procesu dziecka\n");
  }
  else
  {
    wait(NULL);
  }
  return 1;
}

int lsh_execute(char **args)
{
  int i;
  if (args[0] == NULL) return 1;
  for (i = 0; i < commands_size(); i++)
  {
    if (strcmp(args[0], command_names[i]) == 0)
    {
      return (*command_function[i])(args);
    }
  }
  return lsh_launch(args);
}
 void fail()
 {
     fprintf(stderr, "Blad alokacji pamieci\n" );
     exit(EXIT_FAILURE);
 }

char **lsh_split_line(char *line, char *deli)
{
  int splitted_size = 64, i = 0;
  char **splitted = malloc(splitted_size * sizeof(char*));
  char *s, **tokens_backup;

  if (!splitted) fail();

  s = strtok(line, deli);
  while (s != NULL)
  {
    splitted[i] = s;
    i++;

    if (i >= splitted_size) {
      splitted_size += 64;

      splitted = realloc(splitted, splitted_size * sizeof(char*));
      if (!splitted) fail();
    }

    s = strtok(NULL, deli);
  }
  splitted[i] = NULL;
  return splitted;
}

 void printDir()
 {
     char cwd[1024];
     getcwd(cwd, sizeof(cwd));
     printf("~%s ", cwd);
 }

void lsh_loop()
{
  int status;
  do
  {
    printDir();
    printf("> ");
    char *line = lsh_read_line();
    char **args = lsh_split_line(line, " \t\r\n\a");
    status = lsh_execute(args);
    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  signal(SIGCHLD, SIG_IGN);
  lsh_loop();
  return EXIT_SUCCESS;
}
