#include <stdio.h>
#include <stdbool.h>

void fifoPageReplacement(int pages, int incomingStream[], int frames) {
    int pageFaults = 0;
    int temp[frames];
    int front = 0;

    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    printf("\n--- FIFO Page Replacement Algorithm ---\n");
    printf("\nIncoming\t\tFrame 1\t\tFrame 2\t\tFrame 3\t\n");

    for (int m = 0; m < pages; m++) {
        bool pageFault = true;

        for (int n = 0; n < frames; n++) {
            if (temp[n] == incomingStream[m]) {
                pageFault = false;
                break;
            }
        }

        if (pageFault) {
            temp[front] = incomingStream[m];
            front = (front + 1) % frames;
            pageFaults++;
        }

        printf("%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf("%d\t\t", temp[n]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
}

void lruPageReplacement(int pages, int incomingStream[], int frames) {
    int pageFaults = 0;
    int temp[frames];
    int used[frames];

    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
        used[m] = 0;
    }

    printf("\n--- LRU Page Replacement Algorithm ---\n");
    printf("\nIncoming\tFrame 1\tFrame 2\tFrame 3\n");

    for (int m = 0; m < pages; m++) {
        bool pageFault = true;
        int leastUsedIdx = 0;

        for (int n = 0; n < frames; n++) {
            if (temp[n] == incomingStream[m]) {
                pageFault = false;
                used[n] = m + 1;
                break;
            }
            if (used[n] < used[leastUsedIdx]) {
                leastUsedIdx = n;
            }
        }

        if (pageFault) {
            temp[leastUsedIdx] = incomingStream[m];
            used[leastUsedIdx] = m + 1;
            pageFaults++;
        }

        printf("%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf("%d\t\t", temp[n]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
}

void optimalPageReplacement(int pages, int incomingStream[], int frames) {
    int pageFaults = 0;
    int temp[frames];

    for (int m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    printf("\n--- Optimal Page Replacement Algorithm ---\n");
    printf("\nIncoming\tFrame 1\tFrame 2\tFrame 3\n");

    for (int m = 0; m < pages; m++) {
        bool pageFault = true;
        int replaceIdx = -1;
        int farthest = m;
  
        for (int n = 0; n < frames; n++) {
            if (temp[n] == incomingStream[m]) {
                pageFault = false;
                break;
            }
        }

        if (pageFault) {
            for (int n = 0; n < frames; n++) {
                int j;
                for (j = m + 1; j < pages; j++) {
                    if (temp[n] == incomingStream[j]) {
                        if (j > farthest) {
                            farthest = j;
                            replaceIdx = n;
                        }
                        break;
                    }
                }

                if (j == pages) {
                    replaceIdx = n;
                    break;
                }
            }

            if (replaceIdx == -1) {
                replaceIdx = 0;
            }

            temp[replaceIdx] = incomingStream[m];
            pageFaults++;
        }

        printf("%d\t\t", incomingStream[m]);
        for (int n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf("%d\t\t", temp[n]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
}

int main() {
    int pages;
    printf("Enter number of pages in incoming stream: ");
    scanf("%d", &pages);

    int incomingStream[pages];
    printf("Enter the sequence of pages:\n");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &incomingStream[i]);
    }

    int frames;
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    fifoPageReplacement(pages, incomingStream, frames);
    lruPageReplacement(pages, incomingStream, frames);
    optimalPageReplacement(pages, incomingStream, frames);

    return 0;
}
