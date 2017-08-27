//GSS1.cpp

#include <iostream>
#include <vector>
#include <climits>
using namespace std;
#define MAXN 50005

class Node{
	public:
		int maxi, prefix, suffix, sum;
		Node(){
			maxi = prefix = suffix = sum = -100000;
		}
		void set(int val){
			maxi = prefix = suffix = sum = val;
		}
		void merge(Node a, Node b){
			prefix = max(a.prefix, a.sum+b.prefix);
			suffix = max(b.suffix, a.suffix+b.sum);
			sum = a.sum+b.sum;
			maxi = max(max(a.maxi, b.maxi), a.suffix+b.prefix);
		}
};

Node temp[200005];
int arr[50005];

void build(int i, int start, int end){
    if (start==end){
        temp[i].set(arr[start]);
        return;
    }
    int mid = start+(end-start)/2;
    build(2*i, start, mid);
    build(2*i+1, mid+1, end);
    temp[i].merge(temp[2*i], temp[2*i+1]);
}

Node query(int i, int start, int end, int low, int high){
	Node a;
    if (low>end || high<start)
        return a;
    if (start>=low && end<=high)
        return temp[i];
    
    int mid = start+(end-start)/2;
    
    Node res1 = query(2*i, start, mid, low, high);
    Node res2 = query(2*i+1, mid+1, end, low, high);
    a.merge(res1, res2);
    return a;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    build(1,1,n);
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        Node res=query(1,1,n,l,r);
        printf("%d\n",res.maxi);
    }
    return 0;
}
