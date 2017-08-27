//FREQUENT.cpp

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Node{
public:
    int maxi, prefix, suffix, lvalue, rvalue;
    Node(){
        maxi = prefix = suffix = lvalue = rvalue = 0;
    }
    void set(int val){
        maxi = prefix = suffix = 1;
        lvalue = rvalue = val;
    }
    void merge(Node a, Node b){
        lvalue = a.lvalue;
        rvalue = b.rvalue;
        prefix = a.prefix;
        suffix = b.suffix;
        if (a.lvalue==b.lvalue){
            prefix += b.prefix;
        }
        if (b.rvalue==a.rvalue){
            suffix += a.suffix;
        }
        maxi = max(a.maxi, b.maxi);
        if (a.rvalue==b.lvalue){
            maxi = max(maxi, a.suffix+b.prefix);
        }
    }
};

Node tree[4*100005];
int arr[100005];

void build(int i, int start, int end){
    if (start==end){
        tree[i].set(arr[start]);
        return;
    }
    int mid = start+(end-start)/2;
    build(2*i, start, mid);
    build(2*i+1, mid+1, end);
    tree[i].merge(tree[2*i], tree[2*i+1]);
}

Node query(int i, int start, int end, int low, int high){
    Node a;
    if (start>end || low>end || high<start)
        return a;
    
    if (start>=low && end<=high)
        return tree[i];
    
    int mid = start+(end-start)/2;
    Node res1 = query(2*i, start, mid, low, high);
    Node res2 = query(2*i+1, mid+1, end, low, high);
    a.merge(res1, res2);
    return a;
}

int main() {
    int n, c;
    while(1){
	    memset(tree, 0, sizeof tree);
	    memset(arr, 0, sizeof arr);
	    scanf("%d", &n);
	    if (n==0) break;
	    scanf("%d", &c);
	    for (int i=1;i<=n;i++)
	        scanf("%d", &arr[i]);
	    build(1, 1, n);
	    
	    while (c--){
	        int a, b;
	        scanf("%d%d", &a, &b);
	        Node res = query(1, 1, n, a, b);
	        printf("%d\n", res.maxi);
	    }
    }
    return 0;
}