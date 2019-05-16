#include <iostream>

struct SkipList{
    int heigth=10;
    SLNode* first;
    SLNode* last;
};

struct SLNode{
    int val;
    SLNode** next;
    int height;
};

int get_height(int max_height){
    int h=0;
    while(std::rand()%2) h++;
    return h;
}

void insert(SkipList* SL, int i){
    int h = get_height(SL->heigth);
    SLNode* p = new SLNode;
    p->height=h;
    p->next = new SLNode*[h];
    SLNode* tmp=SL->first;
    for(int i=h; i>=0; i--){
        while(tmp->next[i]->val<i){
            tmp=tmp->next[i];
        }
        p->next[i]=tmp->next[i];
        tmp->next[i]=p;
    }
}
//-----------------------------------------

const int n=10;
const int m=15;

void can_sail(bool access[n][m], int A[n][m], int x, int y, int &T){
    if (x>=0 and y>=0 and x<n and y < n and access[x][y]==false and A[x][y]>T){
        access[x][y]=true;
        can_sail(access, A, x+1, y, T);
        can_sail(access, A, x-1, y, T);
        can_sail(access, A, x, y-1, T);
        can_sail(access, A, x, y+1, T);
    } 
}

bool map(int A[n][m], int T){
    bool accessible[n][m] = {{false}};
    can_sail(accessible, A, 0, 0, T);
    return accessible[n-1][m-1];
}