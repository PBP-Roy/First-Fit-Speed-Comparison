# Memory Fragmentation
## Apa itu Memory Fragmentation?
Memory Fragmentation adalah masalah yang terjadi dalam pengelolaan memori di mana memori tidak dapat digunakan secara efisien meskipun masih ada ruang kosong yang tersisa. Ini terjadi karena ruang kosong tersebut terpecah-pecah menjadi potongan-potongan kecil yang tidak bisa dialokasikan untuk kebutuhan program yang lebih besar. Ada dua jenis fragmentasi memori: __Fragmentasi Internal__ dan __Fragmentasi Eksternal__.
### Internal Fragmentation
Internal Fragmentation terjadi ketika blok memori yang dialokasikan untuk suatu proses atau program lebih besar daripada yang sebenarnya diperlukan. Sebagai hasilnya, sebagian dari blok tersebut tidak digunakan dan terbuang sia-sia. Meskipun ruang tersebut masih berada di dalam blok yang dialokasikan, program tidak dapat menggunakannya karena sudah dianggap sebagai bagian dari blok yang diassign oleh sistem operasi.

#### Contoh
![alt text](image-4.png)

### External Fragmentation
External Fragmentation terjadi ketika ada cukup total memori kosong di sistem, tetapi blok-blok memori tersebut tersebar atau terpecah-pecah dalam bagian-bagian kecil yang tidak berurutan, sehingga tidak ada satu blok besar yang bisa dialokasikan untuk proses baru yang membutuhkan memori besar. Hal ini membuat memori yang tersisa tidak bisa digunakan meskipun secara total jumlahnya memadai.

#### Contoh
Terdapat sebuah memori yang dibagi menjadi 8 blok, tiap blok nya berukuran 1KB, sehingga total memori sebesar 8KB.
![alt text](image-1.png)
Program mengalokasikan 1KB, 4KB, dan 2KB.
![alt text](image-2.png)
Program kemudian mendealokasikan 1KB dan 4KB, karena sudah tidak dibutuhkan.
![alt text](image-3.png)
Sekarang program ingin mengalokasikan memori sebesar 6KB, namun tidak bisa. Meskipun total memori yang tersedia berjumlah 6KB, tetapi blok-blok memori nya tidak kontigu. Inilah yang disebut dengan fragmentasi memori.

## Bagaimana Memory Fragmentation dapat Mempengaruhi Sistem?
Memory Fragmentation dapat mempengaruhi sistem secara signifikan, terutama dalam hal efisiensi penggunaan memori dan performa.

### Penggunaan Memori yang Tidak Efisien
Fragmentasi menyebabkan ruang memori tidak digunakan secara optimal. Meskipun total memori kosong yang tersedia mungkin cukup besar, fragmentasi dapat membuat memori tersebut tidak dapat dialokasikan untuk proses yang memerlukan. Inefisiensi ini terutama terlihat dalam fragmentasi eksternal, di mana blok-blok memori kosong tersebar, tidak memungkinkan memori besar untuk dialokasikan meskipun ada cukup total memori.

__Fragmentasi Internal__: Ruang kosong dalam blok yang telah dialokasikan tidak bisa digunakan untuk keperluan lain. Misalnya, jika sistem menggunakan alokasi blok berukuran tetap seperti 4 KB dan suatu proses hanya membutuhkan 2 KB, 2 KB yang tersisa di dalam blok tersebut akan terbuang sia-sia.
__Fragmentasi Eksternal__: Jika ada beberapa ruang kosong kecil yang tersebar di berbagai tempat dalam memori, proses baru yang membutuhkan memori kontinu dalam jumlah besar mungkin tidak bisa mendapatkan alokasi meskipun total ruang kosong mencukupi.

Penggunaan memori yang tidak efisien ini dapat menyebabkan kegagalan alokasi memori, meskipun secara total masih ada memori yang tersedia. Sistem mungkin terlihat "kehabisan" memori ketika sebenarnya memori tersebut terfragmentasi menjadi potongan-potongan kecil yang tidak bisa digunakan secara efektif.

### Penurunaan Performa
__Waktu Alokasi Memori yang Lebih Lama__: Sistem operasi atau pengelola memori harus bekerja lebih keras untuk menemukan blok memori yang sesuai untuk dialokasikan. Pada sistem dengan fragmentasi eksternal yang tinggi, pencarian ruang memori kontinu yang besar akan menjadi sulit dan memerlukan lebih banyak waktu, karena banyak ruang kecil yang tersebar. Ini dapat meningkatkan waktu yang dibutuhkan untuk mengeksekusi program atau proses baru.

