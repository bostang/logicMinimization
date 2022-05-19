/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Rabu, 27 April 2022
*Nama File : logicMinimization.c
*Deskripsi : sourcecode implementasi algoritma quiene mccluskey
*/

// referensi : http://freesourcecode.net/cprojects/102643/sourcecode/McQuicksy.c 

// include library yang dibutuhkan
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

#include "logicMinimization.h"
#include "interface.h"

// REALISASI FUNGSI/PROSEDUR
    // Fungsi/Prosedur terkait pemrosesan file

void validasi_file(char filename[])
{
    // KAMUS LOKAL
        // Variabel
            // temp : pointer to character { untuk memecah string menjadi tokennya menggunakan strtok }
            // temp2 : array [0..14] of character { untuk menyimpan direktori relatif file input }
    // ALGORITMA
    char *temp;

    temp = strtok(filename,".");
    temp = strtok(NULL,"\n"); //mengambil string setelah titik

    // Jika format file salah 
    if (temp == NULL || strcmp(temp,"txt"))
    {
        printf("Error: format salah!\n");
        closing();
        exit(1); 
    }

    char temp2[15];

    // Mengubah nama file menjadi directory
    strcpy(temp2,filename);
    strcpy(filename,"");
    strcat(filename,"./input/");
    strcat(filename,temp2);
    strcat(filename,".txt");

    // Jika file tidak ada
    if (fopen(filename,"r")==NULL)
    {
        printf("Error: file tidak ada!\n");
        closing();
        exit(1);
    }
}

    // Fungsi/Prosedur terkait algoritma minimisasi logika
