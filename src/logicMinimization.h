/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : logicMinimization.h
*Deskripsi : file header untuk logicMinimization.c : sourcecode implementasi algoritma quiene mccluskey
*/

// referensi : http://freesourcecode.net/cprojects/102643/sourcecode/McQuicksy.c 

// KAMUS
    // Tipe data Bentukan
        // type vector : < paired : array [0..limit-1] of integer >
        // type Node : < next          : pointer to Node
        //               hasPaired     : integer [0,1]
        //               numberOfOnes  : integer
        //               paired        : vector
        //               group         : integer
        //               binary        : array [0..ukuranBit-1] of integer
        //               numberOfPairs : integer >
        // type implicantsTable : < arr            : matrix [0..limit-1] x [0..ukuranBit-1] of integer
        //                          arr            : matrix [0..limit] x [0..limit-1] of integer
        //                          top            : integer
        //                          mintermCounter : array [0..limit-1] of integer >
    // Konstanta
        // ukuranBit : integer { banyaknya variabel di dalam fungsi logika yang ingin diminimisasi }
        // limit : integer { banyak maksimum minterm - 1 (2^ukuranBit - 1)}
    // Variabel
        // maxGroup, newmaxGroup : integer
            // menyatakan banyaknya minterm paling besar dalam satu grup pada iterasi tertentu dan iterasi selanjutnya
        // head, head2 : pointer to node
        // minterms : array [0..limit-1] of integer
        // dontCares : : array [0..limit-1] of integer
    // Fungsi / Prosedur
        // procedure logicMinimization(input modeInput : character, )
            // Algoritma utama untuk melakukan algoritma
            // I.S modeInput operasi telah terdefinisi
            // F.S dilakukan minimisasi logika dengan mode input operasi tertentu
            // modeInput : m --> user memasukkan input secara manual
            // modeInput : f --> menerima input dari file eksternal
        // function cekDontCare() -> integer
            // memeriksa apakah suatu minterm don't care atau bukan
            // nilai balikan : 0 : bukan don't care ; 1 : don't care
        // procedure add(input n : integer)
            // membuat linked-list untuk menyimpan minterm
            // I.S. nilai minterm yang ingin ditambahkan ke linked list terdefinisi 
            // F.S. sebuah node dibuat dan ditambahkan ke linked-list 
        // function buatNode(n : integer) -> pointer to node
            // membuat node untuk menyimpan data minterm
        // procedure addPair()
            // membuat linked list untuk menyimpan pasangan minterm
            // I.S. dua buah node yang ingin dipasangkan terdefinisi 
            // F.S. sepasang node ditambahkan ke linked list
        // procedure createNodePair(p, q : pointer to node) -> pointer to Node
            // membuat node baru menggunakan Node yang sudah ada
            // I.S. node p dan q terdefinsi
            // F.S. sebuah node r telah dibuat dari node p dan q
        // procedure tampilkanTabel()
            // menampilkan prime implicant table
            // I.S. Tabel bertipe data implicant table telah terisi
            // F.S. elemen pada Tabel ditampilkan dengan notasi minterm
        // procedure binaryFill(input p,q : pointer to node ;  output r : pointer to node)
            // mengisi nilai biner pada r dengan p dan q. Jika kedua bit sama, maka akan dipertahankan. Jika berbeda, akan bernilai -1
            // I.S. p,q, dan r terdefinisi
            // F.S. nilai biner r telah diperbaharui
        // procedure inisiasiTabel()
            // menginisiasi seluruh elemen table menjadi -1
            // I.S. sebuah variabel bertipe data implicantsTable bernama Tabel telah terdefinisi
            // F.S. seluruh elemen Tabel di-inisiasi dengan nilai -1
        // procedure display()
            // menampilkan minterm dan pasangannya dan nilai biner pada setiap pass (L1, L2, L3, dst.)
            // I.S. node-node pada linked list siap untuk dicetak
            // F.S. sebuah baris pada L1, L2, dan L3 telah ditampilkan 
        // procedure pair()
            // melakukan pemasangan node sekaligus mencetaknya dalam tabel L1, L2, dan L3
            // I.S. linked list telah terdefinisi
            // F.S. L1, L2, dan L3 tercetak (setelah pemanggilan rekursif terakhir selesai)
        // procedure tambahKeTabel()
            // membuat tabel untuk mencari minimum cover
            // I.S. prime implicant telah ditemukan
            // F.S. tabel untuk mencari minimum cover telah dibuat
        // function ifPairingPossible(p,q : pointer to node) -> integer
            // memeriksa jika apakah hanya ada perbedaan satu bit antara p dan q (sehingga mungkin dipasangkan)
        // function findMaxInTable(row : pointer to integer)
            // mencari prime implikan yang memiliki minterm paling banyak
            // tidak digunakan pada suatu waktu dan mengembalikan banyak mintermnya
        // procedure analisisTabel()
            // menganalisis tabel minimum cover yang telah dibentuk dan mencetak fungsi logika yang telah diminimisasi ke layar
            // I.S. tabel minimum cover sudah terdefinisi
            // F.S. fungsi logika yang telah diminimisasi  dicetak ke layar
        // procedure hapusMintermDariTabel(input n : integer)
            // menghapus semua minterm pada suatu baris dan kolom implikan
            // I.S. -
            // F.S. seluruh minterm yang dicover prime implicant dihapus dari tabel
        // function banyakImplikan(n : integer, temp : pointer to integer) -> integer
            // mengembalikan berapa banyak implikan yang ada suatu minterm tertentu
        // procedure konversiBinerKeNotasiMinterm(input n : integer)
            // mengonversi dan mencetak biner ke notasi variabel
            // I.S. implicantsTable bernama Tabel telah terdefinisi
            // F.S. isi Tabel dalam bentuk variabel A,B,C,... telah dicetak ke layar
        // procedure validasi_file(char filename[])
            // memvalidasi nama dan format file eksternal
            // I.S. -
            // F.S. nama file ada dan format file benar (.txt)
    
