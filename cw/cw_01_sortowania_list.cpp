#include <iostream>
using namespace std;

//Sortowanie bąbelkowe
void BubbleSort(int t[], int n)
{
    bool action = true;
    for (int i = 1; i < n and action == true; i++)
    {
        action = false;
        for (int j = i; j < n - 1; j++)
        {
            if (t[i] > t[i + 1])
            {
                swap(t[i], t[i + 1]);
                action = true;
            }
        }
    }
}

//Sortowanie przez wybieranie
void SelectionSort(int t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (t[j] < t[min])
                min = j;
        }
        swap(t[i], t[min]);
    }
}

//Sortowanie przez wstawianie
void InsertionSort(int t[], int n)
{
    for (int i = 1; i < n; i++)
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

//      Listy dwukierunkowe - Sortowania
//__________________________________________

struct node
{
    node *next;
    node *prev;
    int val;
};

void insert_wart(node *head, node *n)
{
    node *p = head;
    while (p->next != nullptr and p->next->val < n->val)
    {
        p = p->next;
    }
    n->prev = p;
    n->next = p->next;
    p->next = n;
    if (p->next != nullptr)
        p->next->prev = n;
}

node *insert(node *head, node *n)
{
    if (head == nullptr)
        return n;
    if (head->val > n->val)
    {
        n->next = head;
        head->prev = n;
        return n;
    }
    node *p = head;
    while (p->next != nullptr and p->next->val < n->val)
    {
        p = p->next;
    }
    n->prev = p;
    n->next = p->next;
    p->next = n;
    if (p->next != nullptr)
        p->next->prev = n;
}

node *remove_max_wart(node *head)
{
    node *max = head->next;
    node *p = head->next;
    while (p != nullptr)
    {
        if (p->val > max->val)
            max = p;
        p = p->next;
    }
    max->prev->next = max->next;
    if (max->next != nullptr)
        max->next->prev = max->prev;
    max->next = max->prev = nullptr;
    return max;
}

node *remove_max(node **head)
{
    node *p = *head;
    if (p->next == nullptr)
    {
        *head = nullptr;
        return p;
    }
    node *max = p;
    for (node *n = p; n != nullptr; n->next)
    {
        if (max->val < n->val)
        {
            max = n;
        }
    }

    if (max == p)
    {
        max->next->prev = nullptr;
        *head = max->next;
        max->next = nullptr;
        return max;
    }

    max->prev->next = max->next;
    if (max->next != nullptr) max->next->prev=max->prev;
    max->next=nullptr;
    max->prev=nullptr;
    return max;
}

//InsertionSort na liście dwukierunkowej
//-----
node* InsertionSort_wart(node* head){ //z wartownikiem
    node* p = new node;
    p->prev=p->next=nullptr;
    while(head->next!=nullptr){
        node* n=head->next;
        if(head->next!=nullptr){
            n->next->prev=n->prev;
        }
        head->next=n->next;
        n->next=n->prev=nullptr;
        p = insert(p,n);
    }
    return p;
}

node* InsertionSort(node* head){ //bez wartownika
    node* p = nullptr;
    while(head!=nullptr){
        node* n=head;
        head=head->next;
        if(head!=nullptr){
            head->prev=nullptr;
        }
        n->next=nullptr;
        p = insert(p,n);
    }
    return p;
}

// SelectionSort na liście jednokierunkowej z wqartownikiem

node* SelectionSort(node* head){
    node* sorted = new node;
    sorted->next=nullptr;
    node* tmp;
    while(head!=nullptr){
        tmp = remove_max_wart(head);
        tmp->next=sorted->next;
        sorted->next=tmp;
    }
    return sorted;
}

int main()
{

    cout << endl;
    system("pause");
    return 0;
}
