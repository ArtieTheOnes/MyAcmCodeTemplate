/*
2-sat��ע��߱��
*/
#include<iostream>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define max(u,d) (u)>(d)?(u):(d)
using namespace std;

const long maxn=5001;
const long maxm=5000000;

long next[maxm],node[maxm],tt; //����
long head[maxn],la[maxn];//ԭͼ��ÿ������ڽӱ���ͷ��ÿ��ǿ��ͨ������������������ͷ 
long vis[maxn],cl[maxn],d[maxn];//ÿ����������ǿ��ͨ������ǣ�Ⱦɫ�ı�ǣ�������ͼÿ����Ķ���
long high[maxn],num[maxn],e[maxm][2];//��ǿ��ͨ����ʱ�ĸ�����ǣ�ÿ����
long st[maxn],top;//��ǿ��ͨ����ʱ�ĸ���ջ
long op[maxn];//ÿ����Ķ�����
long n,m,tot,dfsn; //������������

//����ͷΪhead����������ӽڵ�y
void add(long &head, long y)
{
	node[++tt]=y; next[tt]=head; head=tt;
}
void init()
{

}
void make() //��ͼ������ѡ��ϵ���ߣ�ע��x�Ķ�����Ҫ��op[x]����¼
{
	memset(head,0,sizeof(head)), tt=0;
}
void find(long x) //��ǿ��ͨ����
{
	high[x]=dfsn; num[x]=dfsn--; st[++top]=x;
	for (long i=head[x]; i; i=next[i]) 
		if (!num[node[i]]) {
		   find(node[i]);
		   high[x]=max(high[x],high[node[i]]);
	    } else if (!vis[node[i]]) high[x]=max(high[x],num[node[i]]);
	
	if (num[x]==high[x]) {
		vis[x]=++tot;
		while (st[top]!=x)
			vis[st[top--]]=tot;
		--top;
	}
}
void zip() //����
{
	memset(head,0,sizeof(head)), tt=0; //����������ͼ
	memset(d,0,sizeof(d));
	long x,y;
	fo(i,1,m) {
		x=vis[e[i][0]]; y=vis[e[i][1]];
		if (x!=y) 
			add(head[y],x), ++d[x]; //��������ͼ��������
	}
	memset(la,0,sizeof(la));
	fo(i,1,2*n)
		add(la[vis[i]],i); //��ͬһ��ǿ��ͨ�����еĵ㣬
}
void color() 
/*
�����˹�ϵȾɫ����0�ȵ���ѡ����õ�ì�ܵ����е㼰���Ӿ���ǲ�ѡ
cl[x]==0��ʾδ������cl[x]==1��ʾѡ��cl[x]==2��ʾ��ѡ
*/
{
	memset(cl,0,sizeof(cl));
	long que[maxn],st,ed=0,x,y;
    fo(i,1,tot)
		if (d[i]==0) que[ed++]=i;
	for (x=que[st=0]; st<ed; x=que[++st]) {
		if (!cl[x]) {
			cl[x]=1;
			for (long i=la[x], y=vis[op[node[i]]]; i; i=next[i], y=vis[op[node[i]]]) {
				cl[y]=2; //����x�еĵ�ì�ܵ�ǿ��ͨ�������Ϊ2
			    for (long j=head[y]; j; j=next[j]) cl[node[j]]=2; //��ì�ܵ�ǿ��ͨ�����ĺ��Ҳ���Ϊ2
			}
		}
		//��x�ĺ�̽���
		for (long i=head[x]; i; i=next[i]) 
			if (--d[node[i]]==0) que[ed++]=node[i];
	}
}
void solve()
{
	memset(high,0,sizeof(high));
	memset(num,0,sizeof(num));
	memset(vis,0,sizeof(vis));
	tot=0; top=0; dfsn=2*n;
	fo(i,1,2*n)
		if (!vis[i]) find(i);
    zip();
    color();
}
int main()
{
	init();
	solve();
	return 0;
}
