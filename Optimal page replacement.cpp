#include <stdio.h>

int findOptimal(int page[], int frame[], int pages, int frames, int current) {
    int i, j, pos = -1, farthest = current;

    for(i = 0; i < frames; i++) {
        int nextUse = pages; // Default to a large value if the page isn't found again
        for(j = current + 1; j < pages; j++) {
            if(frame[i] == page[j]) {
                nextUse = j;
                break;
            }
        }
        
        if(nextUse > farthest) {
            farthest = nextUse;
            pos = i;
        }
    }
    
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    int frame[10], page[50];
    int i, j, flag1, flag2, pos;

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

    // Optimal Page Replacement Algorithm
    for(i = 0; i < pages; ++i) {
        flag1 = flag2 = 0;

        // Check if the page is already in a frame
        for(j = 0; j < frames; ++j) {
            if(frame[j] == page[i]) {
                flag1 = flag2 = 1;
                pageHits++;
                break;
            }
        }

        // If the page is not in a frame
        if(flag1 == 0) {
            for(j = 0; j < frames; ++j) {
                if(frame[j] == -1) {  // Empty slot available
                    frame[j] = page[i];
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty slot, replace the page that will not be used for the longest time
        if(flag2 == 0) {
            pos = findOptimal(page, frame, pages, frames, i);
            frame[pos] = page[i];
            pageFaults++;
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

