/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : interface.h
*Deskripsi :  file header untuk interface.c
*/

// KAMUS
    // Prosedur/Fungsi
        // procedure help()
            // menampilkan opsi aks kepada user
            // I.S -
            // F.S pilihan opsi ditampilkan ke layar
        // procedure cetakBumperOpening()
            // menampilkan ASCII art 'Logic minimization' ke layar
            // I.S array of string bumper_opening terdefinisi
            // F.S ASCII art selamat datang ditampilkan ke layar
        // procedure cetakBumperClosing()
            // menampilkan ASCII art 'terimakasih' ke layar
            // I.S array of string bumper_closing terdefinisi
            // F.S ASCII art penutup ditampilkan ke layar
        // procedure cetakPengarang()
            // menampilkan daftar anggota kelompok ke layar
            // I.S array of string pengarang terdefinisi
            // F.S daftar pengarang program tercetak ke layar
        // procedure cetakKredit()
            // menampilkan daftar referensi ke layar
            // I.S array of string referensi terdefinisi
            // F.S daftar referensi program tercetak ke layar
        // procedure opening()
            // rutin pembuka program
            // I.S -
            // F.S bumper opening, pengarang, dan pilihan opsi ditampilkan ke layar
        // procedure closing()
            // rutin penutup program
            // I.S -
            // F.S bumper closing, kredit ditampilkan ke layar  
        
// ALGORITMA

// DEKLARASI KONSTANTA
#define n_referensi 2
#define n_pengarang 4
#define n_baris_bumper_opening 8
#define n_baris_bumper_closing 8

// DEKLARASI PROTOTIPE FUNGSI
    // terkait antar-muka
void help();
void cetakBumperOpening();
void cetakBumperClosing();
void cetakPengarang();
void cetakKredit();
void opening();
void closing();
