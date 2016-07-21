#include<cstdio>
#include<iostream>
using namespace std;
typedef long long int64;
const int64 P=1000000000+7;
int n,m;
int64 fz[110],fm[110];
int64 B[20][20][200];
int64 mi(int64 x,int64 y)
{
	int64 ret=1,tmp=x;
	for(int i=0;i<=31;i++)
	{
		if(y&(1<<i)) ret=ret*tmp%P;
		tmp=tmp*tmp%P;
	}
	return ret;
}
int64 C(int x,int y)
{
	if(x<y) return 0;
	return fz[x]*fm[y]%P*fm[x-y]%P;
}
int64 b(int x,int y,int z)
{
	if(x>=y) return B[x][y][z];
	else return B[y][x][z];
}
int main()
{
	fz[0]=fm[0]=1;
	for(int i=1;i<=100;i++) fz[i]=fz[i-1]*i%P,fm[i]=mi(fz[i],P-2ll);
	B[1][0][0]=1;
	for(int i=1;i<=10;i++)
		for(int j=1;j<=i;j++)
			for(int k=1;k<=i*j;k++)
			{
				B[i][j][k]=C(i*j,k);
				for(int ii=1;ii<=i;ii++)
					for(int jj=0;jj<=j;jj++)
						for(int kk=0;kk<=min(k,ii*jj);kk++)
						{
							if(b(ii,jj,kk)&&(i-ii)*(j-jj)>=(k-kk))
							{
								if(i==ii&&j==jj) break;
								B[i][j][k]=(B[i][j][k]-C(i-1,ii-1)*C(j,jj)%P*b(ii,jj,kk)%P*C((i-ii)*(j-jj),k-kk)%P)%P;
								if(B[i][j][k]<0) B[i][j][k]+=P;
							}
						}
			}
	while(scanf("%d%d",&n,&m)>0)
	{
		if(n<m) swap(n,m);
		int64 ans=0;
		for(int i=1;i<=n*m;i++)
			ans=(ans+B[n][m][i]*mi(2,i)%P)%P;
		printf("%lld\n",ans);
	}
	return 0;
}
