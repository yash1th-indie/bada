#include <stdio.h>

int mutex = 1;
int wrt = 1;
int readcount = 0;
int data = 0;

void wait(int *s)
{
    while (*s <= 0);
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void reader()
{
    wait(&mutex);
    readcount++;

    if (readcount == 1)
        wait(&wrt);

    signal(&mutex);

    printf("\nReader reads data: %d", data);

    wait(&mutex);
    readcount--;

    if (readcount == 0)
        signal(&wrt);

    signal(&mutex);
}

void writer()
{
    wait(&wrt);

    data++;
    printf("\nWriter writes data: %d", data);

    signal(&wrt);
}

int main()
{
    int n;

    printf("\n1. Reader\n2. Writer\n3. Exit");

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                reader();
                break;

            case 2:
                writer();
                break;

            case 3:
                return 0;

            default:
                printf("\nInvalid choice");
        }
    }
}