#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

typedef struct {
    int size;
    int isAllocated;
} Partition;

typedef struct {
    int size;
    int isAllocated;
    int partitionIndex;
} Process;

void allocate(Process processes[], int processCount, Partition partitions[], int partitionCount, int (*findIndex)(Partition[], int, int)) {
    int totalFragmentation = 0;

    printf("\nFile No.\tProcess Size\tBlock No.\tBlock Size\tFragments\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < processCount; i++) {
        int index = findIndex(partitions, partitionCount, processes[i].size);
        if (index != -1) {
            processes[i].isAllocated = 1;
            processes[i].partitionIndex = index;
            partitions[index].isAllocated = 1;

            int fragmentation = partitions[index].size - processes[i].size;
            totalFragmentation += fragmentation;

            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, processes[i].size, index, partitions[index].size, fragmentation);
        } else {
            printf("%d\t\t%d\t\t-\t\t-\t\t-\tProcess could not be allocated\n", i, processes[i].size);
        }
    }

    printf("\nTotal Fragmentation: %d\n", totalFragmentation);
}

int firstFitIndex(Partition partitions[], int partitionCount, int processSize) {
    for (int i = 0; i < partitionCount; i++) {
        if (!partitions[i].isAllocated && partitions[i].size >= processSize) {
            return i;
        }
    }
    return -1;
}

int bestFitIndex(Partition partitions[], int partitionCount, int processSize) {
    int bestIndex = -1;
    for (int i = 0; i < partitionCount; i++) {
        if (!partitions[i].isAllocated && partitions[i].size >= processSize) {
            if (bestIndex == -1 || partitions[i].size < partitions[bestIndex].size) {
                bestIndex = i;
            }
        }
    }
    return bestIndex;
}

int worstFitIndex(Partition partitions[], int partitionCount, int processSize) {
    int worstIndex = -1;
    for (int i = 0; i < partitionCount; i++) {
        if (!partitions[i].isAllocated && partitions[i].size >= processSize) {
            if (worstIndex == -1 || partitions[i].size > partitions[worstIndex].size) {
                worstIndex = i;
            }
        }
    }
    return worstIndex;
}

void reset(Partition partitions[], int partitionCount, Process processes[], int processCount) {
    for (int i = 0; i < partitionCount; i++) partitions[i].isAllocated = 0;
    for (int i = 0; i < processCount; i++) {
        processes[i].isAllocated = 0;
        processes[i].partitionIndex = -1;
    }
}

int main() {
    int partitionCount, processCount, choice, fixedOrVariable, alreadyAllocated;
    Partition partitions[MAX_PARTITIONS];
    Process processes[MAX_PROCESSES];

    printf("Enter the number of partitions: ");
    scanf("%d", &partitionCount);

    printf("Enter the size of each partition:\n");
    for (int i = 0; i < partitionCount; i++) {
        printf("Partition %d: ", i);
        scanf("%d", &partitions[i].size);
        partitions[i].isAllocated = 0;
    }

    printf("Enter the number of processes: ");
    scanf("%d", &processCount);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: ", i);
        scanf("%d", &processes[i].size);
        processes[i].isAllocated = 0;
        processes[i].partitionIndex = -1;
    }

    printf("Choose memory allocation strategy:\n1. First-Fit\n2. Best-Fit\n3. Worst-Fit\n");
    scanf("%d", &choice);


    int (*allocationStrategy)(Partition[], int, int) = NULL;

    switch (choice) {
        case 1: allocationStrategy = firstFitIndex; break;
        case 2: allocationStrategy = bestFitIndex; break;
        case 3: allocationStrategy = worstFitIndex; break;
        default: printf("Invalid choice\n"); return 1;
    }

    printf("\nMemory Management Scheme:\n");
    printf("-----------------------------------------------------------------\n");
    printf("File No.\tProcess Size\tBlock No.\tBlock Size\tFragments\n");
    printf("-----------------------------------------------------------------\n");

    allocate(processes, processCount, partitions, partitionCount, allocationStrategy);

    return 0;
}






