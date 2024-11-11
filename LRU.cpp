#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for(i = 1; i < n; ++i) {
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    int frame[10], page[50], time[10];
    int i, j, pos, counter = 0, flag1, flag2;

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    printf("Enter the page reference sequence:\n");
    for(i = 0; i < pages; ++i) {
        scanf("%d", &page[i]);
    }

    // Initialize frames array with -1
    for(i = 0; i < frames; ++i) {
        frame[i] = -1;
    }

    // LRU Page Replacement Algorithm
    for(i = 0; i < pages; ++i) {
        flag1 = flag2 = 0;

        // Check if the page is already in a frame
        for(j = 0; j < frames; ++j) {
            if(frame[j] == page[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                pageHits++;
                break;
            }
        }

        // If the page is not in a frame
        if(flag1 == 0) {
            for(j = 0; j < frames; ++j) {
                if(frame[j] == -1) {  // Empty slot available
                    counter++;
                    pageFaults++;
                    frame[j] = page[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty slot, replace the least recently used page
        if(flag2 == 0) {
            pos = findLRU(time, frames);
            counter++;
            pageFaults++;
            frame[pos] = page[i];
            time[pos] = counter;
        }

        // Display current frame contents
        printf("\nFrames: ");
        for(j = 0; j < frames; ++j) {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Hits: %d", pageHits);
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

