# logicMinimization
Tugas besar mata kuliah `EL2008 : Pemecahan masalah dengan C` terkait minimalisasi logic

#### Anggota Kelompok:
1. Jefferson Grizzlie (13220013)
2. Muhammad Mikhail Ghrilman (13220021)
3. Bostang Palaguna (13220055)
4. Muhammad Daffa Rasyid (13220059)

### Perintah

1. Eksplorasi algoritma minimisasi logic
2. Rancanglah sebuah simulator untuk menggambarkan kerja sistem tersebut
    - Buat deskripsi simulasi. Deskripsikan dengan jelas: input - proses – output 
    - Lengkapi deskripsi di atas dengan algoritma dalam bentuk flowchart untuk setiap fungsi-fungsi dalam sistem
    - Buat Data Flow Diagram (DFD)
3. Berdasarkan rancangan simulasi dan algoritma yang telah dibuat pada tugas sebelumnya, buatlah program dalam bahasa pemrograman C untuk menjalankan simulasi tersebut.


---

## Penjelasan metode Tabular
### Permasalahan
Misalkan kita memilki sebuah fungsi logika untuk di-minimisasi sebagai berikut:

![Fungsi Logika Awal](./dll/img/ex/01_ekspresiLogikaAwal.png)

atau dalam bentuk kanonikal:

![Tabel SOP](./dll/img/ex/02_tabelSOP.png)

![Ekspresi Awal Logika Bentuk Kanonikal](./dll/img/ex/03_ekspresiAwalLogikaBentukKanonikal.png)

> catatan : variabel dengan huruf kecil menunjukkan komplemen dari variabel huruf besar. Sedangkan variabel huruf besar bernilai _logic 1_.

### Solusi

Tahapan metode tabular secara garis besar dibagi menjadi dua, yaitu mencari prime implicant kemudian menemukan minimum cover.

#### Langkah Pertama : Membuat L1 dengan mengurutkan term berdasarkan banyak angka **1**

Kita akan kelompokkan minterm berdasarkan banyaknya angka **1** yang mereka punya dalam representasi binernya. Kita akan bagi menjadi grup yang memiliki satu angka **1**, dua angka **1**, sampai dengan empat angka **1**.

![L1 : grup term berdasarkan banyak angka 1](./dll/img/ex/04_L1.png)

Kita mengelompokkan term berdasarkan banyaknya angka **1** yang mereka punya sehingga ketika mencari pasangan minterm yang hanya berbeda satu term, kita cukup membandingkan minterm-minterm pada grup yang bersebelahan. Misalkan minterm-minterm pada grup dengan banyak angka **1** sebanyak 1 cukup dibandingkan dengan minterm pada grup dengan banyak angka **1** sebanyak 2. Tidak perlu membandingkannya dengan minterm pada grup dengan banyak angka **1** sebanyak tiga ataupun empat. 

#### Langkah kedua : kelompokkan minterm pada L1 yang hanya berbeda satu term

Contoh minterm yang dipasangkan (yang hanya berbeda satu term) adalah minterm ke-3 dan minterm ke-7.

![contoh pasangan minterm](./dll/img/ex/05_ContohPasangan.png)

Dengan menemukan semua pasangan minterm pada L1 (ingat kita hanya membandingkan minterm-minterm pada grup yang bersebelahan saja), kita akan peroleh L2 sebagai berikut:

![L2 : pasangan minterm dari L1](./dll/img/ex/06_L2.png)

> catatan:
 > 1.  \- menandakan don't care
 > 2. minterm yang bisa dipasangkan grup ke-$n$ dan grup ke-$n+1$ pada L1 akan bergabung menjadi pasangan minterm dengan grup ke-$n$ pada L2

perhatikan bahwa semua minterm pada L1 telah ter-_cover_ oleh pasangan minterm pada L2, sehingga kita tidak lagi membutuhkan L1.

#### Langkah ketiga : kelompokkan pasangan minterm pada L2 yang hanya berbeda satu term

Kita lakukan cara yang sama untuk membentuk L3 dari L2 seperti membentuk L2 dari L1. Kita pasangkan 'pasangan minterm' pada L2 yang hanya berbeda satu term. Kita peroleh L3 sebagai berikut:

![L3 : pasangan 'pasangan minterm' dari L2](./dll/img/ex/07_L3.png)

