#include<unistd.h>
int main()
{
    setuid(0);
    execlp("sudo","sudo","bash", NULL );
    return 0;
    /* pierwsze sudo: polecenie żeby zacząć ("sudo")
        drugie sudo i bash: uruchamia bash jako root
    */
}

/*
gcc zadanie1.c -o zad1
sudo chown root:root zad1
sudo chmod +s zad1
./zad1
*/