__Frekuensi Penggunaan Disk Swap Meningkat__: Ketika memori fisik penuh atau sangat terfragmentasi, sistem mungkin harus menggunakan mekanisme swap ke disk, yaitu memindahkan data dari RAM ke disk sebagai solusi sementara. Disk swap jauh lebih lambat dibandingkan dengan akses langsung ke memori fisik, yang pada gilirannya menurunkan kinerja keseluruhan sistem.

__Fragmentasi Internal__: Pada fragmentasi internal, alokasi blok-blok memori yang lebih besar dari yang diperlukan dapat mengakibatkan memori terpakai secara tidak optimal, mengurangi ruang memori untuk proses lain. Proses baru yang membutuhkan memori mungkin lebih sering gagal dijalankan atau tertunda karena tidak adanya blok yang cukup besar untuk dialokasikan.

Pengelolaan memori yang lambat akibat fragmentasi dapat menurunkan responsivitas aplikasi dan sistem secara keseluruhan. Sistem operasi harus menghabiskan lebih banyak waktu untuk mengatur memori, sehingga memperlambat kinerja aplikasi yang berjalan.

## Solusi Apa yang Bisa Diterapkan untuk Mengatasi Memory Fragmentation?

### 1. Mengimplementasikan Algoritma Alokasi Memori
Untuk mengurangi fragmentasi dan memastikan penggunaan memori yang lebih efisien, berbagai algoritma pengelolaan memori telah dikembangkan. Terdapat tiga algoritma yang umum digunakan:

+ __First Fit__: Mengalokasikan blok memori pertama yang cukup besar untuk memenuhi permintaan.
+ __Best Fit__: Mencari blok memori terkecil yang cukup besar untuk memenuhi permintaan, dengan harapan meminimalkan sisa memori yang tidak terpakai.
+ __Worst Fit__: Mencari blok memori terbesar yang tersedia, dengan harapan meminimalkan fragmentasi dengan membagi blok besar menjadi bagian yang lebih kecil.

Pada eksperimen kelompok kami di pertemuan-pertemuan sebelumnya, ditemukan bahwa algoritma __first fit lebih cepat__ dibanding algoritma lainnya, tetapi sisa __fragmentasi__ first fit yang __paling banyak__. Algoritma __best fit__ memakan __waktu__ yang __paling lama__, tetapi menyisakan __fragmentasi paling sedikit__ jika dibandingkan dengan kedua algoritma lain.

![alt text](image-5.png)

### 2. Compaction
Pemadatan digunakan untuk mengatasi **fragmentasi eksternal**, di mana ada banyak blok memori kosong kecil yang tersebar. Algoritma ini menggabungkan blok-blok kecil ini menjadi satu blok besar untuk memaksimalkan penggunaan memori.

## Alokasi Memori Pada OS
algoritma manajemen memori pada sistem operasi (OS) bertujuan untuk mengelola alokasi, penggunaan, dan pembebasan memori secara efisien. Ada beberapa aspek kunci dalam manajemen memori, seperti pengelolaan memori fisik (RAM) dan memori virtual. Berikut beberapa algoritma yang digunakan dalam OS:

Algoritma manajemen memori dalam sistem operasi (OS) digunakan untuk mengatur alokasi dan dealokasi memori fisik dan virtual, serta untuk mengoptimalkan penggunaan sumber daya memori. Berikut beberapa algoritma manajemen memori yang umum diterapkan dalam OS:

### 1. **Swapping**

- **Swapping** adalah proses memindahkan proses yang tidak aktif dari memori utama ke disk (memori sekunder) untuk membuat ruang bagi proses yang sedang aktif. Ketika proses tersebut kembali dibutuhkan, OS akan menukarnya kembali ke memori utama.

### 2. **Paging**

- **Paging** membagi memori fisik menjadi blok-blok kecil yang disebut _frames_ dan memori logis menjadi blok-blok kecil yang disebut _pages_. Ketika sebuah proses dijalankan, hanya halaman yang dibutuhkan yang dimuat ke dalam memori fisik. Ini memungkinkan OS untuk menjalankan proses yang lebih besar daripada memori fisik yang tersedia.

