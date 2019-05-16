struct Cyclist{
    int id;
    int n_id;
};

struct betterCyclist{
    int id;
    int p_id;
    int n_id;
};

int hash(int kn){
    int p=0;
    while(kn!=0){
        p*=731;
        p+=kn%10;
        kn/=10;
    }
    return p;
}

struct HT{
    int size;
    betterCyclist* c;
};

int get(HT* ht, int id){
    int h = hash(id)%ht->size;
    int i=0;
    while(ht->c[h]->id!=id && i<=ht->size){
        h=(h+1)%ht->size;
        i++;
    }
    return h;
}

void insert(HT* ht, betterCyclist* bc){
    int h = hash(id)%ht->size;
    int i=0;
    while(ht->c[h].id==-1 && i<=ht->size){
        h=(h+1)%ht->size;
        i++;
    }
    ht->c[h]=bc;
    return;
}


int smallest_group(Cyclist cyclist[], int n){
    HT* cyclists = new HT;
    cyclists->size=2*n;
    cyclists->c = new betterCyclist[2*n];

    for(int i=0; i<n; i++){
        int h = hash(cyclist[i].id)%cyclists->size;
        HT->cyclist[]
    }
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
