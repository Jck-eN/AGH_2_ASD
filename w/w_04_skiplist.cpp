#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
using namespace std;

//--------------
// WYKŁAD 4 - SKIPLISTA - prof. Faliszewski
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

void printList(Skiplist* SL){
    for(int i=SL->maxlevel; i>=0; i--){
        cout << "poziom " << i << ": ";
        SLNode* p=SL->first;
        while(p->next[i]!=NULL){
            cout << p->key << " -> ";
            p=p->next[i];
        }
        cout << p->key << endl;
        string q = "test";
    }
}


int main()
{
    
    srand(time(NULL));
    random();
    
    Skiplist* SL = new Skiplist(6);
    for(int i=0; i < 100; i++){
        insert(SL, rand());
    }
    printList(SL);

    cout << endl;
    system("pause");
    return 0;
}
