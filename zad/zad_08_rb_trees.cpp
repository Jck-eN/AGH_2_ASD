// ĆWICZENIA 8 - Jacek Nitychoruk
//---------------------------------------------


enum color{
    black, red
};

struct node{
    int black_quota;
    node* parent;
    node* left;
    node* right;
    color color;
    int height;
    int key;
    int min_height;
};

inline int height(node* a){return a->height;}

//--------------------------------------------------
//2. Udowodnić, że każde drzewo AVL jest drzewem RB.


void color_children(node* a, node* b){
  if (height(a) < height(b) or height(a)%2==1) color_black(a);
  else color_red(a);
  if (height(b) < height(a) or height(b)%2==1) color_black(b);
  else color_red(b);
}

void color_black(node* x){
  x->color = black;
  if (x!=nullptr){
        color_children(x->left, x->right);
  }
}
void color_red(node* x){
  x->color = red;
  if (x!=nullptr){
        color_children(x->left, x->right);
  }
}
//----------------------------------------------------
//1. Zaimplementować funkcję, która koloruje węzły drzewa aby spełniało warunek drzewa RB,
//funkcja powinna zwracać informację czy udało się pokolorować drzewo.

int color_node(node* n){
    if (n->parent == nullptr){
        n->color = black;
        n->black_quota = n->height / 2; // rounded up.
            // black-quota could start at any value between n.height/2 and n.min-height
    }
    else if (n->parent->color==red){
        n->color = black;
        n->black_quota = n->parent->black_quota;
    }

    else{       // (n->parent->color==black)
        n->black_quota = n->parent->black_quota - 1;

        // check that the subtree is not totally uncolorable
        if (n->min_height < n->black_quota) return -1;

        // use red only if the subtree is not colorable (as a tree), with given quota
        if (n->height <= n->black_quota*2){
            n->color = black;
        }
        else n->color = red;
    }
}