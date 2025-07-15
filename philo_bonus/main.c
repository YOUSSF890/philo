#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h> //
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>


long ft_tim_dil() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

int main()
{
    int i = 0;
    int pid;

    printf("__-------->%ld\n",ft_tim_dil());
    while(i < 10)
    {
        pid = fork();
        printf("__-------->%ld\n",ft_tim_dil());
        while(pid == 0)
        {
            exit(0);
        }
        i++;
    }
    return (0);
}