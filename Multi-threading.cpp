#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *print_hello(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("Hello from thread 1\n");
        sleep(1); 
    }
    return NULL;
}


void *print_world(void *arg) {
    for (int i = 0; i < 5; i++) {
        printf("World from thread 2\n");
        sleep(1);  
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

   
    if (pthread_create(&thread1, NULL, print_hello, NULL) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

   
    if (pthread_create(&thread2, NULL, print_world, NULL) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished executing.\n");
    return 0;
}

