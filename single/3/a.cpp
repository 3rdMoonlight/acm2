#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int tt,n,k;
char s[3010];
int p[3010];
int fa[3010];
int ans[3010];
int ind[3010],ttt[3010];
int clr[3010];
vector<int>vv;
int getnxt(int x)
{
	return (x+1)%n;
}
int getpre(int x)
{
	return (x+n-1)%n;
}
int cmp(int a,int b)
{
	return s[a]>s[b];
}
int getf(int x)
{
	if(x==-1) return -1;
	if(fa[x]==x) return x;
	fa[x]=getf(fa[x]);
	return fa[x];
}
int main()
{
	scanf("%d",&tt);
	while(tt--)
	{
		memset(s,0,sizeof s);
		memset(ind,0,sizeof ind);
		memset(clr,0,sizeof clr);
		memset(ttt,0,sizeof ttt);
		vv.clear();
		scanf("%d%d%s",&n,&k,s);
		for(int i=0;i<3000;i++)
			p[i]=fa[i]=i;
		int m=n,al=0;
		while(m>k)
		{
			sort(p,p+m,cmp);
			int l=m-k,r=m-k;
			while(l>=0&&s[p[l]]==s[p[m-k]]) l--;
			while(r<m&&s[p[r]]==s[p[m-k]]) r++;
			if(l==-1&&r==m&&p[0]>=n)
			{
				for(int i=0;i<m;i++)
				{
					p[i]-=n;
					clr[getf(p[i])]=1;
					ttt[getf(p[i])]=1;
				}
				for(int i=0;i<m;i++)
				{
					int bef=getf(getpre(getf(p[i])));
					if(ttt[bef])
						ind[bef]++;
				}
				queue<int>qq;
				for(int i=0;i<m;i++)
				{
					int now=getf(p[i]);
					if(ind[now]==0)
						qq.push(now);
				}
				if(qq.empty())
				{
					double idx=0,step=m*1.0/k;
					for(int i=0;i<m;i++)
					{
						int tmp=getf(p[i]);
						clr[tmp]=1;
						vv.push_back(tmp);
					}
					sort(vv.begin(),vv.end());
					while(k--)
					{
						clr[(int)vv[(idx+0.5)]]=0;
						idx=idx+step;
					}
					break;
				}
				for(int tot=0;tot<k;tot++)
				{
					int x=qq.front();
					qq.pop();
					clr[x]=0;
					int bef=getf(getpre(getf(x)));
					if(ttt[bef])
					{
						if(--ind[bef]==0) qq.push(bef);
					}
				}
				break;
			}
			for(int i=0;i<=l;i++)
			{
				int tmp=getf(p[i]);
				fa[tmp]=-1;
			}
			int nm=r-l-1,nk=k-(m-r);
			for(int i=0;i<nm;i++)
			{
				p[i]=p[i+l+1];
				if(p[i]>=n) p[i]-=n;
			}
			for(int i=0;i<nm;i++)
			{
				int nxtp=getnxt(p[i]);
					if(fa[nxtp]==nxtp)
						nxtp=p[i]+n;
				fa[nxtp]=getf(p[i]);
				p[i]=nxtp;
			}
			m=nm,k=nk;
		}
		for(int i=0;i<n;i++)
		{
			if(clr[i])
				fa[i]=-1;
		}
		for(int i=0;i<n;i++)
			if(fa[i]==i)
				ans[++al]=i;
		string ss="\0",tmp;
		for(int i=1;i<=al;i++)
		{
			tmp=s[ans[i]];
			for(int p=getnxt(ans[i]);fa[p]!=p;p=getnxt(p))
				tmp+=s[p];
			if(ss<tmp) ss=tmp;
		}
		for(int i=0;i<ss.length();i++)
			printf("%c",ss[i]);
		printf("\n");
	}
	return 0;
}
