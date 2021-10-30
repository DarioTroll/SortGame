#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#define LUN 100
#define MAXTUBI 10

struct tubo {
    char elem[4];
    bool attivo;
    int pointer;
};

void riempi_tubi (char settings[], int num_t, struct tubo t[]);
void gioca (struct tubo vet[]);
bool push_pop (struct tubo vet[], int da, int a);
bool ordinato (struct tubo vet[]);
void stampa (struct tubo vet[]);

int main (void) {
    system("cls");
    printf("SORT GAME\nMetti in ordine le lettere nei tubi!!\n\nCOMANDI\nMuovi: DA A (es. Muovi 0 4)");
    Sleep(5000);
    system("cls");
    int numero_tubi;
    struct tubo vet[MAXTUBI];
    
    FILE *fp;
    if ((fp=fopen("livelli.txt","r"))==NULL) {
        fprintf(stderr,"\nImpossibile aprire il file!!");
        return -1;
    }
    
    char riga[LUN];
    char impostazione[LUN];
    int i;
    
    while (fgets(riga,sizeof(riga),fp)!=NULL) {
        sscanf(riga,"%d %[^\n]",&numero_tubi,impostazione);
        riempi_tubi(impostazione,numero_tubi,vet);
        gioca(vet);
    }
    
    return 0;
}

void riempi_tubi (char settings[], int num_t, struct tubo t[]) {
    int i,j,selected;
    
    for (i=0;i<MAXTUBI;++i) {
        t[i].pointer=0;
        t[i].attivo=false;
    }
    
    for (i=0,j=0,selected=0;settings[i]!='\0';++i) {
        if (settings[i]==' ') {
            ++selected;
            j=0;
        }
        else {
            t[selected].elem[j]=settings[i];
            if (settings[i]!='#')
                ++t[selected].pointer;
            else
                t[selected].elem[j]=' ';
            ++j;
        }
    }
    for (i=0;i<num_t;++i) t[i].attivo=true;
}

void gioca (struct tubo vet[]) {
    int da,a;
    stampa(vet);
    while (!ordinato(vet)) {
        do {
            printf("\n\n\n\tMuovi: ");
            scanf("%d%d",&da,&a);
        } while (da==a || (!vet[da].attivo) || (!vet[a].attivo) || !push_pop(vet,da,a));
        system("cls");
        stampa(vet);
    }
    printf("\n\nLIVELLO SUPERATO!!\n\nCaricando il nuovo livello...");
    Sleep(3000);
    system("cls");
}

bool push_pop (struct tubo vet[], int da, int a) {
    if (vet[da].pointer==0) {
        printf("\n\tQuel tubo e' vuoto!!");
        return false;
    }
    if (vet[a].pointer==4) {
        printf("\n\tQuel tubo e' pieno!!");
        return false;
    }
    vet[a].elem[vet[a].pointer]=vet[da].elem[vet[da].pointer-1];
    vet[da].elem[vet[da].pointer-1]=' ';
    ++vet[a].pointer;
    --vet[da].pointer;
    
    return true;
}

bool ordinato (struct tubo vet[]) {
    int i,j;
    char base;
    for (i=0;vet[i].attivo;++i) {
        base=vet[i].elem[0];
        for (j=1;j<4;++j)
            if (base!=vet[i].elem[j]) return false;
    }
    return true;
}

void stampa (struct tubo vet[]) {
    int i,j;
    printf("\n\n");
    for (i=0;i<4;++i) {
        printf("\t");
        for (j=0;vet[j].attivo;++j)
            printf("|  %c  ",vet[j].elem[3-i]);
        printf("|\n");
    }
    printf("\t");
    for (j=0;vet[j].attivo;++j)
            printf("------");
    printf("-\n\t");
    for (j=0;vet[j].attivo;++j) printf("   %d  ",j);
}
