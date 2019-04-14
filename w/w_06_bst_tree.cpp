#include <iostream>
using namespace std;

struct Data{
    int val;
};

struct node{
    node* left;
    node* right;
    node* parent;
    int key;
    Data val;
};

node* find(node* p, int k){
    while(p!=NULL and p->key != k){
        if(k< p->key) p=p->left;
        else p=p->right;
    }
    return p;
}

node* find_rec(node* p, int k){
    if(p==NULL or p->key == k) return p;
    if(k<p->key) return find_rec(p->left, k);
    return find_rec(p->right, k);
}

void insert(node* &p, int k){
    if(p==NULL){
        p=new node;
        p->left=p->right=p->parent=NULL;
        p->key = k;
        return;
    }
    else if(k<p->key) insert(p->left, k);
    else insert(p->right, k);
}

node* min(node* p){
    while(p->left!=NULL){
        p=p->left;
    }
    return p;
}

node* max(node* p){
    while(p->right!=NULL){
        p=p->right;
    }
    return p;
}

node* nastepnik(node* p){
    if(p->right!=NULL) return min(p->right);
    node* q=p->parent;
    while(q!=NULL and q->right==p){
        p=q;
        q=q->parent;
    }
    return q;
}



int main()
{
    
    
    cout << endl;
    system("pause");
    return 0;
}
