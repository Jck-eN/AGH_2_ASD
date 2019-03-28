#include <iostream>
using namespace std;

//-----------
//1. Dana jest posortowana tablica int A[N] oraz liczba x.
//Napisac program, który stwierdza czy istnieją indeksy i oraz j,
//takie ze A[i]+A[j]=x (powinno działać w czasie O(N))

bool TwoIndexes(int* tab, int sum, int n){
    int i=0, j=n-1;
    while(i<j){
        if(tab[i]+tab[j]<sum){
            i++;
        }
        else if(tab[i]+tab[j]>sum){
            j--;
        }
        else{
            return true;
        }
    }
    return false;
}

//-----------
//2. Zaimplementować algorytm, który dla tablicy int A[N] wyznacza
// rekurencyjną medianę median. (magiczne piątki)
/*
void SelectionSort5(int t[], int l, int r);
int Partition(int t[], int p, int r, int med);

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int MagicFives(int tab[], int l, int r, int k){
    int n=r-l+1;
    if(l>=r) return tab[l];
//    if(n<10) return kFromSelectionSort(tab, l, r, k+1);

    int* medians = new int[(n+4)/5];
    for(int i=0, c=0; i<n; i+=5, c++){       //Znajdywanie mediany w piątkach (sortowanie bąbelkowe)
        if(i+4<n)SelectionSort5(tab, i, k);
        else SelectionSort5(tab, i, i+4);
        if(i+2<n) medians[c]=tab[i+2];
        else medians[c]=tab[k];
    }
    int mmedian = MagicFives(medians, 0, ((n+4)/5)-1, (((n+4)/5)-1)/2+1) ;//większe od mmedian
    int pivot_idx = Partition(tab, l, r, mmedian);          //równe mmedian
    if(pivot_idx-l>k-1) return MagicFives(tab, l, pivot_idx-1, k);
    else if(pivot_idx-l==k-1) return tab[pivot_idx];
    else return MagicFives(tab, pivot_idx+1, r, k-(pivot_idx-l));
}

int Partition(int t[], int p, int r, int med){
    int i, j;
    i=p-1;
    for(j=p; j<=r; j++){
        if(t[j]<med){
            i++;
            swap(t[j], t[i]);
        }
    }
    return i+1; // pivot_idx
}


void SelectionSort5(int t[], int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        int min = i;
        for (int j = i + 1; j <=r; j++)
        {
            if (t[j] < t[min])
                min = j;
        }
        swap(t[i], t[min]);
    }
    return;
}

*/
void iSort(int tab[], int n){};

int mMedian(int* tab, int n){
    if(n<=5){
        iSort(tab, n);
        return tab[n/2];
    }
    int a = (n+4)/5;
    int *M = new int[a];
    for(int i=0; i<a; ++i){
        int begin=i*5;
        int size = min(5, n-begin);
        iSort(tab+begin, size);
        M[i]=tab[begin+2];
    }
    return mMedian(M, a);
}

//3. Mamy daną tablicę A z n liczbami. Proszę zaproponować algorytm
//o złożoności O(n), który stwierdza, czy w tablicy ponad połowa elementów
//ma jednakową wartość.

bool isMoreThanHalf(int* tab, int n){
    int counter=1;
    int val=tab[0];
    for(int i=1; i<n; i++){
        if(tab[i]==val){
            counter++;
        }
        else counter--;
        if(counter<=0){
            val=tab[i];
            counter=1;
        }
    }
    counter=0;
    for(int i=0; i<n; i++){
        if(tab[i]==val) counter++;
    }
    if(counter>n/2) return true;
    else return false;
}


//--------------------
//4. Proszę zaproponować algorytm sortujący ciąg słów o różnych długościach
//w czasie proporcjonalnym do sumy długości tych słów.

void CountingSort(string tab[], int left, int right, int depth=0){};

void SortStrings(string tab[], int left, int right, int depth=0){
    if(left>=right) return; 
    CountingSort(tab, left, right, depth);

    char ch=tab[left].at(depth); //sprawdzamy kolejno znaki w sortowanych uprzednio
    int begin=left;              //słowach na depth-tej pozycji
    for(int i=left; i<=right; i++){
        if(ch!=tab[i].at(depth)) {
            SortStrings(tab, begin, i-1, depth+1); //sortuje słowa z tą samą literą według kolejnej litery 
            ch=tab[i].at(depth);
            begin=i;
        }
    }
    SortStrings(tab, begin, right, depth+1);
    return;
}



//------------------------


int main()
{
    int tab[] = {1,2,3,4,5,6,7,8,9};
    //cout << MagicFives(tab, 0, 8, 8);


    system("pause");
    return 0;
}
