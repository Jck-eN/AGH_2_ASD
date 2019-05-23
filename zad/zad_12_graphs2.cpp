#include <iostream>
using namespace std;
const int n = 5;

enum Color{
    white, grey, black
};

/*1. 
Sciezka Hamiltona przechodzi przez wszystkie wierzchołki w grafie, przez kazdy dokładnie jeden raz.
Prosze zaimplementowac algorytm, który stwierdzi czy istnieje sciezka Hamiltona w acyklicznym
grafie skierowanym.

*/

void Topo_DFS_Visit(int Graph[n][n], int u, bool* visited, int* sorted, int& idx){
    visited[u]=true;
    for(int i=0; i<n; i++)
    {
        if(Graph[u][i] && u!=i && visited[i]==false)
        {
            Topo_DFS_Visit(Graph, i, visited, sorted, idx);
        }
    }
    sorted[idx--]=u;
}


bool TopoSort_DFS(int Graph[n][n]){
    int sorted[n] = {-1};
    int idx=n-1;
    bool visited[n] = {false};
    for(int i=0; i<n; i++)
    {
        if(!visited[i]) 
            Topo_DFS_Visit(Graph, i, visited, sorted, idx);
    }
    for(int i=0; i<n-1; i++)
    {
        if(Graph[sorted[i]][sorted[i+1]]==0)
            return false;
    }
    return true;
}


//-------------------------------------------------------

bool HamiltonFrom(int Graph[n][n], int u, int* visited, int depth){
    if(depth==n) return true;
    visited[u]=true;
    for(int i=0; i<n; i++){
        if(Graph[u][i] && u!=i && visited[i]==false){
            if(HamiltonFrom(Graph, i, visited, depth+1)) return true;
        }
    }
    visited[u]=false;
    return false;
}

bool HamiltonPath(int Graph[n][n]){
    int *visited = new int[n];

    for(int i=0; i<n; i++){
        visited[i] = false;
    }
    for(int i=0; i<n; i++){
        if(HamiltonFrom(Graph, i, visited, 1) == true) {
            delete[] visited;
            return true;
        }
    }
    return false;
}

/*2. Cykl Hamiltona o minimalnej sumie wag krawedzi nazywamy droga komiwojazera. Dane sa współrzedne
N punktów na płaszczyznie. Prosze zaimplementowac funkcje obliczajaca dolne ograniczenie
drogi komiwojazera.
Wskazówka: Jaki zwiazek ma długosc drogi komiwojazera z długoscia minimalnego drzewa rozpinajacego?
Droga hamiltona >= długość MST
*/

struct Edge{
    int a, b, val;
    Edge* next;
};


int FindSet(int x, int* parent, int n){
    if(parent[x]==x) return x;
    parent[x]=FindSet(parent[x], parent, n);
    return parent[x];
}

void MakeSets(int* parent, int n){
    for(int i=0; i<n; i++)parent[i]=i;
}

void Union(int x, int y, int* parent, int n){
    x=FindSet(x, parent, n);
    y=FindSet(y, parent, n);
    if(x==y)return;
    parent[y]=x;
}
void sort(Edge* e);

int KruskalSize(int Graph[n][n]){ //Główna funkcja
    int result=0;
    Edge* edges;
    int Z[n];
    MakeSets(Z, n);
    for(int i=0; i<n; i++){
        for(int j=0; i<n; j++){
            if(Graph[i][j]>0){
                Edge e ={i, j, Graph[i][j], nullptr}; 
                e.next=edges;
                edges = &e;
            }
        }
    }
    sort(edges);
    Edge* tmp = edges;
    for(int i=0; i<n-1;i++){ //n-1 krawędzi w drzewie
        do{                 //szukanie krawędzi która nie stworzy cyklu
            edges=edges->next;    //wierzchołki nie mogą być w jednej skł. spójnej
        } while (FindSet(edges->a, Z, n) == FindSet(edges->b, Z, n));
        result+=edges->val;      //Znaleziono - >dodawanie krawędzi do MST
        Union(edges->a, edges->b, Z, n);
    }
    return result;
}




int main(){
    int Graph[n][n]={
        {0,1,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
        {1,0,0,0,0},
        {0,1,0,1,0},
    };
    cout <<TopoSort_DFS(Graph);
    return 0;
}


