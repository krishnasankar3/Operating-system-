#include <stdio.h>

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    int frame[10], page[50], flag1, flag2;
    int i, j, k, pos = 0;

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

    // FIFO Page Replacement Algorithm
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
                    flag2 = 1;
                    pageFaults++;
                    break;
                }
            }
        }

        // If the page is not in a frame and no empty slot, replace the oldest page
        if(flag2 == 0) {
            frame[pos] = page[i];
            pos = (pos + 1) % frames;
            pageFaults++;
        }

        // Display current frame contents
        printf("\nFrames: ");
        for(k = 0; k < frames; ++k) {
            if(frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Hits: %d", pageHits);
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

