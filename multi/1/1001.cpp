#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define maxn 100008
#define maxm 1000008

struct line
{
    int u,v,nt,w;
}eg[maxm],EG[maxm];

int fa[maxn],lt[maxn],son[maxn],f[maxn];
int n,m,sum;
long long ans1,ans2;

int cmp(const line &a,const line &b)
{
    return a.w<b.w;
}

int find(int x)
{
    if (fa[x]==x) return x;
    fa[x]=find(fa[x]);
    return fa[x];
}

void add(int u,int v,int w)
{
    //printf("%d %d %d \n",u,v,w);
    eg[++sum].u=u; eg[sum].v=v; eg[sum].w=w; 
    eg[sum].nt=lt[u]; lt[u]=sum;
}

void dfs(int u)
{
    son[u]=1;
    for (int i=lt[u];i;i=eg[i].nt)
    {
        int v=eg[i].v;
        if (v!=f[u])
        {
            f[v]=u;
            dfs(v);
            son[u]+=son[v];
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--) 
    {
    sum=1; ans1=0; ans2=0;
    memset(lt,0,sizeof(lt));
    memset(son,0,sizeof(son));
    memset(f,0,sizeof(f));
    for(int i=1;i<=n*2;i++) eg[i].nt=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
        scanf("%d%d%d",&EG[i].u,&EG[i].v,&EG[i].w);
    for (int i=1;i<=n;i++) fa[i]=i;
    sort(EG+1,EG+m+1,cmp);
    int x,y;
    for (int i=1;i<=m;i++)
    {
        x=find(EG[i].u);
        y=find(EG[i].v);
        if (x!=y)
        {
            ans1+=EG[i].w;
            fa[x]=y;
            add(EG[i].u,EG[i].v,EG[i].w);
            add(EG[i].v,EG[i].u,EG[i].w);
        }
    }
    printf("%lld ",ans1);

    dfs(1);
    //for(int i=1;i<=n;i++) printf("%d %d\n",f[i],son[i]);
    for (int i=2;i<=sum;i++)
        if (i & 1)
        {
            int u=eg[i].u;
            int v=eg[i].v;
            //printf("%d %d %d %d %d %d \n",i,u,v,f[u],n,ans2);
            if (f[u]==v) ans2+=(long long)(son[u])*(n-son[u])*eg[i].w;
            if (f[v]==u) ans2+=(long long)(son[v])*(n-son[v])*eg[i].w;
        }
    long long N=n*(n-1ll) / 2ll;
    
    printf("%.2lf\n",(double)ans2/(N*1.0));
    }
    return 0;
}
