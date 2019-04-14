//PORÓWNANIE SORTOWAŃ
//_________________________
#include <string>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <conio.h>
#include <random>
#include <climits>

using namespace std;

//#define DEBUG 1;

void ArrayRandomize(int t[], int MAX)
{
    const int min = 0;
    const int max = INT_MAX;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min,max);
    for (int i = 0; i < MAX; i++)
    {
        t[i] = distribution(generator);
    }
}

void ArrayShow(int t[], int MAX)
{
    cout << "---" << endl;
    for (int i = 0; i < MAX; i++)
    {
        cout << t[i] << " ";
    }
    cout << endl;
    cout << "---" << endl;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//Sortowanie przez wstawianie
void InsertionSort(int t[], int MAX)
{
    for (int i = 1; i < MAX; i++)
    {
        int x = t[i]; // x - wartość porównywana
        int j = i - 1;
        while (t[j] > x and j >= 0)
        {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = x;
    }
}

//Sortowanie przez wybieranie
void SelectionSort(int t[], int MAX)
{
    for (int i = 0; i < MAX; i++)
    {
        int k = i;
        for (int j = i + 1; j < MAX; j++)
        {
            if (t[j] < t[k])
                k = j;
        }
        swap(t[i], t[k]);
    }
}

//Sortowanie bąbelkowe
void BubbleSort(int t[], int MAX)
{
    for (int n = MAX-1; n > 0; n--)
    {
        for (int i = 0; i < n; i++)
        {
            if (t[i] > t[i + 1])
            {
                swap(t[i], t[i + 1]);
            }
        }
    }
}
//MergeSort
//----------------
void Merge(int tab[], int p, int mid, int k)
{
    int left = p, right = mid + 1, i = 0;
    int *tmp = new int[k - p + 1];
    while (left <= mid and right <= k)
    {
        tmp[i++] = (tab[left] <= tab[right] ? tab[left++] : tab[right++]);
    }
    while (left <= mid)
    {
        tmp[i++] = tab[left++];
    }
    while (right <= k)
    {
        tmp[i++] = tab[right++];
    }
    for (int j = 0; j < k - p + 1; j++)
    {
        tab[p + j] = tmp[j];
    }
    delete[] tmp;
}

void MergeSortInt(int tab[], int p, int k)
{
    if (p != k)
    {
        int q = (p + k) / 2;
        MergeSortInt(tab, p, q);
        MergeSortInt(tab, q + 1, k);
        Merge(tab, p, q, k);
    }
}
void MergeSort(int tab[], int MAX)
{
    MergeSortInt(tab, 0, MAX - 1);
}

// KOPIEC ang. HEAP
//------------------------------------------
int parent(int i)
{
    return i / 2;
}
int left(int i)
{
    return 2 * i;
}
int right(int i)
{
    return 2 * i + 1;
}
// Porządkowanie kopca (jeden z elementów jest za mały)
void heapify(int t[], int i)
{
    int l = left(i);
    int r = right(i);
    int max = i;
    if (l <= t[0] and t[l] > t[max])
        max = l;
    if (r <= t[0] and t[r] > t[max])
        max = r;
    if (max != i)
    {
        swap(t[i], t[max]);
        heapify(t, max);
    }
}
//Budowa kopca
void build(int t[])
{
    for (int i = t[0] / 2; i > 0; i--)
    {
        heapify(t, i);
    }
}

//Heapsort

void HeapSort_int(int t[])
{
    build(t);
    for (int i = t[0]; i > 0; i--)
    {
        swap(t[i], t[1]);
        t[0]--;
        heapify(t, 1);
    }
}

void HeapSort(int t[], int MAX){
    t[0]=MAX-1;
    HeapSort_int(t);
}

// Quicksort
//-----------------------------------
int Partition(int t[], int p, int r)
{
    int x = t[r];
    int i, j;
    i = p - 1;
    for (j = p; j < r; j++)
    {
        if (t[j] < x)
        {
            i++;
            swap(t[j], t[i]);
        }
    }
    swap(t[r], t[i + 1]);
    return i + 1;
}

void QuickSort_int(int t[], int p, int r)
{
    if (p < r)
    {
        int q = Partition(t, p, r);
        QuickSort_int(t, p, q - 1);
        QuickSort_int(t, q + 1, r);
    }
}

void QuickSort(int t[], int MAX){
    QuickSort_int(t, 0, MAX-1);
}


//RadixSort
//---------------------
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 



void CountingSort(int t[], int N, int exp){
    int* A = new int[N];
    int* B = new int[N];
    for(int i=0; i<N; i++){
        B[i]=0;
    }
    for(int i=0; i<N; i++) B[(t[i]/exp)%10]++;
    for(int i=1; i<N; i++) B[i]+=B[i-1];
    for(int i=N-1; i>=0; i--) A[--B[(t[i]/exp)%10]]=t[i];
    for(int i=0; i<N; i++)t[i]=A[i];
    delete[] A;
    delete[] B;
    return;
}
void RadixSort(int t[], int MAX){
    int m = getMax(t, MAX);

    for (int exp = 1; m/exp > 0; exp *= 10) 
    CountingSort(t, MAX, exp); 
}

//----------------------------------------------------------
double Sort(void sort_type(int*, int), int t[], int MAX){
    int* b_tab = new int[MAX];
    for(int i=0; i<MAX; i++){
            b_tab[i]=t[i];
    }
    
    clock_t begin = clock();
        sort_type(b_tab, MAX);
    clock_t end = clock();

#ifdef DEBUG
     ArrayShow(b_tab, MAX);
#endif
    delete[] b_tab;
    return ((double)(end-begin)/CLOCKS_PER_SEC);
}



void naglowek(){
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t Porownanie czasow sortowan\t\tv1.0\t|"  << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t\t\t\tAutor: Jacek Nitychoruk\t|" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}
void menu(){
    cout << endl;
    cout << "Pojedynczy pomiar:"<< endl;
    cout << "------------------" << endl;
    cout << "1. Wszystkie sortowania" << endl;
    cout << "2. Proste sortowania" << endl;
    cout << "3. Szybkie sortowania" << endl;
    cout << "4. Szybkie + Radix" << endl;
    cout << endl;    
    cout << "Skokowe pomiary:"<< endl;    
    cout << "------------------" << endl;
    cout << "5. Wszystkie sortowania" << endl;
    cout << "6. Proste sortowania" << endl;
    cout << "7. Szybkie sortowania" << endl;
    cout << "8. Szybkie + Radix" << endl;
    cout << endl;
    cout << "0. Wyjscie" << endl;
    cout << endl;
}

void sortowania(int pocz, int koniec, int MAX, int powt, int skok){
    string sorts[7]={"Insertion:", "Selection:", "Bubble:\t", "Merge:\t", "Heap:\t", "Quick:\t", "Radix"};

    void (*sort_ptr[7])(int t[], int MAX)={InsertionSort, SelectionSort, BubbleSort, MergeSort, HeapSort, QuickSort, RadixSort};

    cout << "MAX:\t";
    if(MAX>=1000000) cout << "\t";
    for(int i=pocz; i<koniec;i++){
        cout << sorts[i] << "\t";
    }
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    for(int i=0; i<powt; i++){
        cout << MAX << ":\t";
        for(int i=pocz; i<koniec;i++){   

            int *t = new int[MAX];
            ArrayRandomize(t, MAX);
            
            cout <<fixed<<setprecision(3)<<Sort(sort_ptr[i], t, MAX) << "\t\t";

            delete[] t;
        }
        MAX+=skok;
        cout << endl;
    }
    cout << endl;
    cout << "Nacisnij klawisz, aby wrocic do menu.";
    cin.get();
    cin.get();
}

int main()
{
    while(true){
        int MAX=-1;
        int komenda =-1;
        int poczatek=1, koniec=7;
        bool skokowo=false;
        system("cls");
        naglowek();
        menu();
        char input = getch();
        komenda=input-'0';
        switch(komenda){
            case 1: break;
            case 2: koniec=3;
                    break;
            case 3: poczatek=4;
                    koniec=6;
                    break;
            case 4: poczatek=4;
                    break;

            case 5: skokowo=true;
                    break;
            case 6: skokowo=true;
                    koniec=3;
                    break;
            case 7: skokowo=true; 
                    poczatek=4;
                    koniec=6;
                    break;            
            case 8: skokowo=true; 
                    poczatek=4;
                    break;

            case 0: exit(0);
        }
        
        system("cls");
        naglowek();
        if(skokowo==false){
            cout << "Podaj liczbe elementow do sortowania: ";
            cin >> MAX;
            
            system("cls");
            naglowek();
            sortowania(poczatek-1, koniec, MAX, 1, 0);
        }
        else{
            int powt;
            int skok;
            cout << "Podaj wartosc poczatkowa, liczbe powtorzen oraz skok: " << endl;
            cin >> MAX;
            cin >> powt;
            cin >> skok;
            sortowania(poczatek-1, koniec, MAX, powt, skok);
        }
    }

    cout << endl;
    system("pause");
    return 0;
}