int logicMinimization(char modeInput, int counter, int SOPorPOS)
{
    // KAMUS LOKAL
        // Variabel
            // i : integer
            // temp : integer
            // KondisidontCare : boolean { kondisi yang menyatakan bahwa terdapat don't care}
            // banyakDontCare : integer
            // banyakMinterm : integer
            // filename : string { nama file input }
            // temp  : integer
            // fp : pointer to FILE
            // namaFile : string
            // n_interation : integer { pencacah berapa banyak iterasi yang sudah terjadi }
    // ALGORITMA
    int n_iteration = 1;
    int i,temp,kondisiDontCare=0,banyakDontCare, banyakMinterm, banyakMaxTerm;
    char line[MAX_LEN];
    char* token;
    
        // inisiasi variabel global
    maxGroup=-1;
    newMaxGroup=-1;
    for(i=0; i<limit; i++)
        minterms[i]=-1;
    for(i=0; i<limit; i++)
        dontCares[i]=-1;

    if (SOPorPOS == 0)
    {
        if (modeInput == 'm')
        {
            printf("Masukkan banyaknya minterm:\n>>> ");
            scanf("%d",&banyakMinterm);

            if(banyakMinterm==0)
                return 1;
            
            for(i=0; i<banyakMinterm; i++)
            {
                printf("Masukkan minterm ke-%d:\n>>> ",i+1);
                scanf("%d",&temp);
                minterms[temp]=1;
                add(temp);
            }
            printf("Apakah ada don't care? (1/0)\n>>> ");
            scanf("%d",&kondisiDontCare);
            if(kondisiDontCare==1)
            {
                printf("Masukkan banyaknya don't care:\n>>> ");
                scanf("%d",&banyakDontCare);
                for(i=0; i<banyakDontCare; i++)
                {
                    printf("Masukkan don't care ke-%d:\n>>> ",i+1);
                    scanf("%d",&temp);
                    dontCares[temp]=1;
                    add(temp);
                }
            }
        }

        else if (modeInput == 'f')
        {
            // menerima input file eksternal dan validasi
            char filename[MAX_LEN];
            printf("Masukkan nama File eksternal:\n>>> ");
            scanf("%s", &filename);

            validasi_file(filename);
            // membaca isi file eksternal (setelah divalidasi)
                
            FILE* fp = fopen(filename, "r");

            // Cek file sampai akhir
            fseek(fp, 0, SEEK_END);
            // Jika file kosong
            if (ftell(fp)==0)
            {
                printf("Error: file kosong!\n");
                exit(1);
            }

            fseek(fp, 0, SEEK_SET); // Kembali ke awal

            // Baca baris pertama : banyak minterm
            fgets(line, MAX_LEN, fp);
            token = strtok(line, "\n");
            banyakMinterm = atoi(token);

            if(banyakMinterm==0)
                return 1;

            // Baca baris kedua : daftar minterm
            
            // Menyimpan data dari file ke dalam graph
            fgets(line, MAX_LEN, fp);
            token = strtok(line, ",");
            minterms[atoi(token)]=1;
            add(atoi(token));
            
            for (int i=1;i<(banyakMinterm-1);i++)
            {
                token = strtok(NULL, ",");
                minterms[atoi(token)]=1;
                add(atoi(token));
            }
            token = strtok(NULL, "\n"); // membaca elemen terakhir pada baris kedua
            minterms[atoi(token)]=1;
            add(atoi(token));

            // Baca baris ketiga : apakah ada don't care/tidak
            fgets(line, MAX_LEN, fp);
            token = strtok(line, "\n");
            kondisiDontCare = atoi(token);

            if(kondisiDontCare==1)
            {
                // Baca baris keempat : banyak don't care
                fgets(line, MAX_LEN, fp);
                token = strtok(line, "\n");
                banyakDontCare = atoi(token);
            
                // Baca baris kelima : daftar don't care
                fgets(line, MAX_LEN, fp);
                token = strtok(line, ",");
                dontCares[atoi(token)]=1;
                add(atoi(token));
                
                for(i=1; i<(banyakDontCare-1); i++)
                {
                    token = strtok(NULL, ",");
                    dontCares[atoi(token)]=1;
                    add(atoi(token));
                }
                token = strtok(NULL, "\n");
                dontCares[atoi(token)]=1;
                add(atoi(token));
            }
            
            fclose(fp);
        }

        else
        {
            return 0;
        }

        Tabel.top=0;
        inisiasiTabel();    // inisiasi tabel prime implicant dengan semua sel bernilai -1 (kosong)
        pair(&n_iteration);           // melakukan pemasangan minterm (pengisian tabel prime implicant)
        tampilkanTabel(0); // mencetak tabel prime implicant
        printf("Fungsi Logika setelah minimisasi:\n\t");
        analisisTabel(0);  // menganalisis tabel dan mencetak hasil
            
                // head dan head2 harus kembali di-NULL kan agar hasil benar pada iterasi berikutnya
        head = NULL;
        head2 = NULL;
        printf("\n");
        
        return 0;
    }
    else if(SOPorPOS == 1)
    {
        if (modeInput == 'm')
        {
            printf("Masukkan banyaknya maxterm:\n>>> ");
            scanf("%d",&banyakMaxTerm);

            if(banyakMaxTerm==0)
                return 1;
            
            for(i=0; i<banyakMaxTerm; i++)
            {
                printf("Masukkan maxterm ke-%d:\n>>> ",i+1);
                scanf("%d",&temp);
                maxterms[temp]=1;
                add(temp);
            }
            printf("Apakah ada don't care? (1/0)\n>>> ");
            scanf("%d",&kondisiDontCare);
            if(kondisiDontCare==1)
            {
                printf("Masukkan banyaknya don't care:\n>>> ");
                scanf("%d",&banyakDontCare);
                for(i=0; i<banyakDontCare; i++)
                {
                    printf("Masukkan don't care ke-%d:\n>>> ",i+1);
                    scanf("%d",&temp);
                    dontCares[temp]=1;
                    add(temp);
                }
            }
        }

        else if (modeInput == 'f')
        {
            // menerima input file eksternal dan validasi
            char filename[MAX_LEN];
            printf("Masukkan nama File eksternal:\n>>> ");
            scanf("%s", &filename);

            validasi_file(filename);
            // membaca isi file eksternal (setelah divalidasi)
                
            FILE* fp = fopen(filename, "r");

            // Cek file sampai akhir
            fseek(fp, 0, SEEK_END);
            // Jika file kosong
            if (ftell(fp)==0)
            {
                printf("Error: file kosong!\n");
                exit(1);
            }

            fseek(fp, 0, SEEK_SET); // Kembali ke awal

            // Baca baris pertama : banyak maxterm
            fgets(line, MAX_LEN, fp);
            token = strtok(line, "\n");
            banyakMaxTerm = atoi(token);

            if(banyakMaxTerm==0)
                return 1;

            // Baca baris kedua : daftar maxterm
            
            // Menyimpan data dari file ke dalam graph
            fgets(line, MAX_LEN, fp);
            token = strtok(line, ",");
            maxterms[atoi(token)]=1;
            add(atoi(token));
            
            for (int i=1;i<(banyakMaxTerm-1);i++)
            {
                token = strtok(NULL, ",");
                maxterms[atoi(token)]=1;
                add(atoi(token));
            }
            token = strtok(NULL, "\n"); // membaca elemen terakhir pada baris kedua
            maxterms[atoi(token)]=1;
            add(atoi(token));

            // Baca baris ketiga : apakah ada don't care/tidak
            fgets(line, MAX_LEN, fp);
            token = strtok(line, "\n");
            kondisiDontCare = atoi(token);

            if(kondisiDontCare==1)
            {
                // Baca baris keempat : banyak don't care
                fgets(line, MAX_LEN, fp);
                token = strtok(line, "\n");
                banyakMaxTerm = atoi(token);
            
                // Baca baris kelima : daftar don't care
                fgets(line, MAX_LEN, fp);
                token = strtok(line, ",");
                dontCares[atoi(token)]=1;
                add(atoi(token));
                
                for(i=1; i<(banyakDontCare-1); i++)
                {
                    token = strtok(NULL, ",");
                    dontCares[atoi(token)]=1;
                    add(atoi(token));
                }
                token = strtok(NULL, "\n");
                dontCares[atoi(token)]=1;
                add(atoi(token));
            }
            
            fclose(fp);
        }

        else
        {
            return 0;
        }

        Tabel.top=0;
        inisiasiTabel();    // inisiasi tabel prime implicant dengan semua sel bernilai -1 (kosong)
        pair(&n_iteration);           // melakukan pemasangan minterm (pengisian tabel prime implicant)
        tampilkanTabel(1); // mencetak tabel prime implicant
        printf("Fungsi Logika setelah minimisasi:\n\t");
        analisisTabel(1);  // menganalisis tabel dan mencetak hasil
            
                // head dan head2 harus kembali di-NULL kan agar hasil benar pada iterasi berikutnya
        head = NULL;
        head2 = NULL;
        printf("\n");
        
        return 0;
    }
  
}

