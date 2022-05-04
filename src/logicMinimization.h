/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : logicMinimization.h
*Deskripsi : file header untuk logicMinimization.c : sourcecode implementasi algoritma quiene mccluskey
*/

// KAMUS
    // Tipe data Bentukan
        // type vector : < paired : array [0..limit-1] of integer >
        // type Node : < next          : pointer to Node
        //               hasPaired     : integer
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
            //
            // I.S.
            // F.S. 

// DEKLARASI KONSTANTA
#define ukuranBit 4
#define limit 16

// DEKLARASI TIPE DATA BENTUKAN
struct vector            //stores the list of all minterms grouped
{
    int paired[limit];
};

struct Node                  //node declaration to hold the information about minterms such as number of pairs and number of pairs formed
{
    struct Node* next;    //link to next node in the list
    int hasPaired;            //stores 1 oe 0 to denote the state of pairing
    int numberOfOnes;   //stores the number of ones in the minterm
    struct vector paired; //struct vector to denote other paired minterms
    int group;                  //denote the group according to the number of ones
    int binary[ukuranBit];   //stores the binary of the till then formed paired expression
    int numberOfPairs;    //stores how many paires have been formed 4 denoted 2 paires or 1 quad
};
typedef struct Node node;

struct implicantsTable         //Prime Implicants Table
{
    int arr[limit][ukuranBit];
    int brr[limit][limit];
    int top;                             //denotes how many prime implicants have been added till now
    int mintermCounter[limit];    //stores the number of the minterms in the particular prime implicant
} Table;

// DEKLARASI PROTOTIPE FUNGSI
int logicMinimization(char modeInput);
void add(int);
node* buatNode(int);
void pair();
void display();
void displayTable();
node* createNodePair(node*,node*);
void binaryFill(node*,node*,node*);
void initTable();
int ifPairingPossible(node*,node*);
int cekDontCare(int);
int ifMintermPresentInImplicant(int,int);
void addPair(node*,node*);
void addToTable();
void analyseTable();
void binaryFill(node*,node*,node*);
void convertBinaryToMintermNotation(int);
int findMaxInTable(int*);
void initTable();
int numberOfImplicants(int,int*);
void pair();
void hapusMintermDariTabel(int);


// DEKLARASI VARIABEL
node *head,*head2;

int maxGroup,newMaxGroup;   
int minterms[limit];
int dontCares[limit];