perhatikan bahwa (12,13;14,15) memiliki representasi biner yang sama dengan (12,14;13,15) sehingga kita cukup mengambil salah satu. Misalkan kita ambil (12,13;14,15) sebagai prime implicant.

#### Langkah keempat : Bentuk prime implicant dari L2 dan L3

(12,13,14,15) pada L3 telah men-_cover_ pasangan minterm (12,13), (12,14), (13,15), dan (14,15) pada L2. pasangan minterm yang belum tercover pada L2 adalah (1,3), (3,7), dan (7,15). Maka dari L2 dan L3, kita punya prime implicant P1, P2, P3, dan P4 sebagai berikut:

![prime implicant](./dll/img/ex/08_primeImplicant.png)

#### Langkah kelima : Cari minium cover dari prime implicant yang telah dibentuk

Kita buat sebuah tabel dengan baris (vertikal) berisi prime implicant P1 sampai dengan P4 lalu kolom (horizontal) berisi minterm ke-1 sampai dengan minterm ke 15 (sesuai fungsi logika).

![tabel minimum cover tahap 1](./dll/img/ex/09_MencariMinimumCover1.png)

sekarang kita harus memilih prime implicant se-sedikit mungkin sehingga semua minterm tercover. Perhatikan bahwa agar m1 tercover, mau tidak mau P1 harus dipilih. Selanjutnya, semua yang tercover oleh P1 bisa kita hiraukan.

![tabel minimum cover tahap 2](./dll/img/ex/10_MencariMinimumCover2.png)

selanjutnya, agar m12 dan m13 tercover, kita harus memilih P4. Maka kita peroleh tabel minimum cover yang lebih sederhana sebagai berikut:
![tabel minimum cover tahap 3](./dll/img/ex/11_MencariMinimumCover3.png)

terakhir, untuk men-_cover_ m7, kita bisa bebas memilih P2 ataupun P3. Kedua pilihan sama baiknya. Misalkan untuk sekarang kita pilih P2. Maka semua minterm telah tercover dan kita peroleh fungsi logika yang telah di-minimisasi sebagai berikut:

![tabel minimum cover tahap 4](./dll/img/ex/12_MencariMinimumCover4.png)

![Ekspresi logika setelah minimisasi](./dll/img/ex/13_ekspresiLogikaSetelahMinimisasi.png)

---

### don't care

> sekarang bagaimana jika terdapat `don't care`?

don't care adalah term yang boleh di-cover ataupun tidak. Ia membantu kita dalam memberikan ekspresi logika hasil minimisasi yang lebih sederhana.

Sebagai contoh permasalahan, misalkan kita diminta untuk meminimisasi fungsi logika:

![masalah minimisasi dengan don't care](./dll/img/ex/14_ekspresiLogikaAwalDenganDontCare.png)

sama seperti sebelumnya, kita bentuk L1, L2, dan L3 dengan cara yang sama.

![L1 contoh masalah dengan don't care](./dll/img/ex/15_L1.png)
![L2 contoh masalah dengan don't care](./dll/img/ex/16_L2.png)
![L3 contoh masalah dengan don't care](./dll/img/ex/17_L3.png)

semua minterm pada L1 telah ter-cover oleh pasangan minterm pada L2 sehingga L1 tidak akan kita gunakan. Pasangan 'pasangan minterm' pada L3 (5,7,13,15) telah mencover pasangan minterm (5,7), (5,13), (7,15), dan (13,15) pada L2. Sedangkan yang belum tercover adalah pasangan minterm (11,15) dan (14,15).

Maka kita punya prime implicant : P1 (11,15), P2 (14,15), dan P3 (5,7,13,15).

Sekarang yang membedakan `don't care` dengan minterm biasa adalah pada saat pencarian minimum cover, `don't care` tidak perlu masuk sebagai kolom (horizontal). Berikut adalah tabel minimum covernya:

![mencari minimum cover tahap 1](./dll/img/ex/18_mencariMinimumCover1.png)

P3 harus dipilih agar m7 dan m13 tercover.

![mencari minimum cover tahap 2](./dll/img/ex/19_mencariMinimumCover2.png)

selanjutnya agar m14 tercover, kita pilih P2. Maka kita peroleh fungsi logika yang telah diminimisasi:

![mencari minimum cover tahap 3](./dll/img/ex/20_mencariMinimumCover3.png)

![Ekspresi logika setelah minimisasi](./dll/img/ex/21_ekspresiLogikaSetelahMinimisasi.png)