int cekDontCare(int i)
{
    // ALGORITMA
    if(dontCares[i]==1)
        return 1;
    else
        return 0;
}

void add(int n)
{
    // KAMUS LOKAL
        // Variabel
            // p, q, temp : pointer to node
    // ALGORITMA
    node *p,*q,*temp;
    p=buatNode(n);
    if(p!=NULL)
    {
			// jika p adalah node pertama
        if(head==NULL)
        {
            head=p;
            head->next=NULL;
            return;
        }
        else
        {
            q=head;
            if(p->group<head->group)
            {
                p->next=head;
                head=p;
                return;
            }
            while(q->next!=NULL&&((q->next->group)<=(p->group)))
            {
                q=q->next;
            }
            if(q->next==NULL)
            {
                q->next=p;
                p->next=NULL;
            }
            else
            {
                temp=q->next;
                q->next=p;
                p->next=temp;
            }
        }
    }
}

void addPair(node *p,node *q)
{
    // KAMUS LOKAL
        // Variabel
            // r, temp : pointer to node
    // ALGORITMA
    node *r,*temp;
    r=createNodePair(p,q);
    if(head2==NULL)
    {
        head2=r;
    }
    else
    {
        temp=head2;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=r;
    }
}

node* createNodePair(node *p,node *q)
{
    // KAMUS LOKAL
        // Variabel 
            // i,j : integer
            // r : pointer to node
    // ALGORITMA
    int i,j;
    node *r;
    r=(node *)malloc(sizeof(node));
    if(r==NULL)
        printf("node gagal dibuat\n");
    else
    {
        for(i=0; i<p->numberOfPairs; i++)
        {
            r->paired.paired[i]=p->paired.paired[i];
        }
        r->numberOfPairs=p->numberOfPairs*2;
        for(j=0; j<q->numberOfPairs; j++)
        {
            r->paired.paired[i++]=q->paired.paired[j];
        }
        r->hasPaired=0;
        r->next=NULL;
        r->group=p->group;
        binaryFill(p,q,r);
    }
    return r;
}

