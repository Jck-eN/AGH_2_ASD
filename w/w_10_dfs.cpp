#include <iostream>
#include <queue>
#include <climits>
using namespace std;


//Implementacja grafów:

const int n = 100; // liczba wierzchołków
const int m = 1000; // liczba krawędzi

// 1. Lista krawędzi:

struct Edge{
    int v1;
    int v2;
    Edge* next;
};

Edge* Graph;

// 2. Macierz sąsiedztwa:

bool Graph[n][n];

// 3a. Listy sąsiadów na listach:

struct Node{
    int idx;
    Node* next;
};

Node* Vertex[n];


// 3b. Listy sąsiadów na tablicy:

int head[n+1];
int next[m];

enum Color{
    white, grey, black
};

//--------------------------------------
//Przeszukiwanie grafu wgłąb - DFS
//np. macierz sąsiedztwa


void DFS(int Graph[n][n]){
    int *parent = new int[n];
    Color* color = new Color[n];
    int *d = new int[n];
    int *t = new int[n];

    for(int i=0; i<n; i++){
        color[i] = white;
        parent[i]=-1;
        d[i]=INT_MAX;
        t[i]=INT_MAX;
    }
    int time=0;
    for(int i=0; i<n; i++){
        if(color[i]==white) DFS_Visit(Graph, i, parent, color, d, t, time);
    }
    delete[] parent;
    delete[] color;
    delete[] d;
    delete[] t;
}
void DFS_Visit(int Graph[n][n], int u, int* parent, Color* color, int* d, int* t, int &time){
    color[u]=grey;
    time++;
    d[u]=time;
    for(int i=0; i<n; i++){
        if(Graph[u][i] and u!=i and color[i]==white){
            parent[i]=u;
            DFS_Visit(Graph, i, parent, color, d, t, time);
        }
    }
    color[u]=black;
    time++;
    t[u]=time;
}

//Sortowanie topologiczne
//-----------------------

struct Topo_node{
    int num;
    Topo_node* next;
};

Topo_node* TopoSort_DFS(int Graph[n][n]){
    Topo_node* res =NULL;

    Color* color = new Color[n];

    for(int i=0; i<n; i++){
        color[i] = white;
    }
    int time=0;
    for(int i=0; i<n; i++){
        if(color[i]==white) Topo_DFS_Visit(Graph, i, color, res);
    }
    delete[] color;
    return res;
}

void Topo_DFS_Visit(int Graph[n][n], int u, Color* color, Topo_node* &res){
    color[u]=grey;
    for(int i=0; i<n; i++){
        if(Graph[u][i] and u!=i and color[i]==white){
            Topo_DFS_Visit(Graph, i, color, res);
        }
    }
    color[u]=black;
    Topo_node* tmp = new Topo_node;
    tmp->num=u;
    tmp->next=res;
    res=tmp;
}

//Cykl Eulera
//---------------

struct Euler_node{
    int num;
    Euler_node* next;
};

Euler_node* Euler(int Graph[n][n]){
    Euler_node* res =NULL;

    Color* color = new Color[n];

    for(int i=0; i<n; i++){
        color[i] = white;
    }
    int time=0;
    for(int i=0; i<n; i++){
        if(color[i]==white) Euler_DFS_Visit(Graph, i, color, res);
    }
    delete[] color;
    return res;
}

void Euler_DFS_Visit(int Graph[n][n], int u, Color* color, Euler_node* &res){
    color[u]=grey;
    for(int i=0; i<n; i++){
        if(Graph[u][i] and u!=i and color[i]==white){
            Graph[u][i] = 0;                        //usuń przetworzone krawędzie
            Euler_DFS_Visit(Graph, i, color, res);
        }
    }
    color[u]=black;
    Euler_node* tmp = new Euler_node;
    tmp->num=u;
    tmp->next=res;
    res=tmp;
}

//Silnie spójne składowe

//DFS - czasy przetworzenia
//transpozycja grafu
//DFS w kolejności malejących czasów przetworzenia

bool compare(int a, int b)
{
	return a>b; //domyślnie a<b
}

int Count_strongly_connected_compontents(int Graph[n][n]){
    int *t = new int[n];
    SCC_DFS(Graph, t);
    sort(t, t+n, compare);
    int res = SCC_DFS_next(Graph, t);
    delete[] t;
    return res;
}

int SCC_DFS_next(int Graph[n][n], int t[n]){
    Color* color = new Color[n];
    int res=0;
    for(int i=0; i<n; i++){
        color[i] = white;
        t[i]=INT_MAX;
    }
    int time=0;
    for(int i=0; i<n; i++){
        if(color[t[i]]==white) {
            SCC_DFS_Visit_next(Graph, t[i], color, t);
            res++;
            }
    }
    delete[] color;
    return res;
}
void SCC_DFS_Visit_next(int Graph[n][n], int u, Color* color, int t[n]){
    color[u]=grey;
    for(int i=0; i<n; i++){
        if(Graph[u][t[i]] and u!=t[i] and color[t[i]]==white){
            SCC_DFS_Visit_next(Graph, t[i], color, t);
        }
    }
    color[u]=black;
}


void SCC_DFS(int Graph[n][n], int t[n]){
    Color* color = new Color[n];

    for(int i=0; i<n; i++){
        color[i] = white;
        t[i]=INT_MAX;
    }
    int time=0;
    for(int i=0; i<n; i++){
        if(color[i]==white) SCC_DFS_Visit(Graph, i, color, t, time);
    }
    delete[] color;
}
void SCC_DFS_Visit(int Graph[n][n], int u, Color* color, int* t, int &time){
    color[u]=grey;
    time++;
    for(int i=0; i<n; i++){
        if(Graph[u][i] and u!=i and color[i]==white){
            SCC_DFS_Visit(Graph, i, color, t, time);
        }
    }
    color[u]=black;
    time++;
    t[u]=time;
}