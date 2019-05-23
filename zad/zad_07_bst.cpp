#include <iostream>
using namespace std;

// ĆWICZENIA 7 - Jacek Nitychoruk
//---------------------------------------------
//Implementacja zmodyfikowanego drzewa BST

struct Data{
    int val;
};

struct node{
    node* parent;
    node* left;
    node* right;
    int key;
    Data* val;
    int leftElements;
};

void update_counter(node*, int);

node* find(node* head, int key){
    if( head==NULL || head->key==key) return head;
    else if(key < head->key) return find(head->left, key);
    else return find(head->right, key);
}

void insert(node* &head, int key, Data* data, node* parent=NULL){
    if(head==NULL){
        head=new node;
        head->key=key;
        head->val=data;
        head->parent=parent;
        head->left=NULL;
        head->right=NULL;
        head->leftElements=0;
        if(parent!=NULL){
            if(parent->key > head->key) parent->left=head;
            else parent->right=head;
        }
        update_counter(head->parent, head->key);
        return;
    }
    else if(key < head->key) return insert(head->left, key, data, head);
    else return insert(head->right, key, data, head);

}

void update_counter(node* p, int prev_key){
    if(p==NULL) return;
    if(p->key>prev_key) { //wywołany z lewego poddrzewa
        p->leftElements++;
    }
    update_counter(p->parent, p->key);
}

// --------------------------------------
// Funkcje właściwe

// Zadanie 1. Znalezienie i-tego co do wielkości elementu w drzewie BST.

node* nth_element(node* head, int n){
    if(head->leftElements+1==n) return head;
    if(head->leftElements>=n) return nth_element(head->left, n);
    else return nth_element(head->right, n-(head->leftElements+1));
}

//Zadanie 2. Wyznaczenie, którym co do wielkosci w drzewie jest zadany wezeł.

int which_int(node* p, int prev){
    if(p==NULL) return 1;
    if(p->key<prev) {//wywołany z prawego poddrzewa
        return p->leftElements+1+which_int(p->parent, p->key);
    }
    else return which_int(p->parent, p->key);
}
int which(node* p){
    if(p==NULL) return 0;
    return p->leftElements+which_int(p->parent, p->key);
}



int main()
{
    node* bst = NULL;
    insert(bst, 10, NULL);
    insert(bst, 5, NULL);
    insert(bst, 15, NULL);
    insert(bst, 12, NULL);
    insert(bst, 1, NULL);
    insert(bst, 8, NULL);
    insert(bst, 7, NULL);
    insert(bst, 9, NULL);
    
    for(int i=1; i<=8; i++){
        cout << which(nth_element(bst, i)) << ": ";
        cout << nth_element(bst, i)->key << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}
