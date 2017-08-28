//BRCKTS.cpp

#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 300005

class Node{
	public:
	int open, closed;
	Node(){
		open = closed = 0;
	}
	void merge(Node a, Node b){
		if (a.open>=b.closed){
			open = a.open+b.open-b.closed;
		}else{
			open = b.open;
		}
		
		if (a.open<=b.closed){
			closed = b.closed+a.closed-a.open;
		}else{
			closed = a.closed;
		}
	}
};

Node tree[4*MAXN];
char arr[MAXN];

void build(int i, int start, int end){
	if (start>end) return;
	if (start==end){
		if (arr[start]=='('){
			tree[i].open = 1;
			tree[i].closed = 0;
		}else{
			tree[i].closed = 1;
			tree[i].open = 0;
		}
		return;
	}
	
	int mid = start+(end-start)/2;
	build(2*i, start, mid);
	build(2*i+1, mid+1, end);
	tree[i].merge(tree[2*i], tree[2*i+1]);
}

void update(int i, int start, int end, int idx){
	if (start>end || idx<start || idx>end) return;
	if (start==end){
		if (arr[idx]=='('){
			tree[i].open--;
			tree[i].closed++;
			arr[idx] = ')';
		}else{
			tree[i].open++;
			tree[i].closed--;
			arr[idx] = '(';
		}
		return;
	}
	int mid = start+(end-start)/2;
	update(2*i, start, mid, idx);
	update(2*i+1, mid+1, end, idx);
	tree[i].merge(tree[2*i], tree[2*i+1]);
}

int main() {
	
	for (int k=1;k<=10;k++){
		printf("Test %d:\n", k);
		int n;
		scanf("%d", &n);
		memset(tree, 0, sizeof tree);
		memset(arr, 0, sizeof arr);
		scanf("%s", arr+1);
		build(1, 1, n);	
		int t;
		scanf("%d", &t);
		while (t--){
			int x;
			scanf("%d", &x);
			if (x==0){
				if (tree[1].open==0 && tree[1].closed==0)
					printf("YES\n");
				else
					printf("NO\n");
			}else{
				update(1, 1, n, x);
			}
		}
	}
	return 0;
}