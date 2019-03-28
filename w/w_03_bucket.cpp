#include <iostream>
using namespace std;

const int N;
struct list{};
void put(list tab, int x);
void sort(list tab);

void BucketSort(float A[], int k){
    list* B;
    B = new list[k];
    for(int i = 0 ; i < N; i++){
        put(B[(int)(k*A[i])], A[i]);
    }
    for(int i=0; i<k; i++) sort(B[i]);
}

//----------------
// Szukanie i-tego elementu tablicy - Quicksort 

int partition(int* tab, int p, int r);

int Select(int A[], int p, int r, int i){
    if(p==r)return A[p];
    int q = partition(A, p, r);
    int k=q-p+1;
    if(i==k) return A[q];
    if(i<k) return Select(A, p, q-1, i);
    if(i<k) return Select(A, q+1, r, i);
}