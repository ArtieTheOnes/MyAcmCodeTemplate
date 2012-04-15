#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
#define min(u,d) (u)<(d)?(u):(d)
using namespace std;

const long maxn=110;
const long maxq=16;

//�洢��������
long head[maxn],next[maxn],node[maxn],root,tt; 
/*dfs������ÿ���ڵ��һ�γ��ֵ�λ�ã����е�rmq��ԭ������dfs���еı�ţ�
dfs������ԭ���еı�ţ����г��ȣ�dfs����*/
long pos[maxn],rmq[maxn][maxq],tree_lab[maxn],real_lab[maxn],rlen,dfsn;

void  add(long x, long y)
{
	node[++tt]=y, next[tt]=head[x], head[x]=tt;
}
void swap(long &x, long &y)
{
	x^=y; y=x^y; x^=y;
}
//����dfs����
void build_rmq_seq(long x)
{
	long d=++dfsn;
	rmq[++rlen][0]=d; pos[d]=rlen;
	tree_lab[x]=d; real_lab[d]=x;
	for (long i=head[x]; i; i=next[i]) 
		build_rmq_seq(node[i]), rmq[++rlen][0]=d;
}
void cal_rmq()
{
	fo(j,1,maxq) 
		fo(i,1,rlen-(1 << j)+1) 
		   rmq[i][j]=min(rmq[i][j-1],rmq[i+(1 << (j-1))][j-1]);
}
long find_rmq(long x, long y)
{
	if (x>y) swap(x,y);
	long now=dfsn;
	fod(j,maxq,0) {
		if (x+(1 << j)-1>y) continue;
		now=min(now,rmq[x][j]);
		x+=(1 << j);
	}
	return now;
}
void make_lca()
{
	rlen=0; dfsn=0; 
	build_rmq_seq(root);
	cal_rmq();
}
int main()
{
	make_lca();
	return 0;
}
