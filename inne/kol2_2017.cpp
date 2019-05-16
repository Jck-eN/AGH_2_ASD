struct HT{
    int* table;
    int size;
};

int hash(int x);

void enlarge(HT* ht){
    HT* ht2 = new HT;
    ht2->size=ht->size*2;
    ht2->table=new int(ht2->size);
    for(int i=0; i<ht2->size; i++){
        ht2->table[i]=-1;
    }
    for(int i=0; i<ht->size; i++){
        if(ht->table[i]>=0){
            int h = hash(ht->table[i]);
            h=h%ht2->size;
            if(ht2->table[h]<0){
                ht2->table[h]=ht->table[i];
                ht->table[i]=-1;
            }
        }
    }    
    for(int i=0; i<ht->size; i++){
        if(ht->table[i]>=0){
            int h = hash(ht->table[i]);
            h=h%ht2->size;
            while(ht2->table[h]>=0){
                h=(h+1)%ht2->size;
            }
            ht2->table[h]=ht->table[i];
            ht->table[i]=-1;
        }
    }
    delete[] ht->table;
    delete ht;
}

//------------------------------------------

struct HuntingList {
    HuntingList* next; // nastepny element listy
    int predator; // numer pokemona, który poluje
    int prey;
};

struct node{
    node* next;
    int num;
};

struct Pokemon{
    int id;
    node* my_prey;
    node* my_predator;
    bool released;
};

void releaseHunter(int hunter, Pokemon* p, int n, int* sorted, int* iterator){
    if(p[hunter].released) return;
    node* tmp=p[hunter].my_prey;
    int counter=0;
    while(tmp!=nullptr){
        if(p[tmp->num].released) counter++;
        if(counter==2){
            p[hunter].released=1;
            sorted[*iterator]=hunter;
            iterator++;
        }
        tmp=tmp->next;
    }
    if(counter==2){
        tmp=p[hunter].my_predator;
        while(tmp!=nullptr){
            releaseHunter(tmp->num, p, n, sorted, iterator);
            tmp=tmp->next;
        }
    }
}

int* releaseThemAll (HuntingList* list, int n){
    Pokemon* p = new Pokemon[n];
    int* sorted = new int[n];
    int iterator=0;
    for(int i=0; i<n; i++){
        sorted[i]=-1;
        p[i].id=i;
        p[i].my_predator=nullptr;
        p[i].my_prey=nullptr;
        p[i].released=false;
    }
    while(list!=nullptr){
        node* pred = new node;
        pred->num=list->predator;      

        node* prey = new node;
        prey->num=list->prey;

        prey->next=p[list->predator].my_prey;
        p[list->predator].my_prey=prey;

        pred->next=p[list->predator].my_predator;
        p[list->prey].my_predator=pred;

        list=list->next;
    }
    for(int i=0; i<n; i++){
        if(p[i].my_prey==nullptr){
            sorted[iterator]=i;
            p[i].released=1;
            iterator++;
        }
    }
    for(int i=0; i<n; i++){
        if(!p[i].released){
            releaseHunter(i, p, n, sorted, &iterator);
        }
    }
    if(sorted[n-1]==-1) throw "error"; 
    for(int i=0; i<n; i++){
        node* tmp1=p[i].my_prey;
        node* tmp=tmp1;
        while(tmp!=nullptr){
            tmp1=tmp1->next;
            delete tmp;
            tmp=tmp1;
        }        
        node* tmp1=p[i].my_prey;
        node* tmp=tmp1;
        while(tmp!=nullptr){
            tmp1=tmp1->next;
            delete tmp;
            tmp=tmp1;
        }
    }
    delete[] p;
    return sorted;

}