#include <iostream>
#include <queue>
#include <climits>
using namespace std;


const int n = 100; // liczba wierzchołków
const int m = 1000; // liczba krawędzi

enum Color{
    white, grey, black
};

/*MOSTY W GRAFACH NIESKIEROWANYCH*/ 

void DFS(int Graph[n][n]){
    int *parent = new int[n];
    Color* color = new Color[n];
    int *d = new int[n];
    int *t = new int[n];
    int *low = new int[n];

    for(int i=0; i<n; i++){
        color[i] = white;
        parent[i]=-1;
        d[i]=INT_MAX;
        t[i]=INT_MAX;
    }
    int time=0;
    DFS_Visit(Graph, 0, parent, color, d, t, time, low);
    for(int i=1; i<n; i++){
        if(d[i]==low[i]) cout << "Most: " << i << "--" << parent[i] << endl;
    }

    delete[] parent;
    delete[] color;
    delete[] d;
    delete[] t;
    delete[] low;
}
void DFS_Visit(int Graph[n][n], int u, int* parent, Color* color, int* d, int* t, int &time, int* low){
    color[u]=grey;
    time++;
    d[u]=time;
    int* relation=new int[n] {0};
    relation[parent[u]]=-1;
    for(int i=0; i<n; i++){
        if(Graph[u][i] && u!=i && color[i]==white){
            parent[i]=u;
            relation[i]=1;
            DFS_Visit(Graph, i, parent, color, d, t, time, low);

        }
    }
  //  min(Graph,u,parent, color)
    int min = d[u];

    for(int i=0; i<n; i++){
        if(Graph[u][i] && u!=i && relation[i]==1 && low[i] < min) min=low[i];
        if(Graph[u][i] && u!=i && relation[i]==0 && low[i] < min) min=d[i];
    }
    low[u]=min;
    color[u]=black;

    delete[] relation;

    time++;
    t[u]=time;
}