#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define NUM_PHILOSOPHERS 2

sem_t *forks[NUM_PHILOSOPHERS];
sem_t *print_lock;
int running = 1;

void philosopher_action(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (running) {
        // Think
        sem_wait(print_lock);
        printf("Philosopher %d is thinking...\n", id);
        sem_post(print_lock);
        usleep(1000 * 500); // 0.5 sec

        // Pick up forks (left then right)
        sem_wait(forks[left_fork]);
        sem_wait(forks[right_fork]);

        // Eat
        sem_wait(print_lock);
        printf("Philosopher %d is eating...\n", id);
        sem_post(print_lock);
        usleep(1000 * 500); // 0.5 sec

        // Put down forks
        sem_post(forks[left_fork]);
        sem_post(forks[right_fork]);
    }
}

int main() {
    pid_t pid;
    int i;

    // Initialize semaphores
    print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        char name[20];
        sprintf(name, "/fork%d", i);
        forks[i] = sem_open(name, O_CREAT, 0644, 1);
    }

    // Create philosophers (child processes)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pid = fork();
        if (pid == 0) {
            philosopher_action(i);
            exit(0);
        }
    }

    // Let them run for a while
    sleep(5);
    running = 0;

    // Wait for all philosophers to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }

    // Clean up semaphores
    sem_close(print_lock);
    sem_unlink("/print_lock");
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_close(forks[i]);
        char name[20];
        sprintf(name, "/fork%d", i);
        sem_unlink(name);
    }

    return 0;
}