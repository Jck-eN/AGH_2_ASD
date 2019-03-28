#include <iostream>
using namespace std;

struct node
{
    node *next;
    node *prev;
    int val;
};

node *odetnij(node *head)
{
    node *p = head;
    while (p->next != nullptr and p->next->val >= p->val)
        p = p->next;
    node *q = p->next;
    if (q != nullptr)
        q->prev = nullptr;
    p->next = nullptr;
    return q;
}

node *MergeLists(node *l1, node *l2)
{
    node *head = NULL;
    node *i = head;
    while (l1 != NULL and l2 != NULL)
    {
        if (l1->val > l2->val)
        {
            if (head == nullptr)
                head = i = l2;
            else
            {
                i->next = l2;
                l2->prev = i;
                i = i->next;
            }
            l2 = l2->next;
        }
        else
        {
            if (head == nullptr)
                head = i = l1;
            else
            {
                i->next = l1;
                l1->prev = i;
                i = i->next;
            }
            l1 = l1->next;
        }
        if (l1 != nullptr)
        {
            i->next = l1;
            l1->prev = i;
        }
        if (l2 != nullptr)
        {
            i->next = l2;
            l2->prev = i;
        }
    }
    return head;
}

node *MergeNaturalListsSort(node *head)
{
    node *sorted;
    node *end;
    node *s1, *s2, *q;
    while (true)
    {
        sorted = nullptr;
        s1 = head;
        head = odetnij(head);
        if (head == nullptr)
        {
            if (sorted == nullptr)
                return s1; //Lista jest posortowana
            else
            {
                end->next = s1;
                s1->prev = end;
                head = sorted;
                sorted = end = nullptr;
            }
        }
        else
        {
            s2 = head;
            head = odetnij(head);
            q = MergeLists(s1, s2);
            if (sorted == nullptr)
                sorted = q;
            else{
                end->next=q;
                q->prev=end;
            }
            while(q->next!=nullptr)q=q->next;
            end=q;
            if(head==nullptr){
                head=sorted;
                end=nullptr;
            }
        }
    }
}
struct heap{};

struct FMedian{
    heap* maxHeap;
    heap* minHeap;
};
int getMin(heap* h);
int getMax(heap* h);
int removeMin(heap* h);
int removeMax(heap* h);
void insertMinHeap(heap* h, int x);
void insertMaxHeap(heap* h, int x);
int size(heap* h);

int RemoveMedian(FMedian* fm){
    if(size(fm->maxHeap)>size(fm->minHeap)) return removeMax(fm->maxHeap);
    else return removeMin(fm->minHeap);
}

void insert(FMedian* fm, int x){
    if(x<getMax(fm->maxHeap)) {
        insertMaxHeap(fm->maxHeap, x);
        if(size(fm->maxHeap) == size(fm->minHeap+2))
            insertMinHeap(fm->minHeap, removeMax(fm->maxHeap));
    }
    else{
        insertMinHeap(fm->minHeap, x);
        if(size(fm->minHeap) > size(fm->maxHeap))
            insertMaxHeap(fm->maxHeap, removeMin(fm->minHeap));
    }
        
}

//--------------
//Quicksort

int partition(int tab[], int p, int q);

void QSort(int tab[], int p, int q){
    if(p<q){
        int r=partition(tab, p, q);
        QSort(tab, p, r-1);
        QSort(tab, r+1, q);
    }
    return;
}

void QSortLogNRecurrent(int tab[], int p, int q){
    int r;
    while(p<q){
        r=partition(tab, p, q);
        if(r-p<q-r){
            QSortLogNRecurrent(tab, p, r-1);
            p=r+1;
        }
        else{
            QSortLogNRecurrent(tab, r+1, q);
            q=r-1;
        }
    }
    QSortLogNRecurrent(tab, r+1, q);

    return;
}


int main()
{

    cout << endl;
    system("pause");
    return 0;
}
