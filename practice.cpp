#include <bits/stdc++.h>
using namespace std;

#define MAXN 50010
#define MAXM 2*MAXN

struct edge{
	int x,y;
}E[MAXM];

typedef long long ll;

vector<int>v;
int n,a[MAXN];
int edge_cnt,last[MAXN],ne[MAXM],anc[MAXN][21];
int tot,size[MAXN],Maxson[MAXN],zx,dep[MAXN];
ll dist[MAXN][101];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int f){
	dep[x]=dep[f]+1;
	anc[x][0]=f;
	for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	size[x]=a[x];
	for(int i=last[x];i;i=ne[i]){
		int y = E[i].y;
		if(y==f) continue;
		dfs(y,x);
		size[x]+=size[y];
		Maxson[x]=max(Maxson[x],size[y]);
	}
	Maxson[x]=max(Maxson[x],tot-size[x]);
	if(Maxson[x]<Maxson[zx]) zx=x;
}

int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x = anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

ll getdis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];	
}

ll cal(int x,int y){
	ll res=0;
	for(int i=1;i<=n;i++){
		res+=min(getdis(i,x),getdis(i,y))*a[i];
	}
	return res;
}

void getp(int x,int f,int dis){
	if(dis>4) return;
	v.push_back(x);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
		getp(E[i].y,x,dis+1);
}

bool cmp (const int &x,const int &y){
	return a[x]>a[y];
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),tot+=a[i];
	Maxson[0]=0x7fffffff;
	dfs(1,1);
	ll ans = 0x7fffffffffffffff;
	/*
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=min(ans,cal(i,j));
	*/
	getp(zx,zx,0);
	for(int i=0;i<min(100,(int)v.size());i++)
		for(int j=1;j<=n;j++)dist[j][i]=getdis(j,v[i]);
	for(int i=0;i<min(100,(int)v.size());i++)
		for(int j=i+1;j<min(100,(int)v.size());j++){
			ll res=0;
			for(int k=1;k<=n;k++){
				res+=min(dist[k][i],dist[k][j])*a[k];
			}
			ans=min(ans,res);
		}
	cout<<ans;
	return 0;
}