void tampilkanTabel(int SOPorPOS)
{
    // KAMUS LOKAL
        // Variabel
            // i, j : integer
    // ALGORITMA
    int i,j;
    if (SOPorPOS == 0)
    {
        printf("Tabel Prime Implicant:\n");
        for(i=0; i<Tabel.top; i++)
        {
            konversiBinerKeNotasiMinterm(i);
            for(j=0; j<=limit-1; j++)
            {
                if(Tabel.brr[i][j]==1)
                    printf("   %d  ",j);
            }
            printf("\n");
        }
    }
    else if(SOPorPOS == 1)
    {
        printf("Tabel Prime Implicant:\n");
        for(i=0; i<Tabel.top; i++)
        {
            konversiBinerKeNotasiMaxterm(i);
            for(j=0; j<=limit-1; j++)
            {
                if(Tabel.brr[i][j]==1)
                    printf("   %d  ",j);
            }
            printf("\n");
        }
    }
}

void binaryFill(node *p,node *q,node *r)
{
    // KAMUS LOKAL
        // Variabel
            // c : integer
    // ALGORITMA
    int c=ukuranBit-1;
    while(c!=-1)
    {
        if(p->binary[c]==q->binary[c])
        {
            r->binary[c]=p->binary[c];
        }
        else
        {
            r->binary[c]=-1;
        }
        c--;
    }
}

node* buatNode(int n)
{
    // KAMUS LOKAL
        // Variabel

            // c : integer
            // p : pointer to node
    // ALGORITMA
    int c=ukuranBit-1;
    node *p;
    p=(node *)malloc(sizeof(node));
    if(p==NULL)
        printf("Node gagal dibuat\n");
    else
    {
        p->numberOfOnes=0;
        p->paired.paired[0]=n;
        p->numberOfPairs=1;
        while(n!=0)
        {
            p->binary[c]=n%2;
            if(p->binary[c]==1)
                p->numberOfOnes++;
            c--;
            n=n/2;
        }
        while(c!=-1)
        {
            p->binary[c]=0;
            c--;
        }
        p->hasPaired=0;
    }
    p->group=p->numberOfOnes;
    if(p->group>maxGroup)
        maxGroup=p->group;
    return p;
}

void inisiasiTabel()
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
    // ALGORITMA
    int i,j;
    for(j=0; j<=limit-1; j++)
        for(i=0; i<=limit-1; i++)
        {
            Tabel.brr[j][i]=-1;
        }
}

void display()
{
    // KAMUS LOKAL
        // Variabel
            // c : integer
            // count : integer
            // j : integer
    // ALGORITMA
    int c=1,count=0,j=0;
    node *p;
    p=head;
    while(p!=NULL)
    {
        j=0;
        while(count<(p->numberOfPairs))
        {
            printf("%d,",p->paired.paired[count]); // menampilkan pasangan minterm
            count++;
        }
        printf("\b");
        count=0;
        printf("   ");
        while(j<ukuranBit) // menampikan representasi biner dari pasangan minterm
        {
            if(p->binary[j]==-1) // dont care
                printf("%c",'-');
            else
                printf("%d",p->binary[j]);
            j++;
        }
        printf("\n");
        c++;
        p=p->next;
    }
}

void pair(int* n_iteration)
{
    node *p,*q;
    int oneMatched=0;
    p=head;
    q=p;
    printf("Iterasi ke-%d:\n",*n_iteration);
    display();
    newMaxGroup=-1;
		// mencari minterm yang bisa dipasangkan
    while(p->group!=maxGroup)
    {
        q=q->next;
        while(q!=NULL&&(q->group==p->group))
        {
            q=q->next;
        }
        if(q==NULL)
        {
            p=p->next;
            q=p;
            continue;
        }
        else
        {
            if(q->group!=(p->group+1))
            {
                p=p->next;
                q=p;
                continue;
            }
            if(ifPairingPossible(p,q)) // jika p dan q mungkin dipasangkan, maka akan ditambahkan ke linked list
            {
                oneMatched=1;
                p->hasPaired=1;
                q->hasPaired=1;
                addPair(p,q);
                if((p->group)>newMaxGroup)
                    newMaxGroup=p->group;
            }
        }
    }

    tambahKeTabel();
    if(oneMatched) // memeriksa jika setidaknya ada satu pair yang telah  dibentuk
    {
        head=head2;
        head2=NULL;
        maxGroup=newMaxGroup;
        *n_iteration = (*n_iteration) + 1;
        pair(n_iteration);
    }
}

