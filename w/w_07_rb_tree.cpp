#include <iostream>
using namespace std;

struct Data{
    int val;
};

struct node{
    node* left;
    node* right;
    node* parent;
    int key;
    Data val;
};
void left_rotate(node* &root, node* x){
    node* y = x->right;
    x->right=y->left;
    y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==NULL)root=y;
    else if(x->parent->right==x) x->parent->right=y;
    else x->parent->left=y;
    x->parent=y;
    y->left=x;
}



int main()
{
    
    
    cout << endl;
    system("pause");
    return 0;
}
