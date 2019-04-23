// Implementacja drzwiasta zbiorów
//--------------------------------
struct node{
    node* parent;
    int val;
    int rank;
};

node* FindSet(node* p){
    if(p!=p->parent) p->parent=FindSet(p->parent);
    return p->parent;
}

node* MakeSet(int x){
    node* p = new node;
    p->val=x;
    p->parent=p;
    p->rank=1;
    return p;
}

void Union(node* x, node* y){
    x=FindSet(x);
    y=FindSet(y);
    if(x==y)return;
    if(x->rank>y->rank){
        y->parent=x;
    }
    else {
        x->parent=y;
        if(x->rank==y->rank){
            y->rank++;
        }
    }
}

// Implementacja tablicowa zbiorów
//--------------------------------
const int N=100;
int parent[N];
int rank[N];


int FindSet2(int x){
    if(parent[x]==x) return x;
    parent[x]=FindSet2(parent[x]);
    return parent[x];
}

void MakeSets2(int x){
    for(int i=0; i<x; i++){parent[i]=i; rank[i]=1;}
}

void Union2(int x, int y){
    x=FindSet2(x);
    y=FindSet2(y);
    if(x==y)return;
    if(rank[x]>rank[y]){
        parent[y]=x;
    }
    else {
        parent[x]=y;
        if(rank[x]==rank[y]){
            rank[y]++;
        }
    }
}