/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : interface.h
*Deskripsi :  sourcecode bagian periferal program-user (interface) seperti pesan selamat datang
*/

// KAMUS
    // Prosedur/Fungsi
        // procedure help()
            // menampilkan opsi 
// ALGORITMA

// DEKLARASI KONSTANTA
#define n_referensi 2
#define n_pengarang 4
#define n_baris_bumper_opening 8
#define n_baris_bumper_closing 8

// DEKLARASI VARIABEL
void help()
{
    // ALGORITMA
    printf("--- Opsi Aksi ---\n");
    printf("L : Melakukan minimisasi logika (algoritma utama)\n");
    printf("d : menghapus file input ataupun file output\n");
    printf("q : keluar dari program\n");
    printf("h : bantuan\n");
    printf("\n");
}

char pengarang[n_pengarang][63]=
{
    "Jefferson Grizzlie (13220013)",
    "Muhammad Mikhail Ghrilman (13220021)",
    "Bostang Palaguna (13220055)",
    "Muhammad Daffa Rasyid (13220059)"
};

char referensi[n_referensi][127]=
{
    "http://freesourcecode.net/cprojects/102643/sourcecode/McQuicksy.c",
    "http://www.patorjk.com/software/taag/"
};

char bumper_closing[n_baris_bumper_closing][99] = 
{
    "  _            _                   _             _ _             __  ",
    " | |          (_)                 | |           (_) |         _  \\ \\ ",
    " | |_ ___ _ __ _ _ __ ___   __ _  | | ____ _ ___ _| |__      (_)  | |",
    " | __/ _ \\ '__| | '_ ` _ \\ / _` | | |/ / _` / __| | '_ \\          | |",
    " | ||  __/ |  | | | | | | | (_| | |   < (_| \\__ \\ | | | |     _   | |",
    "  \\__\\___|_|  |_|_| |_| |_|\\__,_| |_|\\_\\__,_|___/_|_| |_|    (_)  | |",
    "                                                                 /_/ "
};

char bumper_opening[n_baris_bumper_opening][99]=
{
    "  _             _        __  __ _       _           _          _   _             ",
    " | |           (_)      |  \\/  (_)     (_)         (_)        | | (_)            ",
    " | | ___   __ _ _  ___  | \\  / |_ _ __  _ _ __ ___  _ ______ _| |_ _  ___  _ __  ",
    " | |/ _ \\ / _` | |/ __| | |\\/| | | '_ \\| | '_ ` _ \\| |_  / _` | __| |/ _ \\| '_ \\ ",
    " | | (_) | (_| | | (__  | |  | | | | | | | | | | | | |/ / (_| | |_| | (_) | | | |",
    " |_|\\___/ \\__, |_|\\___| |_|  |_|_|_| |_|_|_| |_| |_|_/___\\__,_|\\__|_|\\___/|_| |_|",
    "           __/ |                                                                 ",
    "          |___/                                                                  "
};

// REALISASIPROSEDUR /FUNGSI
void cetakBumperOpening()
{
    // ALGORITMA
    printf("Selamat datang di program:\n");
    for (int k=0;k<n_baris_bumper_opening;k++)
    {
        printf("%s\n",bumper_opening[k]);
    }
}

void cetakBumperClosing()
{
    // ALGORITMA
    for (int k=0;k<n_baris_bumper_closing;k++)
    {
        printf("%s\n",bumper_closing[k]);
    }
}

void cetakPengarang()
{
    // ALGORITMA
    printf("oleh:\n");
    for (int k=0;k<n_pengarang;k++)
    {
        printf("%d. %s\n",k+1,pengarang[k]);
    }
}

void cetakKredit()
{
    // ALGORITMA
    printf("credit to:\n");
    for (int k=0;k<n_referensi;k++)
    {
        printf("%d. %s\n",k+1,referensi[k]);
    }
    printf("\n");
    
}

void opening()
{
    // ALGORITMA
    cetakBumperOpening();
    
    cetakPengarang();
    printf("\n");
    help();
}

void closing()
{
    // ALGORITMA
    cetakBumperClosing();

    cetakKredit();
}
