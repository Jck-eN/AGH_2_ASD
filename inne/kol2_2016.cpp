struct SLNode {
    int value;
    int level;
    SLNode** next;
};

struct SkipList {
    SLNode* first;
    SLNode* last;
};

const int INF = 100000;

const int MAX_LEVEL;

SkipList merge(SkipList A, SkipList B){
    SkipList C;
    C.first=new SLNode;
    C.first->value=-INF;
    C.first->next = new SLNode*[MAX_LEVEL];
    SLNode* tmp_a; 
    SLNode* tmp_b;
    SLNode* tmp_c;
    for(int i=MAX_LEVEL-1; i>=0; i--){
        tmp_c=C.first;
        tmp_a=A.first->next[i];
        tmp_b=B.first->next[i];
        while(tmp_a->value!=INF and tmp_b->value!=INF){
            if(tmp_a->value<tmp_b->value){
                tmp_c->next[i]=tmp_a;
                tmp_c=tmp_c->next[i];
                tmp_a=tmp_a->next[i];
            }
            else{
                tmp_c->next[i]=tmp_b;
                tmp_c=tmp_c->next[i];
                tmp_b=tmp_b->next[i];
            }
        }
        if(tmp_a->value==INF){
            tmp_c->next[i]=tmp_b;
        }
        else{
            tmp_c->next[i]=tmp_a;
        }
    }
}




//--------------------------------------------

struct Cyclist {
    int id, n_id;
};
struct HTel{
    int id;
    int next;
    int prev;
};

struct HT{
    HTel* c;
    int size;
};

unsigned int hash(int n){
    unsigned int p=0;
    while(n>0){
        p*=731;
        p+=n;
    }
    return p;
}

void add(HT* ht, int id, int prev){
    int h = hash(id)%ht->size;
    while(ht->c[h].id<0) h=(h+1)%ht->size;
    ht->c[h].id=id;    
    ht->c[h].prev=prev;
}
int get(HT* ht, int id){
    int h = hash(id)%ht->size;
    while(ht->c[h].id!=id) h=(h+1)%ht->size;
    return h;
}



int smallestGroup(Cyclist cyclist[], int n){
    HT ht;
    ht.size=2*n;
    ht.c = new HTel[2*n];
    for(int i=0; i<2*n; i++){
        ht.c[i].id=ht.c[i].next=ht.c[i].prev=-1;
    }
    int* group = new int[n];
    for(int i=0; i<n; i++){
        group[i]=i;
        add(&ht, cyclist[i].id, i);
    }
    for(int i=0; i<n; i++){
        int next = get(&ht, cyclist[i].n_id);
        ht.c[next].prev=i;
    }

    int mingroup= n+10;
    int counter;
    for(int i=0; i<2*n; i++){
        if(ht.c[i].id!=-1 and ht.c[i].prev==-1){
            counter=0;
            int tmp=i;
            while(ht.c[tmp].next!=-1){
                int next_id = get(&ht, ht.c[tmp].next);
                counter++;
                tmp=next_id;
            }
        }
        mingroup=(mingroup<counter ? mingroup : counter);
    }
    return mingroup;
}