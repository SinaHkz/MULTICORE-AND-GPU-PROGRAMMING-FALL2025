#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3
#define ITEMS_TO_PRODUCE 5

int buffer[BUFFER_SIZE];
int count = 0;       // number of items currently in buffer
int in = 0;          // next position to produce
int out = 0;         // next position to consume

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

// --- Producer thread function ---
void* producer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        int item = i + (id * 100); // unique item per producer

        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        if (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer %d produced %d\n", id, item);

        pthread_mutex_unlock(&mutex);
        // Signal that buffer is not empty
        pthread_cond_signal(&not_empty);

        // A random delay to simulate processing time
        usleep((rand() % 500) * 1000); 
    }
    return NULL;
}

// --- Consumer thread function ---
void* consumer(void* arg) {
    int id = *(int*)arg;
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        if (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        // Remove item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        sleep(1);  // A small delay to simulate processing time for the item
        printf("Consumer %d consumed %d\n", id, item);

        pthread_mutex_unlock(&mutex);
        // Signal that buffer is not full
        pthread_cond_signal(&not_full);

        // A random delay to simulate processing time
        usleep((rand() % 700) * 1000);
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // NOTE: Consumers run indefinitely in this version
    // In practice, you'd signal them to stop after all items are consumed
    // You should handle proper shutdown of consumer threads here instead of cancelling them

    sleep(5);

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_cancel(consumers[i]);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