### 3. **Segmentation**

- **Segmentation** membagi memori menjadi segmen-segmen dengan ukuran yang berbeda sesuai dengan logika program, seperti segmen untuk kode, data, dan tumpukan (_stack_). Setiap segmen memiliki basis alamat dan panjangnya sendiri, sehingga mendukung pemrograman modular.

### 4. **Virtual Memory**

- **Virtual Memory** adalah teknik di mana OS membuat ilusi memori yang lebih besar dari memori fisik sebenarnya. Ini memungkinkan program untuk menggunakan lebih banyak memori daripada yang tersedia di RAM dengan memanfaatkan ruang penyimpanan pada disk. Konsep utama dalam memori virtual adalah penggunaan tabel halaman (_page table_) untuk memetakan alamat virtual ke alamat fisik.

### 5. **Memory Allocation Algorithms**

- **First Fit**: Mencari dan menggunakan blok memori pertama yang cukup besar untuk kebutuhan proses.
- **Best Fit**: Mencari blok memori terkecil yang cukup besar untuk alokasi, mengurangi fragmentasi eksternal.
- **Worst Fit**: Mencari blok memori terbesar yang tersedia, digunakan untuk menghindari fragmentasi dengan menggunakan blok besar.
- **Next Fit**: Mirip dengan First Fit, tetapi pencarian dilanjutkan dari posisi terakhir alokasi sebelumnya.

### 6. **Fragmentation Management**

- **Fragmentasi Eksternal**: Memori bebas tersebar dalam blok-blok kecil yang tidak berdekatan, membuatnya sulit untuk mengalokasikan memori besar.
- **Fragmentasi Internal**: Terjadi ketika blok memori yang dialokasikan lebih besar dari yang diperlukan, menyisakan ruang kosong yang tidak terpakai.
- Untuk mengatasi fragmentasi, teknik seperti **Compaction** digunakan untuk menggabungkan ruang memori bebas yang tersebar menjadi satu blok yang lebih besar.

### 7. **Buddy System**

- Algoritma alokasi memori yang membagi memori menjadi blok-blok berukuran pangkat dua. Saat memori diperlukan, blok terbesar yang lebih kecil dari atau sama dengan ukuran yang diminta dipilih. Jika diperlukan, blok tersebut dibagi menjadi dua bagian yang lebih kecil hingga ukuran yang sesuai ditemukan.

### Contoh Kasus
ketika menjalankan software pada os jika membuka banyak aplikasi atau tab browser sekaligus akan menyebabkan penurunan performa, kemudian ketika kita men close nya secara acak kemungkinan memori yang telah teralokasi akan menjadi lubang atau terjadi fragmentasi yang membuat tidak bisa mengembalikan performa seperti awal secara penuh
[Source](https://techcommunity.microsoft.com/t5/ask-the-performance-team/disk-fragmentation-and-system-performance/ba-p/372921)

1. **Linux Kernel Memory Allocation**:
    
    - **Buddy System**: Sistem buddy pada kernel Linux menggunakan variasi dari algoritma first fit untuk mengalokasikan blok memori. Sistem ini membagi memori menjadi blok-blok dengan ukuran yang merupakan pangkat dua, dan mencari blok terkecil yang cukup besar untuk memenuhi permintaan memori [source](https://www.kernel.org/doc/html/latest/core-api/memory-allocation.html)[1](https://www.kernel.org/doc/html/latest/core-api/memory-allocation.html).
    - **Slab Allocator**: Slab allocator menggunakan pendekatan best fit untuk mengalokasikan objek kecil dalam kernel. Ini membantu mengurangi fragmentasi internal dengan mencari cache yang paling sesuai dengan ukuran objek yang diminta [source](https://www.geeksforgeeks.org/operating-system-allocating-kernel-memory-buddy-system-slab-system/)[2](https://www.geeksforgeeks.org/operating-system-allocating-kernel-memory-buddy-system-slab-system/).
2. **Windows Heap Manager**:

    - **Heap Manager**: Pada Windows, heap manager mendukung berbagai strategi alokasi, termasuk first fit dan best fit. Heap manager biasanya memilih blok pertama yang cukup besar untuk memenuhi permintaan alokasi, tetapi dapat beralih ke strategi yang lebih mirip best fit saat memori semakin terfragmentasi [source](https://www.kernel.org/doc/html/v5.4/core-api/memory-allocation.html)