void tambahKeTabel()
{
    // KAMUS LOKAL
        // Variabel
            // i, j, k : integer
            // allMatched : integer
            // p : pointer to node
    // ALGORITMA
    int i,j,k,allMatched;
    node *p;
    p=head;
    while(p!=NULL)
    {
        if(!(p->hasPaired))
        {
            if(Tabel.top!=0) // memeriksa apakah ada duplikat
            {
                for(j=0; j<Tabel.top; j++)
                {
                    allMatched=1;
                    for(k=0; k<p->numberOfPairs; k++)
                    {
                        if(Tabel.brr[j][p->paired.paired[k]]==1)
                            continue;
                        else
                        {
                            allMatched=0;
                            break;
                        }
                    }
                    if(allMatched==1)
                    {
                        break;
                    }
                }
                if(allMatched==1)
                {
                    p=p->next;
                    continue;
                }
            }
            i=ukuranBit-1;
            while(i!=-1)
            {
                Tabel.arr[Tabel.top][i]=p->binary[i];
                i--;
            }
            for(i=0; i<p->numberOfPairs; i++)
            {
                if(cekDontCare(p->paired.paired[i])==1)      //jika minterm ada di array don't care, maka jangan tambahkan ke tabel
                {
                    Tabel.brr[Tabel.top][p->paired.paired[i]]=-1;
                    continue;
                }
                Tabel.mintermCounter[Tabel.top]++;
                Tabel.brr[Tabel.top][p->paired.paired[i]]=1;
            }
            Tabel.top++;
        }
        p=p->next;
    }
}

int findMaxInTable(int *row)
{
    // KAMUS LOKAL
        // Variabel
            // i : integer
            // greatest : integer
    // ALGORITMA
    int i,greatest=-1;
    for(i=0; i<Tabel.top; i++)
    {
        if(Tabel.mintermCounter[i]>greatest)
        {
            *row=i;
            greatest=Tabel.mintermCounter[i];
        }
    }
    return greatest;
}

void analisisTabel(int SOPorPOS)
{
    // KAMUS LOKAL
        // Variabel
            // i,j,k : integer
            // greatestRow : integer
            // ifFirst : integer
            // essentialPrimeImplicant : array [0..limit-1] of integer
            // temp : integer
            // c : integer
    // ALGORITMA
    int i,j,k,greatestRow,ifFirst=1;
    int essentialPrimeImplicant[limit]; // menyimpan nomor baris dari semua essential prime implikan ke dalam sebuah array of integer
    int temp,c;

    if (SOPorPOS == 0)
    {
        for(i=0; i<=limit-1; i++)
            essentialPrimeImplicant[i]=-1;
        for(i=0; i<=limit-1; i++)
        {
            if(minterms[i]==1)
            {
                if(banyakImplikan(i,&temp)==1)
                {
                    essentialPrimeImplicant[i]=temp;
                }
            }
        }

        for(i=0; i<=limit-1; i++)
        {
            if(essentialPrimeImplicant[i]!=-1)
            {
                if(ifFirst!=1)
                    printf(" + ");
                else
                    ifFirst=0;
                konversiBinerKeNotasiMinterm(essentialPrimeImplicant[i]);

                hapusMintermDariTabel(essentialPrimeImplicant[i]);
                for(j=i+1; j<=limit-1; j++)
                {
                    if(essentialPrimeImplicant[j]==essentialPrimeImplicant[i])
                        essentialPrimeImplicant[j]=-1;
                }
                essentialPrimeImplicant[i]=-1;

            }
        }

        while(findMaxInTable(&greatestRow)!=0)
        {
            if(ifFirst!=1)
                printf(" + ");
            else
                ifFirst=0;
            konversiBinerKeNotasiMinterm(greatestRow);

            hapusMintermDariTabel(greatestRow);
        }
        printf("\b");     
    }
    else if (SOPorPOS == 1)
    {
        for(i=0; i<=limit-1; i++)
            essentialPrimeImplicant[i]=-1;
        for(i=0; i<=limit-1; i++)
        {
            // ???
            if(maxterms[i]!=1)
            {
                if(banyakImplikan(i,&temp)==1)
                {
                    essentialPrimeImplicant[i]=temp;
                }
            }
        }

        for(i=0; i<=limit-1; i++)
        {
            if(essentialPrimeImplicant[i]!=-1)
            {
                if(ifFirst!=1)
                    printf(" . ");
                else
                    ifFirst=0;
                konversiBinerKeNotasiMaxterm(essentialPrimeImplicant[i]);
                hapusMaxtermDariTabel(essentialPrimeImplicant[i]);
                for(j=i+1; j<=limit-1; j++)
                {
                    if(essentialPrimeImplicant[j]==essentialPrimeImplicant[i])
                        essentialPrimeImplicant[j]=-1;
                }
                essentialPrimeImplicant[i]=-1;

            }
        }

        while(findMaxInTable(&greatestRow)!=0)
        {
            if(ifFirst!=1)
                printf(" . ");
            else
                ifFirst=0;
            konversiBinerKeNotasiMaxterm(greatestRow);
            hapusMaxtermDariTabel(greatestRow);
        }
        printf("\b");    
    }
   
}

