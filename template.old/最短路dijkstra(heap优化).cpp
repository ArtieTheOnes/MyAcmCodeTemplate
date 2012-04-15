#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=6100;
const long maxm=300010;
const long inf=2000000000;

struct point
{
	long dist,u; //��ǰ��ŵĳ��Ⱥͽڵ���
	point() {}
	point(long dist, long u) 
	{
		this->dist=dist;
		this->u=u;
    }
};

struct heap //�ѵ�struct
{
	point p[maxm];
	long len;

	void clear() { len=0; }

	void swap(point &p1, point &p2)
	{
		point tmp;
		tmp=p1;  p1=p2; p2=tmp;
	}

	void ins(point x) 
	{
		p[++len]=x;
		for (long i=len; i>1; i/=2)
			if (p[i].dist<p[i/2].dist) swap(p[i],p[i/2]);
		    else break;
	}

	point pop() //����ͬʱɾ���Ѷ��ڵ�
	{
		point now=p[1];
		p[1]=p[len--];
		for (long i=2; i<=len; i*=2) {
			if (i+1<=len && p[i].dist>p[i+1].dist) ++i;
			if (p[i].dist<p[i/2].dist) swap(p[i],p[i/2]);
			else break;
		}
		return now;
	}

} min_heap; //��С�ѣ���distΪ�ؼ���

long head[maxn],next[maxm],node[maxm],tt;
long len[maxm]; //��Ȩ
long shortest[maxn],pre[maxn]; //���·�������·�ߵ�ǰ��
long n,m,st; //������������Դ��

void add(long x, long y, long d)
{
	node[++tt]=y, next[tt]=head[x], head[x]=tt;
	len[tt]=d;
}
void init()
{
	long x,y,d;
	memset(head,0,sizeof(head)), tt=0;
	scanf("%d%d",&n,&m);
	st=1;
	fo(i,1,m) {
		scanf("%d%d%d",&x,&y,&d);
		add(x,y,d), add(y,x,d);
	}
}
void cal_shortest()
{
	bool vis[maxn];
	memset(vis,0,sizeof(vis));
	fo(i,1,n) shortest[i]=inf; shortest[st]=0; pre[st]=0;
	min_heap.clear();
	min_heap.ins(point(0,st));

    for (point p; min_heap.len>0; ) {
		p=min_heap.pop();
		if (vis[p.u]) continue; //��ʹ������ɾ����Ҫ�жϳ��ѵ�״̬ʱ����Ч
		vis[p.u]=1;
		for (long i=head[p.u]; i; i=next[i]) { //��չ��״̬
			if (vis[node[i]]) continue;
			if (shortest[p.u]+len[i]<shortest[node[i]]) {
				shortest[node[i]]=shortest[p.u]+len[i];
				pre[node[i]]=p.u;
				min_heap.ins(point(shortest[node[i]],node[i]));
			}
		}
	}
}
int main()
{
	init();
	cal_shortest();
	return 0;
}
