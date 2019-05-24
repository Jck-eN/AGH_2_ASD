//Zadanie 1+2. Dijsktra + najkrótsze ścieżki na podst. parenta

#include <iostream>
#include <climits>
using namespace std;

const int n = 9; 

void print_path(int parent[], int v){
    if(parent[v]==-1) {
        return;
    }
    print_path(parent, parent[v]);
    cout << v << " -> ";
}

int min_dist(int* d, int* visited){
    int min=INT_MAX, min_idx;
    for(int v=0; v<n-1; v++){
        if(visited[v]==false && d[v]<=min) 
        {
            min=d[v];
            min_idx=v;
        }
    }
    return min_idx;
}


void dijkstra(int G[n][n], int src){
    int d[n];
    int visited[n];
    int parent[n];

    for(int i=0; i<n; i++){
        d[i]=INT_MAX;
        visited[i]=false;
        parent[i]=-1;
    }

    d[src]=0;

    for(int i=0; i<n-1; i++){
        int u = min_dist(d, visited);
        visited[u]=true;
        for(int v=0; v<n; v++){
            if(!visited[v] && G[u][v])
            {
                if(d[v]>d[u]+G[u][v]) 
                {
                    d[v]=d[u]+G[u][v];
                    parent[v]=u;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout << i << ": " << d[i] << " | ";
        print_path(parent, i);
        cout << endl;
    }
}

//Zadanie 3. - nieobowiązkowe


void dijkstra_2(int G[n][n], int src){
    int d[n];
    int visited[n];
    int parent[n];
    int driver[n];

    for(int i=0; i<n; i++){
        d[i]=INT_MAX;
        visited[i]=false;
        parent[i]=-1;
        driver[i]=-1;
    }

    d[src]=0;
    driver[src]=0;

    for(int i=0; i<n-1; i++){
        int u = min_dist(d, visited);
        visited[u]=true;
        for(int v=0; v<n; v++){
            if(!visited[v] && G[u][v])
            {
                if(d[v]>=d[u]+G[u][v] && driver[u]==0)
                {
                    d[v]=d[u]+G[u][v];
                    parent[v]=u;
                    driver[v]=1;
                }
                else if(d[v]>d[u] && driver[u]==1){
                    d[v]=d[u];
                    parent[v]=u;
                    driver[v]=0;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout << i << ": " << d[i] << " | ";
        print_path(parent, i);
        cout << endl;
    }
}


int main()
{
    int G[n][n] = {{0, 4, 0, 0, 0, 0, 0, 8, 0}, 
                    {4, 0, 8, 0, 0, 0, 0, 11, 0}, 
                    {0, 8, 0, 7, 0, 4, 0, 0, 2}, 
                    {0, 0, 7, 0, 9, 14, 0, 0, 0}, 
                    {0, 0, 0, 9, 0, 10, 0, 0, 0}, 
                    {0, 0, 4, 14, 10, 0, 2, 0, 0}, 
                    {0, 0, 0, 0, 0, 2, 0, 1, 6}, 
                    {8, 11, 0, 0, 0, 0, 1, 0, 7}, 
                    {0, 0, 2, 0, 0, 0, 6, 7, 0} 
                    }; 
    dijkstra(G, 3);
    cout << endl;
    dijkstra_2(G, 3);
    
    cout << endl;
    system("pause");
    return 0;
}