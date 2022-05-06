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
            // I.S. 
            // F.S. 
        // function buatNode(n : integer) -> pointer to node
            // membuat node untuk menyimpan data minterm
        // procedure addPair()
            // membuat linkes list untuk menyimpan pasangan minterm
            // I.S. 
            // F.S. 
        // procedure createNodePair(p, q : pointer to node) -> pointer to Node
            // membuat node baru menggunakan Node yang sudah ada
            // I.S.
            // F.S.
        // procedure tampilkanTabel()
            // menampilkan prime implicant table
            // I.S.
            // F.S.
        // procedure binaryFill(input p,q : pointer to node ;  output r : pointer to node)
            // mengisi nilai biner pada r dengan p dan q. Jika kedua bit sama, maka akan dipertahankan. Jika berbeda, akan bernilai -1
            // I.S.
            // F.S.
        // procedure buatNode(input n : integer)
            //
            // I.S.
            // F.S.
        // procedure inisiasiTabel()
            // menginisiasi seluruh elemen table menjadi -1
            // I.S.
            // F.S.
        // procedure display()
            // menampilkan minterm dan pasangannya dan nilai biner pada setiap pass (L1, L2, L3, dst.)
            // I.S.
            // F.S.
        // procedure pair()
            // melakukan pemasangan node
            // I.S.
            // F.S.
        // procedure tambahKeTabel()
            //
            // I.S.
            // F.S.
        // function ifPairingPossible(p,q : pointer to node) -> integer
            // memeriksa jika apakah hanya ada perbedaan satu bit antara p dan q (sehingga mungkin dipasangkan)
        // function findMaxInTable(row : pointer to integer)
            // mencari prime implikan ang memiliki minterm paling banyak
            // tidak digunakan pada suatu waktu dan mengembalikan banyak mintermnya
        // procedure analisisTabel()
            // 
            // I.S.
            // F.S.
        // procedure hapusMintermDariTabel(input n : integer)
            // menghapus semua minterm pada suatu baris dan kolom implikan
            // I.S.
            // F.S.
        // function banyakImplikan(n : integer, temp : pointer to integer) -> integer
            // mengembalikan berapa banyak implikan yang ada suatu minterm tertentu
        // procedure konversiBinerKeNotasiMinterm(input n : integer)
            // mengonversi dan mencetak biner ke notasi variabel
            // I.S.
            // F.S.
        // procedure validasi_file(char filename[])
            // memvalidasi nama dan format file eksternal
            // I.S. -
            // F.S. nama file ada dan format file benar (.txt)
    
// DEKLARASI KONSTANTA
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
    int group;             // denote the group according to the number of ones
    int binary[ukuranBit]; // menyimpan nilai biner dari minterm
    int numberOfPairs;    // berapa banyak pasangan yang telah terbentuk (contoh: 4 menyatakan 2 double atau 1 quad)
};
typedef struct Node node;

struct implicantsTable // Tabel prime implicant
{
    int arr[limit][ukuranBit];
    int brr[limit][limit];
    int top;                         
    int mintermCounter[limit]; // banyak minterm pada tabel
} Table;

// DEKLARASI PROTOTIPE FUNGSI
    // terkait algoritma minimisasi logika
int logicMinimization(char modeInput, int counter);
void add(int);
node* buatNode(int);
void pair(int* n_iteration);
void display();
void tampilkanTabel();
node* createNodePair(node*,node*);
void binaryFill(node*,node*,node*);
void inisiasiTabel();
int ifPairingPossible(node*,node*);
int cekDontCare(int);
void addPair(node*,node*);
void tambahKeTabel();
void analisisTabel();
void binaryFill(node*,node*,node*);
void konversiBinerKeNotasiMinterm(int);
int findMaxInTable(int*);
void inisiasiTabel();
int banyakImplikan(int,int*);
void hapusMintermDariTabel(int);

    // terkait pemrosesan file
void simpanKeFile(int solusi[], int n, int noFile);
void hapusFile(int nFile);
void validasi_file(char filename[]);

// DEKLARASI VARIABEL
node *head,*head2;

int maxGroup,newMaxGroup;   
int minterms[limit];
int dontCares[limit];