//LITE.cpp

#include <iostream>
#include <cstring>
using namespace std;

int tree[4*100005];
bool lazy[4*100005];

void update(int i, int start, int end, int low, int high){
	if (lazy[i]){
		lazy[i] = false;
		tree[i] = end-start+1 - tree[i];
		if (start!=end){
			lazy[2*i] = !lazy[2*i];
			lazy[2*i+1] = !lazy[2*i+1];
		}
	}
	
	if (start>end || low>end || high<start)
		return;
	
	if (start>=low && end<=high){
		tree[i] = end-start+1 - tree[i];
		if (start!=end){
			lazy[2*i] = !lazy[2*i];
			lazy[2*i+1] = !lazy[2*i+1];
		}
		return;
	}
	
	int mid = start+(end-start)/2;
	update(2*i, start, mid, low, high);
	update(2*i+1, mid+1, end, low, high);
	tree[i] = tree[2*i] + tree[2*i+1];
}

int query(int i, int start, int end, int low, int high){
	if (low>end || high<start)
		return 0;
	
	if (lazy[i]){
		tree[i] = end-start+1 - tree[i];
		if (start!=end){
			lazy[2*i] = !lazy[2*i];
			lazy[2*i+1] = !lazy[2*i+1];
		}
		lazy[i] = false;
	}
	
	if (start>=low && end<=high)
		return tree[i];
		
	int mid = start+(end-start)/2;
	int res1 = query(2*i, start, mid, low, high);
	int res2 = query(2*i+1, mid+1, end, low, high);
	return res1+res2;
}

int main() {
	memset(tree, 0, sizeof tree);
	memset(lazy, false, sizeof lazy);
	int n, c;
	scanf("%d%d", &n, &c);
	while (c--){
		int x, l, r;
		scanf("%d%d%d", &x, &l, &r);
		if (x==0){
			update(1, 1, n, l, r);
		}else{
			int res = query(1, 1, n, l, r);
			printf("%d\n", res);
		}
	}
	return 0;
}