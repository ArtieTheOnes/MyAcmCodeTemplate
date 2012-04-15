/*���忴lrjѧϰָ��*/
#include<iostream>
#include<cmath>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=20010;
const long maxm=16;

long head[maxn],next[maxn],node[maxn],tt;
long ancestor[maxn][maxm],depth[maxn]; //ancestor[i][j]��ʾi�Žڵ�ĵ�2^j������,0�ױ�ʾ����
long stack[maxn]; //ͬ�ڼ���ancestor,������ǵ�ǰ��root��x��·���ϵĽڵ�
long n,t,root;

void add(long x, long y)
{
	node[++tt]=y; next[tt]=head[x]; head[x]=tt;
}
void init()
{
	memset(head,0,sizeof(head)), tt=0;
}
void pre_k_ancestor(long x, long y, long dep)
{
	depth[x]=dep; stack[dep]=x; ancestor[x][0]=x;
	for (long j=0; dep-(1 << j)>=0; ++j) ancestor[x][j+1]=stack[dep-(1 << j)];
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y) pre_k_ancestor(node[i], x, dep+1);
}
//��x�ĵ�k�����ȣ�����rmq����
long cal_k_ancestor(long x, long k)
{
	fod(j,maxm,0) 
		if ((1 << j)<=k) x=ancestor[x][j+1], k-=1 << j;
	return x;
}
void solve()
{
	long x,y;
	scanf("%d%d",&x,&y);
	long low=0, high=depth[x]<depth[y]?depth[x]:depth[y];
	long jie,xx,yy;
	//��x��y������ͬһ�߶�
	x=cal_k_ancestor(x,depth[x]-high);
	y=cal_k_ancestor(y,depth[y]-high);
	if (x==y) {printf("%d\n",x); return;} //x==y����x��y�����Ⱥ����ϵ
	/*����2�ֵ�������ÿ���ҳ�����jieʹ��high-2^jie<low��ͨ���ж����Ϊhigh-2^jie
    �Ľڵ��Ƿ�Ϊ�������ȣ�ͬʱ������ش���*/
	while (low+1<high) { //��������Ϊx,y����lca���·�
		jie=long(log(double(high-low-1))/log(2.0));
	    xx=ancestor[x][jie+1];
		yy=ancestor[y][jie+1];
		if (xx==yy) low=high-(1 << jie);
		else high-=1 << jie, x=xx, y=yy;
	}
	printf("%d\n",ancestor[x][1]);
}
int main()
{
	scanf("%d",&t);
	while (t--) {
		init();
		pre_k_ancestor(root,root,0);
		solve();
	}
	return 0;
}
