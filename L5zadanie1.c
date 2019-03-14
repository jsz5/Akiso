#include <unistd.h>
#include<stdlib.h>

char *convert(int variable, int base)
{
  char *characters={"0123456789ABCDEFG"};
  int conversion_size = 64;
  char *conversion = malloc(conversion_size*sizeof(char));
  int i=0;
  while(variable>0)
  {
    conversion[i]=characters[variable%base];
    variable/=base;
    i++;
    if (i >= conversion_size) {
      conversion_size += 64;
      conversion = realloc(conversion, conversion_size * sizeof(char*));
    }
  }
  char *result= malloc(i*sizeof(char));
  int r=i-1;
  for(int j=0; j<i; j++,r--)
  {
    result[j]=conversion[r];
  }
  result[i]='\0';
  return result;
}
void myprintf(char *output,...)
{
  int i=0;
  int w;
  char *p = (char *) &output +sizeof(output);
  while(output[i]!='\0')
  {
    if(output[i]=='%')
    {
        i++;
        switch (output[i])
        {
            case 's':
            {
              char *r=*((char **)p);
              p+=sizeof(r);
              int h=0;
              while(r[h]!='\0')
              {
                  write(1,&r[h],sizeof(char));
                  h++;
              }
              break;
            }
            case 'd':
            {
                w = *((int *)p);
                p+=sizeof(int);
                char *t=convert(w,10);
                write(1,t,sizeof(t));
                break;
            }
            case 'x':
            {
              w = *((int *)p);
              p+=sizeof(int);
              char *t=convert(w,16);
              write(1,t,sizeof(t));
              break;
            }
            case 'b':
            {
              w = *((int *)p);
              p+=sizeof(int);
              char *t=convert(w,2);
              write(1,t,sizeof(t));
              break;
            }
        }

      }
      else write(1, &output[i],sizeof(char));
        i++;
    }
}
int input_conversion(char *q, int base)
{
  char *characters={"0123456789ABCDEFG"};
  int i=0;
  int number=0;
  while(q[i]!='\0')
  {
    for(int j=0; j<16; j++)
    {
      if(characters[j]==q[i])
      {
        number*=base;
        number+=j;
        break;
      }
    }
    i++;
  }
  return number;
}
void myscanf(char *input,...)
{
  char *p = (char *) &input +sizeof(input);
  int i=0;
  int *w;
  while(input[i]!='\0')
  {
    if(input[i]=='%')
    {
        i++;
        switch (input[i])
        {
            case 's':
            {
              char *q=malloc(1024*sizeof(char));
              read(0,q,1024);
              char **r=*((char ***)p);
              p+=sizeof(r);
              *r=q;
              break;
            }
            case 'd':
            {
                w = *((int **)p);
                char *q=malloc(1024*sizeof(char));
                read(0,q,1024);
                *w=input_conversion(q,10);
                p+=sizeof(w);
                break;
            }
            case 'x':
            {
              w = *((int **)p);
              char *q=malloc(1024*sizeof(char));
              read(0,q,1024);
              *w=input_conversion(q,16);
              p+=sizeof(w);
              break;
            }
            case 'b':
            {
              w = *((int **)p);
              char *q=malloc(1024*sizeof(char));
              read(0,q,1024);
              *w=input_conversion(q,2);
              p+=sizeof(w);
              break;
            }
        }

      }
      i++;
    }
}
int main()
{

  //myprintf("This will %s be output %d to %b standard %x out %d\n",p,778, 3, 10,16);
  int t;
  int s;
  char *d;
  myscanf("%x", &s);


  return 0;
}
