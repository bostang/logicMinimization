/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : main.c
*Deskripsi : main program/driver code dari program yang melakukan minimisasi logika dengan metode tabular
*/

// Program main
    // main program untuk program minimisasi logika
// KAMUS
    // Variabel
        // aksi : character
        // isProgramFinished : boolean
        // modeInput : character

// ALGORITMA UTAMA


#include <stdio.h>

#include "logicMinimization.h"
#include "interface.h"

int main(void)
{   
    char aksi;
    int isProgramFinished = 0;
    char modeInput;

    opening();
    while (!isProgramFinished)
    {
        printf("Masukkan Aksi:\n>>> ");
        scanf("%c",&aksi);
        fflush(stdin); // untuk membersihkan buffer input

        if (aksi == 'L')
        {
                // menerima masukan mode input sekaligus validasi
            printf("Masukkan mode input:\t\t(m : manual, f : file)\n>>> ");
            scanf("%c",&modeInput);
            fflush(stdin);
            if (modeInput == 'm' || modeInput == 'f')
            {
                logicMinimization(modeInput);
            }
            else
            {
                printf("mode input tidak valid!\n");
            }

        }
        else if (aksi == 'q')
        {
            closing();
            isProgramFinished = 1;
        }
        else if (aksi == 'h')
        {
            help();
        }
        else
        {
            printf("Aksi tidak valid!\n");
        }
        fflush(stdin);
    }

    return 0;
}
