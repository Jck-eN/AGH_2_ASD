#include <iostream>
using namespace std;

const int MAX = 1000;

struct node
{
    node *next;
    int val;
};

void swap(int *first, int *second);
int parent(int i) { return i / 2; }

//Zadanie 4. - "Liczba inwersji w tablicy"
int Merge(int tab[], int p, int mid, int k)
{
    int left = p, right = mid + 1, i = 0, inv_count = 0;
    int *tmp = new int[k - p + 1];
    while (left <= mid and right <= k)
    {
        if (tab[left] <= tab[right])
        {
            tmp[i] = tab[left];
            i++;
            left++;
        }
        else
        {
            tmp[i] = tab[right];
            i++;
            right++;
            inv_count += mid + 1 - left;
        }
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
    return inv_count;
}

int MergeSortInt(int tab[], int p, int k)
{
    int inv_count = 0;
    if (p != k)
    {
        int q = (p + k) / 2;
        inv_count += MergeSortInt(tab, p, q);
        inv_count += MergeSortInt(tab, q + 1, k);
        inv_count += Merge(tab, p, q, k);
    }
    return inv_count;
}

int MergeSort(int tab[], int size)
{
    return MergeSortInt(tab, 0, size - 1);
}

// Zadanie 1. "MergeSort na listach"

node *MergeLists(node *first, node *second)
{
    node *merged = new node;
    node *tmp = merged;
    while (first != nullptr and second != nullptr)
    {
        if (first->val <= second->val)
        {
            tmp->next = first;
            first = first->next;
            tmp = tmp->next;
            tmp->next = nullptr;
        }
        else
        {
            tmp->next = second;
            second = second->next;
            tmp = tmp->next;
            tmp->next = nullptr;
        }
    }
    if (first != nullptr)
    {
        tmp->next = first;
    }
    else if (second != nullptr)
    {
        tmp->next = second;
    }
    tmp = merged;
    merged = merged->next;
    delete tmp;
    return merged;
}

node *MergeSortLists(node *head)
{
    if (head->next == nullptr)
        return head;
    node *a = head;
    node *b = head;
    while (b->next != nullptr)
    {
        b = b->next;
        if (b->next != nullptr)
        {
            a = a->next;
            b = b->next;
        }
    }
    node *tmp = a->next;
    a->next = nullptr;
    node *left = MergeSortLists(head);
    node *right = MergeSortLists(tmp);
    return MergeLists(left, right);
}

//Zadanie 3. Proszę zaproponować strukturę przechowującą liczby naturalne, w której operacje: Insert i GetMedian mają złożoność O(log(n))

struct TwoHeaps
{
    int tab1[MAX]; // kopiec max
    int tab2[MAX]; // kopiec min
};

int getMedian(TwoHeaps *heaps)
{
    if (heaps->tab1[0] == heaps->tab2[0])
        return (heaps->tab1[1] + heaps->tab2[1]) / 2;
    else
        return heaps->tab1[1];
}

TwoHeaps *Insert(int val, TwoHeaps *heaps)
{
    if (val <= heaps->tab1[1])
        insert_in_max_heap(heaps->tab1, heaps->tab1[0]);
    else
        insert_in_min_heap(heaps->tab2, heaps->tab2[0]);
    if (heaps->tab1[0] > heaps->tab2[0] + 1)
        move_to_min_heap(heaps->tab1, heaps->tab2);
    else if (heaps->tab1[0] < heaps->tab2[0])
        move_to_max_heap(heaps->tab2, heaps->tab1);
}

void heapify_max(int tab[], int i);
void heapify_min(int tab[], int i);

void insert_in_max_heap(int t[], int val)
{
    t[0]++;
    int i = t[0];
    t[i] = val;
    while (i > 1 and t[parent(i)] > t[i])
    {
        swap(t[parent(i)], t[i]);
        i = parent(i);
    }
}
void insert_in_min_heap(int t[], int val)
{
    t[0]++;
    int i = t[0];
    t[i] = val;
    while (i > 1 and t[parent(i)] < t[i])
    {
        swap(t[parent(i)], t[i]);
        i = parent(i);
    }
}
void move_to_min_heap(int a[], int b[])
{
    int val = a[1];
    a[1] = a[a[0]];
    a[0]--;
    heapify_max(a, 1);
    insert_in_min_heap(b, val);
}
void move_to_max_heap(int a[], int b[])
{
    int val = a[1];
    a[1] = a[a[0]];
    a[0]--;
    heapify_min(a, 1);
    insert_in_max_heap(b, val);
}

//Zadanie 2. Proszę zaproponować/zaimplementować algorytm scalający k posortowanych tablic o łącznej długości n
//w jedną posortowaną tablicę w czasie O(n*log(k))
struct MinHeapNode
{
    MinHeapNode()
    {
        arr_num = -1;
        index = -1;
        val = -1;
    }
    int arr_num;
    int index;
    int val;
};

void InsertInMinHeap(MinHeapNode *heap, int **tab, int arr_num, int index);
MinHeapNode* PopFromMinHeap(MinHeapNode *heap);

int *merge_k_arrays(int **t, int k, int n)
{
    int el_in_arr = n / k;
    MinHeapNode *heap = new MinHeapNode[k]; //kopiec ze struktur z

    int *sorted = new int[n];
    int sorted_num = 0;

    for (int i = 0; i < k; i++)
    {
        InsertInMinHeap(heap, t, i, 0);
    }
    while (sorted_num < n)
    {
        MinHeapNode* min = PopFromMinHeap(heap);
        sorted[sorted_num] = min->val;
        sorted_num++;
        if (min->index + 1 < k)
            InsertInMinHeap(heap, t, min->arr_num, min->index + 1);
    }
}

int main()
{
    int t[10] = {10, 2, 3, 4, 5, 6, 9, 8, 7, 1};
    cout << "Liczba inwersji: " << MergeSort(t, 10) << endl;
    //   for(int i=0; i<10; i++){
    //      cout << t[i] << " ";
    //   }
    cout << endl;
    system("pause");
    return 0;
}
