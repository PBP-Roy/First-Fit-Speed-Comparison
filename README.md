# First-Fit-Speed-Comparison
### Studi Kasus Dunia Nyata

**Masalah: Pengelolaan Memori pada Sistem Embedded di Robotika**

Dalam sistem embedded seperti yang digunakan dalam robotika, memori seringkali terbatas dan harus dikelola dengan efisien. Sebagai contoh, sebuah robot yang memiliki berbagai modul untuk penginderaan, pengolahan data, dan kontrol motor, memerlukan manajemen memori yang baik untuk memastikan semua modul dapat berjalan tanpa terjadi kehabisan memori atau penundaan yang signifikan.

Dalam studi kasus ini, kita akan mensimulasikan pengelolaan memori pada robot yang memiliki blok-blok memori dengan ukuran bervariasi. Modul-modul robot memerlukan alokasi memori untuk menjalankan tugas-tugas tertentu seperti pemrosesan gambar, pengenalan objek, dan pengendalian motor. Pengelolaan memori yang buruk dapat menyebabkan fragmentasi, yang dapat mengakibatkan kegagalan alokasi memori pada saat dibutuhkan.

**Solusi: Implementasi Algoritma First Fit**

Algoritma first fit dapat digunakan untuk mengalokasikan memori pada blok pertama yang cukup besar untuk menampung data yang diperlukan oleh modul-modul robot. Ini memungkinkan pengalokasian memori yang cepat dan efisien, meskipun dapat menyebabkan fragmentasi jika tidak dikelola dengan baik.

Berikut adalah program C yang mensimulasikan pengalokasian memori menggunakan algoritma first fit dan algoritma lain (misalnya, best fit). Program ini akan menunjukkan bagaimana algoritma first fit dapat meningkatkan kecepatan alokasi memori dan mengurangi kemungkinan fragmentasi.

### Program Simulasi Pengelolaan Memori

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 1024 // Total memory in bytes
#define BLOCK_COUNT 20   // Number of memory blocks

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

void* first_fit_allocate(int size) {
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory_blocks[i].free && memory_blocks[i].size >= size) {
            memory_blocks[i].free = 0;
            return memory_blocks[i].address;
        }
    }
    return NULL;
}

void* best_fit_allocate(int size) {
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
        return memory_blocks[best_index].address;
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
    print_memory_status();

    clock_t start, end;
    double first_fit_time, best_fit_time;

    // Simulate memory allocation using first fit
    start = clock();
    for (int i = 0; i < 10; i++) {
        void* ptr = first_fit_allocate(rand() % 128 + 16);
        if (ptr != NULL) free_memory(ptr);
    }
    end = clock();
    first_fit_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Simulate memory allocation using best fit
    start = clock();
    for (int i = 0; i < 10; i++) {
        void* ptr = best_fit_allocate(rand() % 128 + 16);
        if (ptr != NULL) free_memory(ptr);
    }
    end = clock();
    best_fit_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("First Fit Allocation Time: %f seconds\n", first_fit_time);
    printf("Best Fit Allocation Time: %f seconds\n", best_fit_time);

    print_memory_status();

    return 0;
}
```

### Penjelasan Program

- **init_memory_blocks**: Menginisialisasi blok-blok memori dengan ukuran acak dan menandainya sebagai "bebas".
- **first_fit_allocate**: Mengalokasikan memori menggunakan algoritma first fit.
- **best_fit_allocate**: Mengalokasikan memori menggunakan algoritma best fit.
- **free_memory**: Membebaskan memori yang telah dialokasikan.
- **print_memory_status**: Menampilkan status blok-blok memori.

### Perbandingan Kecepatan

Program ini mengukur waktu yang diperlukan untuk mengalokasikan memori menggunakan algoritma first fit dan best fit. Dari hasil eksekusi, Anda bisa melihat apakah first fit lebih cepat dalam alokasi memori dibandingkan dengan best fit, terutama dalam situasi di mana alokasi memori harus dilakukan dengan cepat seperti dalam sistem embedded.

### Hasil dan Diskusi

Dalam skenario dunia nyata, first fit seringkali lebih cepat karena mengalokasikan memori pada blok pertama yang cukup besar, namun mungkin menyebabkan fragmentasi. Sebaliknya, best fit mencari blok terkecil yang cukup besar untuk meminimalkan fragmentasi tetapi bisa lebih lambat karena memerlukan lebih banyak perbandingan. Hasil perbandingan kecepatan di program ini akan menunjukkan trade-off antara kecepatan dan efisiensi memori.
