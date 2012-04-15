/*
���ص�ʵ�ַ�����ʱ�临�Ӷ�ΪO(n^4)������Ҫ��O(n)������·��ÿ�����������Ҫ�޸�O(n)�ζ��꣬
ÿ���޸Ķ���ʱ����Ҫö�ٱ�����minֵ�����Ӷ�ΪO(n^2)��ʵ����KM�㷨�ĸ��Ӷ��ǿ�������O(n^3)�ġ�
���Ǹ�ÿ��Y����һ�����ɳ���������slack��ÿ�ο�ʼ������·ʱ��ʼ��Ϊ�����
��Ѱ������·�Ĺ����У�����(i,j)ʱ����������������ͼ�У�
����slack[j]���ԭֵ��lx[i]+ly[j]-g[i][j]�Ľ�Сֵ��
���������޸Ķ���ʱ��ȡ���в��ڽ������е�Y�����slackֵ�е���Сֵ��Ϊdֵ���ɡ�
����Ҫע��һ�㣺�����޸Ķ���������ڽ������е�lx[i]����d�����Ҫ�����е�slackֵ����ȥd��
*/
#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=201;
const long inf=1000000000;

long w[maxn];
long lx[maxn],ly[maxn];
bool bx[maxn],by[maxn];
long n,g[maxn][maxn];
long slack[maxn];

void init()
{
	fo(i,1,n) 
		fo(j,1,n) scanf("%d",&g[i][j]);
}
bool find(long x)
{
	bx[x]=1;
	fo(i,1,n) {
		if (!by[i] && lx[x]+ly[i]==g[x][i]) {
		   by[i]=1;
		   if (!w[i] || find(w[i])) {
			   w[i]=x;
			   return 1;
		   }
		   continue;
	    }
		if (lx[x]+ly[i]>g[x][i]) slack[i]=slack[i]<lx[x]+ly[i]-g[x][i]?slack[i]:lx[x]+ly[i]-g[x][i];
	}
	return 0;
}
void solve()
{
	fo(i,1,n) {
		lx[i]=ly[i]=0;
		fo(j,1,n) 
			if (g[i][j]>lx[i]) lx[i]=g[i][j];
	}
	memset(w,0,sizeof(w));
	for (long l=1,min; l<=n; ++l) {
		fo(i,1,n) slack[i]=inf;
		for (;;) {
			memset(bx,0,sizeof(bx));
			memset(by,0,sizeof(by));
			if (find(l)) break;
			min=inf;
			fo(i,1,n) 
				if (!by[i]) min=min<slack[i]?min:slack[i];
			/*fo(i,1,n) if (bx[i]) 
				fo(j,1,n) if (!by[j])
				    min=lx[i]+ly[j]-g[i][j]<min?lx[i]+ly[j]-g[i][j]:min;*/
			fo(i,1,n) {
				if (bx[i]) lx[i]-=min;
				if (by[i]) ly[i]+=min;
				slack[i]-=min;
			}
		}
	}
	long ans=0;
	fo(i,1,n) ans+=g[w[i]][i];
	printf("%d\n",ans);
}
int main()
{
	while (scanf("%d",&n),n!=0) {
		init();
		solve();
	}
	return 0;
}
