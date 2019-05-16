#include <iostream>

const int n = 50;

using namespace std;

struct Set{
    Set* left;
    Set* right;
    bool is_end = false;
};

void addToSet(string a, Set* s){
    Set* tmp=s;
    for(int i=0; i<a.length; i++){
        if(a[i]=='1'){
            if(tmp->left==nullptr){
                Set* p = new Set;
                p->is_end=false;
                p->left=p->right=nullptr;
                tmp->left=p;
            }
            tmp=tmp->left;
        }
        else{
            if(tmp->right==nullptr){
                Set* p = new Set;
                p->is_end=false;
                p->right=p->right=nullptr;
                tmp->right=p;
            }
            tmp=tmp->right;
        }
    }
    tmp->is_end=true;
}

bool contains(Set a, string s){
    Set* tmp=&a;
    for(int i=0; i<s.length; i++){        
        if(s[i]=='1'){
            if(tmp->left==nullptr){
                return false;
            }
            tmp=tmp->left;
        }
        else{
            if(tmp->right==nullptr)
                return false;
            tmp=tmp->right;
        }
    }
    return tmp->is_end;
}

Set createSet(string A[], int n){
    Set s;
    s.left=s.right=nullptr;
    for(int i=0; i<n; i++){
        addToSet(A[i], &s);
    }
    return s;
}

//-------------------------------------------------------------

struct Edge {
    int u, v; // u < v
    Edge* next;
};

struct node{
    node* next;
    int val;
};

bool exists(node* root, int x){
    while(root!=nullptr){
        if(root->val==x) return true;
        root=root->next;
    }
    return false;
}

void add(node* &root, int val){
    node* tmp = new node;
    tmp->next=root;
    tmp->val=val;
    root=tmp;
}


bool Euleran(Edge* E){
    int counter[n] = {0};
    node* vertex[n];
    for(int i=0; i<n; i++){
        vertex[i]->val=0;
        vertex[i]->next=nullptr;
    }
    Edge* tmp = E;
    while(tmp!=nullptr){
        if(!exists(vertex[tmp->u], tmp->v)) {
            add(vertex[tmp->u], tmp->v);
            add(vertex[tmp->v], tmp->u);
            counter[tmp->u]++;
            counter[tmp->v]++;
        }
        tmp=tmp->next;
    }
    for(int i=0; i<n ; i++){
        if(counter[i]%2==1) return false;
    }
    return true;
}

//---------------------------------------------------------