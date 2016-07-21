#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,tt;
int sg[1<<21];
int vis[22];
int main()
{
	for(int s=0;s<(1<<20);s++)
	{
		int k=200;
		memset(vis,0,sizeof vis);
		for(int i=19;i>=0;i--)
		{
			if((s&(1<<i))==0) continue;
			if(k<i) vis[sg[s^(1<<i)^(1<<k)]]=1;
			else
			{
				for(int j=i-1;j>=0;j--)
					if((s&(1<<j))==0)
					{
						k=j;
						vis[sg[s^(1<<i)^(1<<k)]]=1;
						break;
					}
			}
		}
		for(int i=0;i<=20;i++)
			if(!vis[i])
			{
				sg[s]=i;
				break;
			}
	}
	scanf("%d",&tt);
	while(tt--)
	{
		scanf("%d",&n);
		int ans=0,m,r;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&m);
			int s=0;
			for(int j=1;j<=m;j++)
				scanf("%d",&r),s+=1<<(20-r);
			ans^=sg[s];
		}
		if(ans>0) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
