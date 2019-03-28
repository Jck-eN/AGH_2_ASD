#include <iostream>
using namespace std;

const int N;

int digit(int n, int base, int c){
    if(c==1){return n%base;}
    if(c==2){return n/base;}
}

void RadixSort(int t[], int N){
    CountingSort(t, N, 1);
    CountingSort(t, N, 2);
}

void CountingSort(int t[], int N, int c){
    int* A = new int[N];
    int* B = new int[N];
    for(int i=0; i<N; i++){
        B[i]=0;
    }
    for(int i=0; i<N; i++) B[digit(t[i], N, c)]++;
    for(int i=1; i<N; i++) B[i]+=B[i-1];
    for(int i=1; i<N; i++) B[i]+=B[i-1];
    for(int i=N-1; i>0; i--) A[--B[digit(t[i], N, c)]]=t[i];
    for(int i=0; i<N; i++)t[i]=A[i];
    return;
}

/*------------------------|
init(n)             O(1)  |
insert(idx, val)    O(1)  |
get(idx)            O(1)  |
-------------------------*/




int main()
{
    
    
    cout << endl;
    system("pause");
    return 0;
}
