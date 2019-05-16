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

//--------------------------------------
//Przeszukiwanie grafu wszerz - BFS
//np. macierz sąsiedztwa

enum Color{
    white, grey, black
};

void BFS(int Graph[n][n], int start){
    int *parent = new int[n];
    Color *color = new Color[n];
    int *d = new int[n];
    for(int i=0; i<n; i++){
        parent[i]=-1;
        d[i]=INT_MAX;
        color[i]=white;
    }
    color[start] = grey;
    d[start]=0;
    queue<int> Q;
    Q.push(start);
    while(!Q.empty){
        int u=Q.front;
        Q.pop;
        for(int i=0; i<n; i++){
            if(Graph[u][i] and color[i]==white){
                color[i]=grey;
                d[i]=d[u]+1;
                parent[i]=u;
                Q.push(i);
            }
        }
        color[u]=black;
    }


//--------------------
    delete[] parent;
    delete[] color;
    delete[] d;
}
