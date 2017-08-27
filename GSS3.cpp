//GSS3.cpp

#include <iostream>
#include <cstring>

using namespace std;
#define MAXN 100000
typedef long long ll;

ll tree[4*MAXN];
ll lazy[4*MAXN];

void update(int i, int start, int end, int low, int high, int val){
	if (lazy[i]){
		tree[i] += (end-start+1)*lazy[i];
		if (start!=end){
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
		}
		lazy[i] = 0;
	}
	
	if (start>end || high<start || low>end)
		return;
	if (start>=low && end<=high){
		tree[i] += (end-start+1)*val;
		if (start!=end){
			lazy[2*i] += val;
			lazy[2*i+1] += val;
		}
		return;
	}
	
	int mid = start+(end-start)/2;
	update(2*i, start, mid, low, high, val);
	update(2*i+1, mid+1, end, low, high, val);
	tree[i] = tree[2*i] + tree[2*i+1];
}

ll query(int i, int start, int end, int low, int high){
	if (start>end || high<start || low>end)
		return 0;
	
	if (lazy[i]){
		tree[i] += (end-start+1)*lazy[i];
		if (start!=end){
			lazy[2*i] += lazy[i];
			lazy[2*i+1] += lazy[i];
		}
		lazy[i] = 0;
	}
	
	if (start>=low && end<=high){
		return tree[i];
	}
	
	int mid = start+(end-start)/2;
	int res1 = query(2*i, start, mid, low, high);
	int res2 = query(2*i+1, mid+1, end, low, high);
	return (res1+res2);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--){
		memset(tree, 0, sizeof tree);
		memset(lazy, 0, sizeof lazy);
		int n, c;
		scanf("%d%d", &n, &c);
		for (int i=0;i<c;i++){
			int x, l, r;
			scanf("%d%d%d", &x, &l, &r);
			if (x==0){
				int val;
				scanf("%d", &val);
				update(1, 1, n, l, r, val);
			}else{
				ll res = query(1, 1, n, l, r);
				printf("%lld\n", res);
			}
		}
	}
	return 0;
}