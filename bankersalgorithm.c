#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allot[MAX_PROCESSES][MAX_RESOURCES], int np, int nr) {
    for (int i = 0 ; i < np ; i++)
        for (int j = 0 ; j < nr ; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int np, int nr) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allot, np, nr);

    bool finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < nr ; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < np) {
        bool found = false;
        for (int p = 0; p < np; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < nr; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == nr) {
                    for (int k = 0 ; k < nr ; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("System is not in safe state\n");
            return false;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < np ; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    int np, nr;
    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resource types: ");
    scanf("%d", &nr);

    int processes[MAX_PROCESSES];
    for(int i = 0; i < np; i++) processes[i] = i;

    int avail[MAX_RESOURCES];
    printf("Enter available resources: ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &avail[i]);

    int max[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter maximum resource matrix:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &max[i][j]);
    }

    int allot[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter allocation resource matrix:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &allot[i][j]);
    }

    isSafe(processes, avail, max, allot, np, nr);

    return 0;
}

