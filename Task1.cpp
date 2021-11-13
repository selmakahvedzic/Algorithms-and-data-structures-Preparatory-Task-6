#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <fstream>



using namespace std;
template <typename Tip>
void bubble_sort(Tip *niz,int velicina)
{
    for(int i=velicina-1; i>=1; i--) {
        for(int j=1; j<=i; j++) {
            if(niz[j-1]>niz[j]) {
                std::swap(niz[j-1],niz[j]);
            }
        }
    }
}

template <typename Tip>
void selection_sort(Tip *niz, int velicina)
{
    Tip min=niz[0];
    int minimum=0;

    for(int i=0; i<velicina-1; i++) {
        min=niz[i];
        minimum=i;
        for(int j=i+1; j<velicina; j++) {
            if(min>niz[j]) {
                min=niz[j];
                minimum=j;
            }
        }
        std::swap(niz[i],niz[minimum]);
    }
}

template<typename Tip>
int particija(Tip *niz, int prvi, int posljednji)
{
    Tip pivot=niz[prvi];
    int i=prvi+1;
    while(i<=posljednji && niz[i]<pivot) {
        i++;
    }

    for(int j=i+1; j<=posljednji; j++) {
        if(niz[j]<pivot) {
            std::swap(niz[i++], niz[j]);
        }
    }
    std::swap(niz[prvi],niz[i-1]);
    return i-1;
}


template <typename Tip>
void quicksort(Tip *niz, int prvi, int posljednji)
{
    if(prvi<posljednji) {
        int pi=particija(niz,prvi,posljednji);
        quicksort(niz,prvi,pi-1);
        quicksort(niz,pi+1,posljednji);
    }
}


template <typename Tip>
void quick_sort(Tip *niz, int velicina)
{
    quicksort(niz,0,velicina-1);
}




template <typename Tip>
void merge2(Tip *niz, int velicina, int l, int u, int pi)
{
    int i=l,j=pi+1,k=0;
    Tip *a=new Tip[u-l+1];

    while (i<=pi && j<=u) {
        if(niz[i]<=niz[j]) a[k++]=niz[i++];
        else a[k++]=niz[j++];

    }

    while(i<=pi) a[k++]=niz[i++];
    while(j<=u) a[k++]=niz[j++];
    k=0;
    for(int i=l; i<=u; ++i) niz[i]=a[k++];
    delete [] a;
}


template <typename Tip>
void merge_sort(Tip *niz,int velicina, int l=-1, int u=-1)
{
    if(l==-1 && u==-1) {
        l=0;
        u=velicina-1;
    }

    if(l<u) {
        int pi=l+(u-l)/2;
        merge_sort(niz,velicina,l,pi);
        merge_sort(niz,velicina,pi+1,u);
        merge2(niz,velicina,l,u,pi);
    }
}

void ucitaj(string filename, int *&niz, int &velicina)
{
    ifstream ulaz;
    ulaz.open(filename+".txt");
    int kapacitet(1000);
    niz=new int[kapacitet];
    int i(0),broj(0);
    while(!ulaz.eof()) {
        if(i==kapacitet) {
            kapacitet*=2;
            int *niz2=new int[kapacitet];
            for(int j=0; j<i; j++) {
                niz2[j]=niz[j];
            }

            delete [] niz;
            niz=niz2;
            niz2=nullptr;
        }

        ulaz>>broj;
        niz[i++]=broj;
    }
    velicina=--i;
    ulaz.close();
}


void generisi(string filename, int velicina)
{
    ofstream izlaz;
    izlaz.open(filename+".txt");
    for(int i=0; i<velicina; i++) {
        izlaz<<rand()<<" ";
    }
    izlaz.close();
}



void f(string filename, int velicina)
{
    int *niz;
    ucitaj(filename,niz,velicina);
    cout<<"Meni:/n"<<"Unesite: 1 - za bubble sort/n2 - za selection sor/n3 -  za quick sort/n4 - za merge sort";
    int opcija;
    cin>>opcija;

    clock_t start(clock()),finish;

    switch(opcija) {
    case 1:
        bubble_sort(niz,velicina);
        finish=clock();
        break;

    case 2:
        selection_sort(niz,velicina);
        finish=clock();
        break;

    case 3:
        quick_sort(niz,velicina);
        finish=clock();
        break;

    case 4:
        merge_sort(niz,velicina);
        finish=clock();
        break;
    }

    std::cout << "Funkcija se izvršavala: " << finish-start << "milisekundi.";

    for(int i=1; i<velicina; i++) {
        if(niz[i-1]>niz[i]) {
            std::cout << "Niz nije sortiran.";
            break;
        }
        std::cout << "Niz je sortiran.";
    }
    ofstream izlaz;
    izlaz.open("izlazna.txt");
    for(int i=0; i<velicina-1; i++) {
        izlaz<<niz[i]<<" ";
    }
}



int main()
{
    std::cout << "Unesite naziv datoteke i velicinu niza:";
    std::string ime;
    std::cin>>ime
            ;
    int velicina(0);
    std::cin>>velicina;

    generisi(ime,velicina);
    f(ime,velicina);

    return 0;
}
