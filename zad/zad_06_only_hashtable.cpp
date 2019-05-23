#include <iostream>
#include <cmath>
using namespace std;

struct Data{
    int number;
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
        if(ht->element[i].data!=NULL){
            cout << i << ". " << ht->element[i].data->number  << "\t" << ht->element[i].zajety <<"\t" << ht->element[i].usun << endl;
        }else{
             cout << i << ". " << "<~>"  << "\t" << ht->element[i].zajety <<"\t" << ht->element[i].usun << endl;
        }
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

int main()
{
    hashtable* tab = new hashtable(15);
    Data data[10] = {{1},{2},{3},{4},{5},{6},{7},{8},{9},{0}};
    for(int i=0; i<10; i++){
    ht_insert(tab, &data[i]);
    }
    
    ht_print(tab);
    cout << endl;
    return 0;
}
