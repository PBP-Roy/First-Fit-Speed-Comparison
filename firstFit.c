#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

#define BLOCK_COUNT 20 // Number of variating memory blocks

typedef struct {
    int size;
    int free;
    void* address;
} MemoryBlock;

MemoryBlock memory_blocks[BLOCK_COUNT];

void init_memory_blocks() {
    srand(time(NULL));
    for (int i = 0; i < BLOCK_COUNT; i++) {
        memory_blocks[i].size = rand() % 128 + 32; // Block sizes between 32 and 160 bytes
        memory_blocks[i].free = 1;
        memory_blocks[i].address = malloc(memory_blocks[i].size);
    }
}

void* first_fit_allocate(int size, int *internal_frag) {
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory_blocks[i].free && memory_blocks[i].size >= size) {
            memory_blocks[i].free = 0;
            *internal_frag += (memory_blocks[i].size - size); // Calculate internal fragmentation
            return memory_blocks[i].address;
        }
    }
    return NULL;
}

void* best_fit_allocate(int size, int *internal_frag) {
    int best_index = -1;
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory_blocks[i].free && memory_blocks[i].size >= size) {
            if (best_index == -1 || memory_blocks[i].size < memory_blocks[best_index].size) {
                best_index = i;
            }
        }
    }
    if (best_index != -1) {
        memory_blocks[best_index].free = 0;
        *internal_frag += (memory_blocks[best_index].size - size); // Calculate internal fragmentation
        return memory_blocks[best_index].address;
    }
    return NULL;
}

void* worst_fit_allocate(int size, int *internal_frag) {
    int worst_index = -1;
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory_blocks[i].free && memory_blocks[i].size >= size) {
            if (worst_index == -1 || memory_blocks[i].size > memory_blocks[worst_index].size) {
                worst_index = i;
            }
        }
    }
    if (worst_index != -1) {
        memory_blocks[worst_index].free = 0;
        *internal_frag += (memory_blocks[worst_index].size - size); // Calculate internal fragmentation
        return memory_blocks[worst_index].address;
    }
    return NULL;
}

void free_memory(void* ptr) {
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory_blocks[i].address == ptr) {
            memory_blocks[i].free = 1;
            break;
        }
    }
}

void print_memory_status() {
    printf("Memory Status:\n");
    for (int i = 0; i < BLOCK_COUNT; i++) {
        printf("Block %d: Size = %d, Free = %s\n", i + 1, memory_blocks[i].size, memory_blocks[i].free ? "Yes" : "No");
    }
    printf("\n");
}

int main() {
    init_memory_blocks();

    clock_t start, end;
    double first_fit_time, best_fit_time, worst_fit_time;

    int internal_frag_first_fit = 0, internal_frag_best_fit = 0, internal_frag_worst_fit = 0;

    // Simulate memory allocation using first fit
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        void* ptr = first_fit_allocate(rand() % 128 + 16, &internal_frag_first_fit);
        if (ptr != NULL) free_memory(ptr);
    }
    end = clock();
    first_fit_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Simulate memory allocation using best fit
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        void* ptr = best_fit_allocate(rand() % 128 + 16, &internal_frag_best_fit);
        if (ptr != NULL) free_memory(ptr);
    }
    end = clock();
    best_fit_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Simulate memory allocation using worst fit
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        void* ptr = worst_fit_allocate(rand() % 128 + 16, &internal_frag_worst_fit);
        if (ptr != NULL) free_memory(ptr);
    }
    end = clock();
    worst_fit_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("First Fit Allocation Time: %f seconds\n", first_fit_time);
    printf("Best Fit Allocation Time: %f seconds\n", best_fit_time);
    printf("Worst Fit Allocation Time: %f seconds\n", worst_fit_time);

    printf("\n");

    printf("First Fit - Fragmentation: %d bytes\n", internal_frag_first_fit);
    printf("Best Fit - Fragmentation: %d bytes\n", internal_frag_best_fit);
    printf("Worst Fit - Fragmentation: %d bytes\n", internal_frag_worst_fit);

    return 0;
}