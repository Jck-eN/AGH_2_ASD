#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX = 10000001;
const int SIZE = 10000000;

#define size t[0]

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void ArrayRandomize(int t[], int s)
{
    srand(time(NULL));
    t[0]=s;
    for (int i = 1; i <= s; i++)
    {
        t[i] = rand();
    }
}

void ArrayShow(int t[])
{
    cout << "---" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << t[i] << " ";
    }
    cout << endl;
    cout << "---" << endl;
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
    if (l <= size && t[l] > t[max])
        max = l;
    if (r <= size && t[r] > t[max])
        max = r;
    if (max != i){
        swap(t[i],t[max]);
        heapify(t, max);
    }
}
//Budowa kopca
void build(int t[]){
    for(int i=size/2; i>0; i--){
        heapify(t, i);
    }
}

//Heapsort

void HeapSort(int t[]){
    build(t);
    for(int i=size; i>0; i--){
        swap(t[i], t[1]);
        size--;
        heapify(t, 1);
    }
}



//KOLEJKA PRIORYTETOWA
//---------------------------------------

//Pobieranie z kolejki
int get_max(int k[], int &length){
    if(length==0) return -1;
    int res=k[1];
    k[1]=k[length];
    length--;
    heapify(k, 1);
    return res;
}

void put(int k[], int &length, int val){
    length++;
    k[length]=val;
    int i=length;
    while(k[i]>k[parent(i)]){
        swap(k[i], k[parent(i)]);
        i=parent(i);
    }
}

//---------------------------------------


int main()
{
    int *t = new int[MAX];
    ArrayRandomize(t, SIZE);
    clock_t begin = clock();
    HeapSort(t);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "---" << endl;
    cout << "Czas heap: " << elapsed_secs<< endl;
    size=SIZE;

    cout << endl;
    system("PAUSE");


    return 0;
}
