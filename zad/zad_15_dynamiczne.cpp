const int n = 100;

int max(int a, int b, int c){
    if (a>b){
        if(a>c) return a;
        else return c;
    }
    else if(b>c) return b;
    else return c;
}

int lumberjack(int Tree[n]){ //     Let's assume that n>2
    int profit[n];
    profit[0]=Tree[0];
    profit[1]=Tree[1]+Tree[0];
    profit[2]=max(Tree[1]+Tree[2], Tree[0]+Tree[2], Tree[0]+Tree[1]);
    for(int i=3;i<n;i++){
        profit[i]=max(
            profit[i-3]+Tree[i-1]+Tree[i],
            profit[i-2]+Tree[i],
            profit[i-1]
        );
    }
    return profit[n-1];