void hapusMintermDariTabel(int n) 
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
    // ALGORITMA
    int i,j;
    for(i=0; i<=limit-1; i++)
    {
        if(Tabel.brr[n][i]==1)
        {
            minterms[i]=-1;

            for(j=0; j<Tabel.top; j++)
            {
                if(Tabel.brr[j][i]==1)
                {
                    Tabel.brr[j][i]=-1;
                    Tabel.mintermCounter[j]--;
                }
            }
        }
    }
}

void hapusMaxtermDariTabel(int n) 
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
    // ALGORITMA
    int i,j;
    for(i=0; i<=limit-1; i++)
    {
        if(Tabel.brr[n][i]==1)
        {
            maxterms[i]=-1;

            for(j=0; j<Tabel.top; j++)
            {
                if(Tabel.brr[j][i]==1)
                {
                    Tabel.brr[j][i]=-1;
                    Tabel.mintermCounter[j]--;
                }
            }
        }
    }
}

int banyakImplikan(int n,int *temp)
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
            // count : integer
    // ALGORITMA
    int i,j;
    int count=0;
    for(i=0; i<Tabel.top; i++)
    {
        if(Tabel.brr[i][n]==1)
        {
            j=i;
            count++;
        }
    }
    *temp=j;
    return count;
}

void konversiBinerKeNotasiMinterm(int n)
{
   // KAMUS LOKAL
        // Variabel
            // c : integer
            // characterNormal : array [0..7] of character
            // characterComplement : array [0..7] of character
    // ALGORITMA 
    int c=0;
    
    // untuk sekarang kita batasi jumlah variabel maksimum sebanyak 8
    // kalau ingin menaikan jumlah variabel, ubah konten array dan naikkan ukuran Bit
    char charactersNormal[]= {'A','B','C','D','E','F','G','H'};
    char charactersComplement[]= {'a','b','c','d','e','f','g','h'};
    while(c!=ukuranBit)
    {
        if(Tabel.arr[n][c]!=-1)
        {
            if(Tabel.arr[n][c]==1)       
                printf("%c",charactersNormal[c]);

            else
                printf("%c",charactersComplement[c]);
        }
        c++;
    }
}

void konversiBinerKeNotasiMaxterm(int n)
{
   // KAMUS LOKAL
        // Variabel
            // c : integer
            // characterNormal : array [0..7] of character
            // characterComplement : array [0..7] of character
            // jmlPlus : jumlah tanda plus yang dibutuhkan untuk mencetak ekspresi POS
    // ALGORITMA 
    int c=0;
    int i=0;
    int jmlPlus=0;

    // mencari banyaknya jumlah tanda plus yang dibutuhkan
    while(i<=ukuranBit)
    {
        if(Tabel.arr[n][i]!=-1)
        {
            jmlPlus++;
        }
        i++;
    }

    // pada POS, huruf kecil menyatakan 1 dan huruf besar menyatakan 0 (kebalikan dari SOP)
    char charactersNormal[]= {'a','b','c','d','e','f','g','h'};
    char charactersComplement[]= {'A','B','C','D','E','F','G','H'};
    printf("(");
    while(c!=ukuranBit)
    {
        if(Tabel.arr[n][c]!=-1)
        {
            if(Tabel.arr[n][c]==1)       
                printf("%c",charactersNormal[c]);

            else
                printf("%c",charactersComplement[c]);
            
            if(c<jmlPlus)
                printf("+");
        }
        c++;
    }
    printf(")");
}

int ifPairingPossible(node *a,node *b)
{
    // KAMUS LOKAL
        // Variabel
            // c : integer
            // apakahBedaSatuBit : boolean
    // ALGORITMA
    int c=ukuranBit-1;
    int apakahBedaSatuBit=0;
    while(c!=-1)
    {
        if(a->binary[c]!=b->binary[c])
        {
            if(apakahBedaSatuBit)
                return 0;
            else
                apakahBedaSatuBit=1;
        }
        c--;
    }
    return 1;
}