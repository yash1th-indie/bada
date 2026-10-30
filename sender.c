#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    void *shared_memory;
    char buff[100];
    int shmid, bytes;

    shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);

    if (shared_memory == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    printf("Process attached at %p\n", shared_memory);
    printf("Enter data to write to shared memory:\n");

    bytes = read(0, buff, sizeof(buff) - 1);

    if (bytes <= 0)
    {
        printf("No input received.\n");
        shmdt(shared_memory);
        return 1;
    }

    buff[bytes] = '\0';
    strcpy(shared_memory, buff);

    printf("Data written is %s\n", (char *)shared_memory);

    shmdt(shared_memory);

    return 0;
}