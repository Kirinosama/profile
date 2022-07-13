#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010

int ans[MAXN],a[MAXN],s[MAXN],Max[MAXN],cnt,n,top;

void print(){
	for(int i=1;i<=top;i++)printf("%d ",s[i]);
	cout<<endl;
}

int main(){
	//freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)Max[i]=max(Max[i+1],a[i]);
	int pos = 1; s[++top]=a[1];
	while(pos<n){
		if(top==0 || Max[pos+1]>s[top])
			s[++top]=a[++pos];
		else
			ans[++cnt]=s[top--];
	}
	while(top) ans[++cnt]=s[top--];
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}



/*

4 5 1 6 10 7 8 9 3 2

后方有比栈顶更大就接着push 否则pop

stack: 4 5 1 6 7 8

10 9

*/
