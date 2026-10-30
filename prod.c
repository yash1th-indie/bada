#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 5;
int x = 0;

void wait(int *s)
{
    while (*s <= 0);
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void producer()
{
    wait(&empty);
    wait(&mutex);

    x++;
    printf("\nProducer produces item %d", x);

    signal(&mutex);
    signal(&full);
}

void consumer()
{
    wait(&full);
    wait(&mutex);

    printf("\nConsumer consumes item %d", x);
    x--;

    signal(&mutex);
    signal(&empty);
}

int main()
{
    int n;

    printf("\n1. Producer\n2. Consumer\n3. Exit");

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                if (empty != 0)
                    producer();
                else
                    printf("\nBuffer is full");
                break;

            case 2:
                if (full != 0)
                    consumer();
                else
                    printf("\nBuffer is empty");
                break;

            case 3:
                return 0;

            default:
                printf("\nInvalid choice");
        }
    }
}