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

#include "logicMinimization.h"

// REALISASI FUNGSI/PROSEDUR
int logicMinimization(char modeInput)
{
    // KAMUS LOKAL
        // Variabel
            // i : integer
            // temp : integer
            // KondisidontCare : boolean { kondisi yang menyatakan bahwa terdapat don't care}
            // dontCareNumber : integer
            // banyakMinterm : integer
    // ALGORITMA
    int i,temp,kondisiDontCare=0,dontCareNumber, banyakMinterm;
    
    maxGroup=-1;
    newMaxGroup=-1;
    printf("Masukkan banyaknya minterm:\n>>> ");
    scanf("%d",&banyakMinterm);

    if(banyakMinterm==0)
        return 1;
    for(i=0; i<limit; i++)
        minterms[i]=-1;
    for(i=0; i<limit; i++)
        dontCares[i]=-1;
    
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
        scanf("%d",&dontCareNumber);
        for(i=0; i<dontCareNumber; i++)
        {
            printf("Masukkan don't care ke-%d:\n>>> ",i+1);
            scanf("%d",&temp);
            dontCares[temp]=1;
            add(temp);
        }
    }

    Table.top=0;
    initTable();    //initialise the Prime Implicants Table with all cells -1 to denote empty.
    pair();           //do the pairing
    displayTable(); //display the Prime Implicants Table
    printf("Simplified Boolean Expression is.......");
    analyseTable();  //Analyse the table and print the result
    
    printf("\n");
    return 0;
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

void displayTable()
{
    // KAMUS LOKAL
        // Variabel
            // i, j : integer
    // ALGORITMA
    int i,j;
    printf("Prime Implicants Table.............\n");
    for(i=0; i<Table.top; i++)
    {
        konversiBinerKeNotasiMinterm(i);
        for(j=0; j<=limit-1; j++)
        {

            if(Table.brr[i][j]==1)
                printf("   %d  ",j);
        }
        printf("\n");
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

void initTable()
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
    // ALGORITMA
    int i,j;
    for(j=0; j<=limit-1; j++)
        for(i=0; i<=limit-1; i++)
        {
            Table.brr[j][i]=-1;
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
            printf("%d,",p->paired.paired[count]);
            count++;
        }
        printf("\b");
        count=0;
        printf("   ");
        while(j<ukuranBit)
        {
            if(p->binary[j]==-1)
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

void pair()
{
    node *p,*q;
    int oneMatched=0;
    static int iteration=1; // menyimpan jumlah iterasi atau pencacahan pass
    p=head;
    q=p;
    printf("Iteration  %d........\n",iteration);
    iteration++;
    display();
    newMaxGroup=-1;
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

    addToTable();
    if(oneMatched) // memeriksa jika setidaknya ada satu pair yang telah  dibentuk
    {
        head=head2;
        head2=NULL;
        maxGroup=newMaxGroup;
        pair();
    }
}

void addToTable()
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
            if(Table.top!=0) // memeriksa apakah ada duplikat
            {
                for(j=0; j<Table.top; j++)
                {
                    allMatched=1;
                    for(k=0; k<p->numberOfPairs; k++)
                    {
                        if(Table.brr[j][p->paired.paired[k]]==1)
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
                Table.arr[Table.top][i]=p->binary[i];
                i--;
            }
            for(i=0; i<p->numberOfPairs; i++)
            {
                if(cekDontCare(p->paired.paired[i])==1)      //if minterms is in dont care dont add it to table
                {
                    Table.brr[Table.top][p->paired.paired[i]]=-1;
                    continue;
                }
                Table.mintermCounter[Table.top]++;
                Table.brr[Table.top][p->paired.paired[i]]=1;
            }
            Table.top++;
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
    for(i=0; i<Table.top; i++)
    {
        if(Table.mintermCounter[i]>greatest)
        {
            *row=i;
            greatest=Table.mintermCounter[i];
        }
    }
    return greatest;
}

void analyseTable()
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

void hapusMintermDariTabel(int n) 
{
    // KAMUS LOKAL
        // Variabel
            // i,j : integer
    // ALGORITMA
    int i,j;
    for(i=0; i<=limit-1; i++)
    {
        if(Table.brr[n][i]==1)
        {
            minterms[i]=-1;

            for(j=0; j<Table.top; j++)
            {
                if(Table.brr[j][i]==1)
                {
                    Table.brr[j][i]=-1;
                    Table.mintermCounter[j]--;
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
    for(i=0; i<Table.top; i++)
    {
        if(Table.brr[i][n]==1)
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
        if(Table.arr[n][c]!=-1)
        {
            if(Table.arr[n][c]==1)       
                printf("%c",charactersNormal[c]);

            else
                printf("%c",charactersComplement[c]);
        }
        c++;
    }
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