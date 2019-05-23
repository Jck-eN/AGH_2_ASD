#include <iostream>
#include <queue>
using namespace std;

const int n = 100;

/*1. Proszę zaimplementować następujące algorytmy:
- Sprawdzanie czy graf jest dwudzielny
- Policzyć liczbę spójnych składowych w grafie
Graf jest reprezentowany jako macierz sąsiedztwa albo listy sąsiadów albo listy krawędzi.*/

/*
0. sposoby przechodzenia po sąsiadach w grafie: "for(v in adj[u])"

0a. Macierz incydencji
for(int i=0; i<n; i++){
    if(graph[u][i]){
        ... Code here ...
    }
}

0b. Listy sąsiadów

node* v = List[u];
while(v!=nullptr){
    ... Code here ...
    v=v->next;
}

0c. Listy krawędzi

edge* head;
while(head!=nullptr){
    if(head.first==u){
        ... Code here ...
    }
    head=head->next;
}
*/

//1a Czy jest dwudzielny

bool is_bipartite(int Graph[n][n], int start)
{
    int* side = new int[n];
    for(int i=0; i<n; i++)
    {
        side[i] = 0;
    }
    queue<int> Q;
    Q.push(start);
    side[start]=1;
    while(!Q.empty)
    {
        int u=Q.front;
        Q.pop;
        for(int i=0; i<n; i++)
        {
            if(Graph[u][i])
            {
                if(side[i]==0){
                    side[i]=-side[u];
                    Q.push(i);
                }
                else if(side[i]==side[u]) 
                {
                    delete[] side;
                    return false;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        if(side[i]==0){
            delete[] side;
            return false;
        }
    }
    delete[] side;
    return true;
}

//Connected components

void Connected(int Graph[n][n], bool* visited, int v){
    visited[v]=true;
    for(int i=0; i<n; i++){
        if(Graph[v][i] && !(visited[v])){
            Connected(Graph, visited, i);
        }
    }
}


int Connected_components(int Graph[n][n]){
    bool *visited = new bool[n];
    for(int i=0; i<n; i++){
        visited[i] = false;
    }
    int res=0;
    for(int i=0; i<n; i++){
        if(visited[i]==false){
            Connected(Graph, visited, i);
            res++;
        } 
    }
    return res;
}

//Znajdowanie ujścia w grafie (universal sink)
/*
2. Mówimy, że wierzchołek t w grafie skierowanym jest ujściem, jeśli:
- z każdego innego wierzchołka v istnieje krawędź z v do t,
- nie istnieje żadna krawędź wychodząca z t.
Podać algorytm znajdujący ujście (jeśli istnieje) przy macierzowej reprezentacji grafu.
*/

bool is_sink(bool Graph[n][n], int k){
    for(int i=0;i<n; i++){
        if(Graph[k][i]) return false;
    }    
    for(int i=0;i<n; i++){
        if(!Graph[i][k] && i!=k) return false;
    }
    return true;
}

int has_sink(bool Graph[n][n]){
    int i=0, j=0;
    while(i<n && j<n){
        if(Graph[i][j]==1) i++;
        else j++;
    }
    if(i>=n) return -1;
    else if(!is_sink(Graph, i)) return -1;
    else return i;
}