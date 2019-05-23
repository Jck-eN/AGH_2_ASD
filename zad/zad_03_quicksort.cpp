#include <iostream>
#include <ctime>
using namespace std;

struct node
{
    node *next;
    int val;
};

void swap(int &i, int &j)
{
    int tmp = i;
    j = i;
    i = tmp;
}

//Zadanie 1. Quicksort na listach

node *partition(node *&head)
{
    if (head == nullptr)
        return nullptr;
    node *tmp = head;
    int w = tmp->val;
    tmp = tmp->next;
    node *left;
    node *l_tmp = left;
    node *right;
    node *r_tmp = right;
    while (tmp != nullptr)
    {
        if (tmp->val < w)
        {
            if (l_tmp == nullptr)
            {
                l_tmp = tmp;
                left = tmp;
            }
            else
            {
                l_tmp->next = tmp;
            }
            tmp = tmp->next;
            l_tmp = l_tmp->next;
            l_tmp->next = nullptr;
        }
        else
        {
            if (r_tmp == nullptr)
            {
                r_tmp = tmp;
                right = tmp;
            }
            else
            {
                r_tmp->next = tmp;
            }
            tmp = tmp->next;
            r_tmp = r_tmp->next;
            r_tmp->next = nullptr;
        }
    }
    tmp = head;
    tmp->next = right;
    head = left;
    return tmp; //zwracamy wskaźnik na początek prawej listy (pivota)
}

node *QuickSortLists(node *head)
{
    if (head == nullptr)
        return nullptr;
    if (head->next == nullptr)
        return head;
    node *q = partition(head);  //pivot dołączony na początek prawej listy

    head = QuickSortLists(head);            //lewa posortowana strona
    node* right = QuickSortLists(q->next);  //Prawa posortowana strona
    node* tmp=head;
    if(tmp!=nullptr){
        while(tmp->next!=nullptr) tmp=tmp->next;
        tmp->next=q;
        q->next=right;
    }
    else{
        tmp->next=q;
        q->next=right;
    }
    return head;
}

// Zadanie 2.Proszę zaimplementować algorytm, który w czasie liniowym sortuje
// tablicę A zawierającą n liczb ze zbioru 0,...,n^2−1.
void LineSort(int *A, int size, int n)
{
    int *C = new int[n];
    int *B = new int[size];

    for (int i = 0; i < n; i++)
    {
        C[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        B[i] = 0;
        C[(A[i] % n)]++;
    }
    for (int i = 1; i < n; i++)
    {
        C[i] += C[i - 1];
    }
    for (int i = size - 1; i >= 0; i--)
    {
        C[(A[i] % n)]--;
        B[C[(A[i] % n)]] = A[i];
    }
    int *tmp = A;
    A = B;
    B = tmp;
//Sortowanie wg drugiej cyfry (w systemie n-kowym) z prawej
    for (int i = 0; i < n; i++)
    {
        C[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        B[i] = 0;
        C[((A[i]) / n)]++;
    }
    for (int i = 1; i < n; i++)
    {
        C[i] += C[i - 1];
    }
    for (int i = size - 1; i >= 0; i--)
    {
        C[(A[i] / n)]--;
        B[C[(A[i] / n)]] = A[i];
    }
    A = B;
    return;
}

// Zadanie 3. Mamy serię pojemników z wodą, połączonych (każdy z każdym) rurami.
// Pojemniki maja kształty prostokątów (2d), rury nie maja objętości (powierzchni).
// Każdy pojemnik opisany jest przez współrzędne lewego górnego rogu i prawego dolnego rogu.
// Wiemy, ze do pojemników nalano A wody (oczywiście woda rurami spłynęła do najniższych pojemników).
// Obliczyć ile pojemników zostało w pełni zalanych.

struct Container
{
    int l_x;
    int l_y;
    int r_x;
    int r_y;
};

int FullContainers(Container container[], int n, int A)
{
    int min{}, max{};
    bool min_def = false, max_def = false;
    for (int i = 0; i < n; i++)
    {
        if (min_def == false || min > container[i].r_y)
        {
            min_def = true;
            min = container[i].r_y;
        }
        if (min_def == false || min > container[i].l_y)
        {
            max_def = true;
            max = container[i].l_y;
        }
    }
    int* level=new int[max-min+1];
    for(int i=0; i<max-min+1; i++){
        level[i]=0;
    }
    for (int i = 0; i < n; i++){
        // curr_level=i+min;
        for(int j=container[i].r_y; j<=container[i].l_y; j++){
            level[j]+=(container[i].r_x-container[i].l_x+1);
        }
    }
    int j=0;
    while(level[j]<=A){
        A-=level[j];
        j++;
    }   //j(+min)-ty poziom jest pierwszym nie zalanym wodą
    int wynik;
    for (int i = 0; i < n; i++){
        if(container[i].l_y<j+min) wynik++;
    }
    delete[] level;
    return wynik;
}


/* 4. Dany jest ciąg przedziałów domkniętych [a1, b1], . . . ,[an, bn].
Proszę zaproponować algorytm, który znajduje taki przedział [at, bt],
w którym w całości zawiera się jak najwięcej innych przedziałów. */

struct interval{
    int lx;
    int rx;
    int left_sort_index;
    int right_sort_index;
};

void SortLeftEnd(interval tab[]);
void SortRightEnd(interval tab[]);

interval IntervalContainment(interval inter[], int n){
    SortLeftEnd(inter);
    SortRightEnd(inter);
    int max = inter[0].right_sort_index-inter[0].right_sort_index;
    interval max_interval = inter[0];
    for(int i=1; i<n; i++){
        if(inter[i].right_sort_index-inter[i].right_sort_index>max){
            max_interval = inter[i];
            max = inter[i].right_sort_index-inter[i].right_sort_index;
        }
    }
    return max_interval;
}