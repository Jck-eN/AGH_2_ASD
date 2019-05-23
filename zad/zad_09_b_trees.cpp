// ĆWICZENIA 9 - Jacek Nitychoruk
//---------------------------------------------

//1. Dana jest tablica bool A[N][N]; Gracz początkowo znajduje się na (zadanej) pozycji(x, y),
//dla której zachodzi A[y][x] == true. Z danej pozycji wolno bezpośrednio przejść jedynie na pozycję,
//której dokładnie jedna współrzędna różni się o 1, oraz której wartość w tablicy A wynosi true.
//Proszę napisać funkcję obliczający do ilu różnych pozycji może dojść gracz startując z zadanej pozycji(x, y).

#include <climits>
#include <iostream>

using namespace std;

int get_parent(int a, int* parent){
	if(parent[a] == a)return a;
	else return parent[a] = get_parent(parent[a], parent);
}

void union_set(int a, int b, int* parent){
	int pa = get_parent(a, parent);
	int pb = get_parent(b, parent);
	if(pa==pb)return;
	parent[pb] = pa;
}

void check_and_union(int n, int** A, int xp, int yp, int x, int y, int* parent){
	if(xp<0 || xp>=n || yp<0 || yp>=n || A[xp][yp] != 1)return;

	union_set(x*n+y, xp*n+yp, parent);
}

int count_neighbors(int n, int** A, int xs, int ys){
	int* parent = new int[n*n];

	for(int i=0;i<n*n;i++){
		parent[i] = i;
	}

	for(int i=0;i<n*n;i++){
		int x = i/n; // i = x*n + y, y<n
		int y = i - x*n;

		if(A[x][y]==1){
			check_and_union(n, A, x+1, y, x, y, parent);
			check_and_union(n, A, x-1, y, x, y, parent);
			check_and_union(n, A, x, y+1, x, y, parent);
			check_and_union(n, A, x, y-1, x, y, parent);
		}
	}

	int p = get_parent(xs*n+ys, parent);
	int res=0;

	for(int i=0;i<n*n;i++){
		int pp = get_parent(i, parent);
		if(pp == p)res++;
		//cout<<parent[i]<<" ";
	}
	//cout<<endl;

	return res-1;
}

/*2. Dana jest struktura węzła drzewa B-tree przechowującego unikalne klucze:
struct node {
int n; // liczba kluczy zawarta w węźle
int key[N]; // tablica kluczy w węźle
node* child[N+1] // wskaźniki do synów węzła
bool leaf; // czy węzeł jest liściem
};
Proszę napisać funkcję bool is_b_tree(node* p); sprawdzającą czy
wskaźnik p wskazuje na poprawne drzewo b-tree.
*/
const int N = 5;

struct node {
	int n; 				// liczba kluczy zawarta w węźle
	int key[N]; 		// tablica kluczy w węźle
	node* child[N+1]; 	// wskaźniki do synów węzła
	bool leaf; 			// czy węzeł jest liściem
};

bool is_b_tree(node* p){
	int leaves_lvl=-1;
	int lvl=1;
	int tmp=INT_MIN;
	return is_b_tree_int(p, tmp, leaves_lvl, lvl, true);
}

bool is_b_tree_int(node* p, int& val, int& leaves_lvl, int lvl, bool is_root){
	int i=0;
	if(is_root && p->child[1]==nullptr) return false; //root must have at least 2 children

	if(p->leaf==true) {
		
		if(leaves_lvl==-1) leaves_lvl=lvl;		//all leaves must be at the same level
		else if(lvl!=leaves_lvl) return false;

		for(i=0; i<p->n; i++){
			if(p->key[i]>=val) val=p->key[i];
			else return false;
		}
	}
	else{
		
		if(p->n*2<N && is_root==false) return false; //middle nodes must have at least N/2 values

		for(i=0; i<p->n; i++){
			if (p->child[i]!=nullptr && is_b_tree_int(p->child[i],val, leaves_lvl, lvl+1, false)==false) return false;
			if(p->key[i]>=val) val=p->key[i];
			else return false;
		}
		if (p->child[i]!=nullptr && is_b_tree_int(p->child[i+1], val, leaves_lvl, lvl+1, false)==false) return false;
	}
	return true;
}

//--------------------------------------------------------------------

int main(){

    int n;

    cin>>n;

    int** A = new int*[n];
	for(int i=0; i<n; i++){
		A[i] = new int[n];
	}

    for(int i = 0;i<n;i++){
    	for(int j=0;j<n;j++){
    		cin>>A[i][j];
    	}
    }

    int x,y;

    cin>>x>>y;

    int res2 = 0;

    res2 = count_neighbors(n, A, x, y);
    cout<<res2<<endl;
	return 0;
}