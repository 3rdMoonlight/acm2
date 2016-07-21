#include<map>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=100010;
int n,q,tt;
int rea[MAXN];
int ql[MAXN],qr[MAXN];
int stb[MAXN][20];
int lg[MAXN];
map<int,long long> num;
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
int rmq(int l,int r)
{
	int k=floor(log(r-l+1.0)/log(2.0));
	return gcd(stb[l][k],stb[r-(1<<k)+1][k]);
}
int main()
{
	scanf("%d",&tt);
	for(int i=2;i<=100000;i++) lg[i]=lg[i/2]+1;
	for(int cnt=1;cnt<=tt;cnt++)
	{
		memset(stb,0,sizeof stb);
		num.clear();
		printf("Case #%d:\n",cnt);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&rea[i]),stb[i][0]=rea[i];
		int k=floor(log(1.0*n)/log(2.0));
		for(int j=1;j<=k;j++)
			for(int i=n;i>0;i--)
			{
				if(i+(1<<(j-1))<=n)
					stb[i][j]=gcd(stb[i][j-1],stb[i+(1<<(j-1))][j-1]);
			}
		for(int i=1;i<=n;i++)
		{
			int ll=i-1;
			while(ll<n)
			{
				ll++;
				int tmp=rmq(i,ll),lt=ll;
				for(int p=1<<lg[n-lt+1];p;p>>=1)
					if(ll+p<=n&&rmq(i,ll+p)==tmp) ll+=p;
				num[tmp]+=ll-lt+1ll;
			}
		}	
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&ql[i],&qr[i]);
			printf("%d %lld\n",rmq(ql[i],qr[i]),num[rmq(ql[i],qr[i])]);
		}
	}
	return 0;
}
