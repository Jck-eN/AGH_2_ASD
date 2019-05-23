#include <iostream>
#include <cmath>
using namespace std;

// ĆWICZENIA 6 - Jacek Nitychoruk
//---------------------------------------------
/* 
1. Proszę zaimplementować następujące operacje na tablicy z haszowaniem:
- wstawianie
- usuwanie
- wyszukiwanie
- reorganizacja (usunięcie kluczy zaznaczonych do skasowania)
*/

struct Data{
    int number;
    int idx;
};

struct ht_el{
    Data* data;
    bool zajety;
    bool usun;
};

int hash_single(int kn, int s){
    double a = (fmod(kn*0.618033, 1.0))*s;
    return (int)a;

}

int h(int kn, int i, int s){
    return ((hash_single(kn, s)+i*i))%s;
}

struct hashtable{
    int size;
    ht_el* element;

    hashtable(int s){
        size=s;
        element = new ht_el[s];
        for(int i=0; i<s; i++){
            element[i].data = NULL;
            element[i].zajety=false;
            element[i].usun=false;
        }
    }

};

void ht_print(hashtable* ht){
    cout << "Tablica z haszowaniem. Rozmiar: " << ht->size << endl;
    cout << "_______zajety:___usun:_______" << endl;
    for(int i=0; i<ht->size; i++){
        cout << i << ". " << ht->element[i].data->number  << " \t[" << ht->element[i].data->number << "] \t"<< ht->element[i].zajety <<" \t" << ht->element[i].usun << endl;
    }
    cout << "________________________________" << endl;
}

void ht_insert(hashtable* ht, Data* data){
    int i=0;
    int idx = 0;
    do{
        idx = h(data->number, i, ht->size);
        if(ht->element[idx].zajety==false) {
            ht->element[idx].zajety=true;
            ht->element[idx].usun=false;
            ht->element[idx].data=data;
            return;
        }
        else i++;
    }
    while(i<ht->size);
    cout << "BLAD WSTAWIANIA: " << data->number << endl;
    return;
}

Data* ht_search(hashtable* ht, int k){
    int i=0;
    int j=-1;
    do{
        j=h(k, i, ht->size);
        if(ht->element[j].data->number==k) return (ht->element[j].data);
        else i++;
    }
    while(ht->element[j].zajety || ht->element[j].usun || i<ht->size);
    return NULL;
}

void ht_remove(hashtable* ht, int k){
    int i=0;
    int j=-1;
    do{
        j=h(k, i, ht->size);
        if(ht->element[j].data->number==k) {
            ht->element[j].usun=true;
            ht->element[j].zajety=false;
            Data* tmp=ht->element[j].data;
            ht->element[j].data=NULL;
            delete tmp;
            return;
        }
        else i++;
    }
    while(ht->element[j].zajety || ht->element[j].usun || i<ht->size);
}

void ht_reorganize(hashtable* ht){
    Data** tmp = new Data*[ht->size];
    int j=0;
    for(int i=0; i<ht->size; i++){
        if(ht->element[i].zajety) {
            tmp[j]=ht->element[i].data;
            j++;
        }
        ht->element[i].data=NULL;
        ht->element[i].usun=false;
        ht->element[i].zajety=false;
    }
    for(int i=j-1; i>=0; i--){
        ht_insert(ht, tmp[i]);
        tmp[i]=NULL;
    }
    delete[] tmp;

    return;
}
/*
--------------------------------
2. Dana jest nieposortowana tablica A[N] oraz liczba x.
Proszę napisać funkcję, która sprawdza na ile sposobów można przedstawić
x jako sumę A[i]+A[j] takiego że i<j.
*/

int sum(int x, int* A, int N){
    hashtable* ht = new hashtable(N);
    int counter = 0;
    Data* tmp;
    for(int i=0; i<N; i++){
        tmp=NULL;
        int szuk=x-A[i];
        tmp=ht_search(ht, szuk);
        if(tmp!=NULL && tmp->idx > i) counter++;
    }
    return counter;
}