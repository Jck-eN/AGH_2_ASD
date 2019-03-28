void swap(int &a, int &b);

// MergeSort na tablicy
void Merge(int tab[], int p, int mid, int k){
    int left=p, right=mid+1, i=0;
    int *tmp = new int[k-p+1];
    while(left<=mid and right <= k){
        tmp[i++]=(tab[left] <= tab[right] ? tab[left++] : tab[right++]);
    }
    while(left<=mid){
        tmp[i++]=tab[left++];
    }
    while(right<=k){
        tmp[i++]=tab[right++];
    }
    for(int j=0; j<k-p+1; j++){
        tab[p+j]=tmp[j];
        delete[] tmp;
    }
}

void MergeSort(int tab[], int p, int k){
    if(p!=k){
        int sr=(p+k)/2;
        MergeSort(tab, p, sr);
        MergeSort(tab, sr+1, k);
        Merge(tab, p, sr, k);
    }
}
//-----
// QuickSort

void QuickSort(int t[], int p, int r){
    int q = Partition(t, p, r);
    QuickSort(t, p, q-1);
    QuickSort(t, q+1, r);
}

int Partition(int t[], int p, int r){
    int x=t[r];
    int i, j;
    i=p-1;
    for(j=p; j<r; j++){
        if(t[j]<x){
            i++;
            swap(t[j], t[i]);
        }
    }
    swap(t[r], t[i+1]);
    return i+1;
}
//-----
//CountingSort

void CountingSort(int A[], int k, int N){
    int* B = new int[N]; //B - docelowa tablica
    int* C = new int[k]; //C - przechowuje liczbę el. o wartości równiej indeksowi C
    for(int i=0; i<N; i++) B[i]=0;
    for(int i=0; i<k; i++) C[i]=0;
    for(int i=0; i<N; i++) C[A[i]]++;
    for(int i=1; i<k; i++) C[i]+=C[i-1]; 
    for(int i=N-1; i>=0; i--){
        C[A[i]]--; //Numer indeksu w B gdzie ma trafić el. A[i]
        B[C[A[i]]]=A[i];
    }
    A=B;
}
