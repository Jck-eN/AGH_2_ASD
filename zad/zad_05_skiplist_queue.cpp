#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

// ĆWICZENIA 5 - Jacek Nitychoruk
//---------------------------------------------
// ZADANIE 1 - dodawanie do skiplisty         |
//---------------------------------------------
double random(){
    return(double)rand()/RAND_MAX;
}

int GetLevel(int max_lvl){
    int lvl=0;
    while(random()<(0.5)){
        lvl++;
    };
    return lvl<=max_lvl ? lvl : max_lvl;
}

struct SLNode{
    int key;
    SLNode** next;

    SLNode(int val = 0){
        key=val;
    }
};
struct Skiplist{
    int maxlevel;
    SLNode* first;
    SLNode* last;

    Skiplist(int lvl){
        maxlevel=lvl;
        last = new SLNode(INT_MAX);
        last->next = new SLNode*[maxlevel+1];
        for(int i=0; i<=maxlevel; i++) last->next[i]=NULL;

        first = new SLNode(INT_MIN);
        first->next = new SLNode*[maxlevel+1];
        for(int i=0; i<=maxlevel; i++) first->next[i]=last;

    }
};

SLNode* find(Skiplist* SL, int key){
    SLNode* p=SL->first;
    for(int lvl=SL->maxlevel; lvl>=0; lvl--){
        while(p->next[lvl]->key < key){
            p=p->next[lvl];
        }
    }
    p=p->next[0];
    if(p->key==key) return p;
    return NULL;
}

bool insert(Skiplist* SL, int key){
    int insert_lvl = GetLevel(SL->maxlevel);
    SLNode* newItem = new SLNode;
    newItem->key = key;
    newItem->next = new SLNode*[insert_lvl+1];


    SLNode** prev = new SLNode*[insert_lvl+1]; //wskaźniki na node'y do podłączenia do nowego node'a
    SLNode* p=SL->first;
    for(int lvl=SL->maxlevel; lvl>=0; lvl--){
        while(p->next[lvl]->key < key){
            p=p->next[lvl];
        }
        if(lvl<=insert_lvl) prev[lvl]=p;
    }
    if(p->next[0]->key==key){
        delete[] prev;
        return false;
    }
    for(int i=0; i<=insert_lvl; i++){
        newItem->next[i]=prev[i]->next[i];
        prev[i]->next[i]=newItem;
    }
    delete[] prev;
    return true;
}

//---------------------------------------------
// ZADANIE 2 - kolejka na dwóch stosach       |
//---------------------------------------------


struct Stack{
    int* T;
    int size;
    int top;

    Stack(int s){
        size=s;
        T = new int[size];
        top=-1;
    }
};

int pop_stack(Stack*);
void push_stack(Stack*, int val);
bool is_stack_empty(Stack*); 

struct TwoStacksQueue{
    Stack* Stack1;
    Stack* Stack2;
};

bool is_empty(TwoStacksQueue* q){
    return is_stack_empty(q->Stack1) and is_stack_empty(q->Stack2);
}
void push(TwoStacksQueue* q, int val){
    push_stack(q->Stack1, val);
}

int pop(TwoStacksQueue* q){
    if(!is_stack_empty(q->Stack2)){
        return pop_stack(q->Stack2);
    }
    while(!is_stack_empty(q->Stack1)){
        push_stack(q->Stack2, pop_stack(q->Stack1));
    }
    return pop_stack(q->Stack2);
}
