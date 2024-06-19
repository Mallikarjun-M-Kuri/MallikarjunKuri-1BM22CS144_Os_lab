#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t* forks;
sem_t mutex;

void* philosopher_one(void* num) {
    int id = *(int *)num;

    // Thinking
    printf("P %d is waiting\n", id);

    // Hungry
    sem_wait(&mutex);
    printf("P %d is granted to eat\n", id);
    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % 5]);
    sem_post(&mutex);

    // Eating
    sleep(1);

    // Finished eating
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % 5]);

    return NULL;
}

void* philosopher_two(void* num) {
    int id = *(int *)num;

    // Thinking
    printf("P %d is waiting\n", id);

    // Hungry
    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % 5]);
    printf("P %d is granted to eat\n", id);

    // Eating
    sleep(1);

    // Finished eating
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % 5]);

    return NULL;
}

int main() {
    int num_philosophers, num_hungry;
    printf("DINING PHILOSOPHER PROBLEM\n");
    printf("Enter the total no. of philosophers: ");
    scanf("%d", &num_philosophers);

    printf("How many are hungry: ");
    scanf("%d", &num_hungry);

    int hungry_positions[num_hungry];
    for (int i = 0; i < num_hungry; i++) {
        printf("Enter philosopher %d position: ", i + 1);
        scanf("%d", &hungry_positions[i]);
        hungry_positions[i]--; // Adjusting position to 0-indexed
    }

    forks = (sem_t*)malloc(num_philosophers * sizeof(sem_t));
    pthread_t philosophers[num_hungry];
    int ids[num_hungry];

    // Initialize the semaphores
    for (int i = 0; i < num_philosophers; i++) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);

    int choice;
    printf("\n1. One can eat at a time\t2. Two can eat at a time\t3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nAllow one philosopher to eat at any time\n");
        for (int i = 0; i < num_hungry; i++) {
            ids[i] = hungry_positions[i];
            pthread_create(&philosophers[i], NULL, philosopher_one, &ids[i]);
        }
    } else if (choice == 2) {
        printf("\nAllow two philosophers to eat at the same time\n");
        for (int i = 0; i < num_hungry; i++) {
            ids[i] = hungry_positions[i];
            pthread_create(&philosophers[i], NULL, philosopher_two, &ids[i]);
        }
    } else {
        printf("Exiting program.\n");
        free(forks);
        return 0;
    }

    for (int i = 0; i < num_hungry; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the semaphores
    for (int i = 0; i < num_philosophers; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    free(forks);

    return 0;
}
