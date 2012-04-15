/*k��·(��ͱ߿��ظ���)��ƫ���㷨(MPS�Ż�)*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=6100;
const long maxm=300010;
const long inf=2000000000;

struct point //���������·��ʱ��ź���k��·ʱ��ʾƫ��·
{
/*
�������·ʱhû���õ����ڱ�ʾƫ��·ʱdist��ʾ��ǰst��ed�ľ��롣
u��ʾƫ��ڵ㣬h��ʾƫ������ڽӱ��еı�š�
*/
	long dist,u,h;
	point() {}
	point(long dist, long u, long h) 
	{
		this->dist=dist;
		this->u=u;
		this->h=h;
    }
};

struct heap //���������·��k��·�Ķ�struct
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

	point pop() //���ضѶ�Ԫ��ͬʱɾ���Ѷ�Ԫ��
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

} min_heap;

//���ͼ�еı�������ģ������ed���������·ʱҪ���ߵķ���ת֮�������
long head[maxn],next[maxm],node[maxm],tt; 
long len[maxm],plen[maxm]; //len��Ȩ��plenƫ��·����
long shortest[maxn],pre[maxn]; //shortest��ed���������·��pre���·���е�ǰ��
long n,m,st,ed,k;//��������������㣬�յ㣬k��·

void add(long x, long y, long d)
{
	node[++tt]=y, next[tt]=head[x], head[x]=tt;
	len[tt]=d;
}
void init()
{
	long x,y,d;
	memset(head,0,sizeof(head)), tt=0;
	scanf("%d%d%d",&n,&m,&k);
	st=1; ed=n;
	fo(i,1,m) {
		scanf("%d%d%d",&x,&y,&d);
		add(x,y,d), add(y,x,d);
	}
}
void cal_shortest() //heap�Ż���dijkstra
{
	bool vis[maxn];
	memset(vis,0,sizeof(vis));
	fo(i,1,n) shortest[i]=inf; shortest[ed]=0; pre[ed]=0;
	min_heap.clear();
	min_heap.ins(point(0,ed,0));

    for (point p; min_heap.len>0; ) {
		p=min_heap.pop();
		if (vis[p.u]) continue;
		vis[p.u]=1;
		for (long i=head[p.u]; i; i=next[i]) {
			if (vis[node[i]]) continue;
			if (shortest[p.u]+len[i]<shortest[node[i]]) {
				shortest[node[i]]=shortest[p.u]+len[i];
				pre[node[i]]=p.u;
				min_heap.ins(point(shortest[node[i]],node[i],0));
			}
		}
	}
}

struct edge //���ڱ����ڽӱ��еıߣ�dz��ʾ�����ڽӱ��еĵ�ַ��dist��ʾƫ��·����
{
	long dz,dist;
};

bool cmp(const edge &p1, const edge &p2)
{
	return p1.dist<p2.dist;
}

void sort_edge()
{
	edge e[maxn];
	long tot;
	fo(l,1,n) {
		tot=1; 
		e[tot].dz=0, e[tot].dist=inf; //���ڷ���Ա߽�������
		//�Ѵ�l������ÿһ�������ڽӱ��е�λ�ú�����Ϊƫ��ߵ�ƫ��·���ĳ���
		for (long i=head[l]; i; i=next[i]) 
			e[++tot].dz=i, e[tot].dist=len[i]+shortest[node[i]];
		sort(e+1,e+tot+1,cmp); //��ƫ��·���ĳ�����������

        //��ƫ��·�����ȴ�С�����������д�l�����ı�
        head[l]=e[1].dz;
		for (long i=1; i<=tot-1; ++i)
			next[e[i].dz]=e[i+1].dz, plen[e[i].dz]=e[i].dist; //��������ͬʱ��ֵ��Ӧ��ƫ��·������
	}
}
void cal_k_shortest() //���k��·
{
	min_heap.clear();
	min_heap.ins(point(shortest[st],st,head[st])); //��ʼ��
	long now_len;
	point p=min_heap.pop();

    for (long l=1; l<k; ++l, p=min_heap.pop() ) {
		//p.u��ʾ��ǰ·����ƫ��㣬p.h��ʾƫ���

		if (next[p.h]!=0) { //��ǰƫ��·���ĵ�һ����p.uѡ���µ�ƫ��·��Ҫѡ��ǰûѡ�������ƫ��·��
		    now_len=p.dist-plen[p.h]+plen[next[p.h]]; 
			min_heap.ins(point(now_len,p.u, next[p.h]));
		}

		for (long x=node[p.h]; x>0 && x!=p.u; x=pre[x]) { 
		//��ƫ��ߵ�node[p.h]��ʼ��ed�����·���Ͼ����ĵ㶼��չ���е�ƫ��·��
			if (x!=ed && next[head[x]]!=0)  { //��ed�ĵ���Ե�2�̵�·����ʼ��ƫ��·
				now_len=p.dist-plen[head[x]]+plen[next[head[x]]];
			    min_heap.ins(point(now_len,x,next[head[x]]));
		    }
			if (x==ed) {//ed����̵�·����Ϊƫ��·
			   now_len=p.dist+plen[head[x]];
			   min_heap.ins(point(now_len,x,head[x]));
		     }
		}

	}

    //��k�γ��ѵþ���k��·
	printf("%d\n",p.dist);
}
int main()
{
	init();
	cal_shortest();
	sort_edge();
	cal_k_shortest();
	return 0;
}