// DEKLARASI KONSTANTA
    // ubah secara manual UkuranBit dan limit = 2^ukuranBit
#define ukuranBit 4
#define limit 16
#define MAX_LEN 127

// DEKLARASI TIPE DATA BENTUKAN
struct vector            // menyimpan list semua minterm yang telah dikelompokkan
{
    int paired[limit];
};

struct Node                  // menyimpan informasi tentang minterm seperti banyak pasangan dan banyak pasangan yang terbentuk
{
    struct Node* next;     // pointer ke node selanjutnya pada linked-list
    int hasPaired;         // kondisi pemasangan
    int numberOfOnes;      // banyaknya '1' pada minterm
    struct vector paired;  // struct vector untuk menyatakan minterm berpasangan lain
    int group;             // menyatakan nomr grup sesuai jumlah angka satu pada minterm
    int binary[ukuranBit]; // menyimpan nilai biner dari minterm
    int numberOfPairs;    // berapa banyak pasangan yang telah terbentuk (contoh: 4 menyatakan 2 double atau 1 quad)
};
typedef struct Node node;

struct implicantsTable // Tabel prime implicant
{
    int arr[limit][ukuranBit]; // array referensi sebelum mencetak fungsi logika yang telah diminimalisasi ke layar
    int brr[limit][limit]; // array untuk mencari minimum cover
    int top; // banyak implikan pada tabel implikan                         
    int mintermCounter[limit]; // banyak minterm pada tabel implikan
} Tabel;

// DEKLARASI PROTOTIPE FUNGSI
    // terkait algoritma minimisasi logika
int logicMinimization(char modeInput, int counter, int SOPorPOS);
void add(int);
node* buatNode(int);
void pair(int* n_iteration);
void display();
void tampilkanTabel(int SOPorPOS);
node* createNodePair(node*,node*);
void binaryFill(node*,node*,node*);
void inisiasiTabel();
int ifPairingPossible(node*,node*);
int cekDontCare(int);
void addPair(node*,node*);
void tambahKeTabel();
void analisisTabel(int SOPorPOS);
void binaryFill(node*,node*,node*);
void konversiBinerKeNotasiMinterm(int);
void konversiBinerKeNotasiMaxterm(int);
int findMaxInTable(int*);
int banyakImplikan(int,int*);
void hapusMintermDariTabel(int);
void hapusMaxtermDariTabel(int n);

    // terkait pemrosesan file
void validasi_file(char filename[]);

// DEKLARASI VARIABEL
node *head,*head2;

int maxGroup,newMaxGroup;   
int minterms[limit];
int maxterms[limit];
int dontCares[limit];