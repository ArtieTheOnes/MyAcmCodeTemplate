/*ÿ��ͨ�������������������������֣�ʹ�û��ֵ�ÿ�������ڵ���������n/2����
ÿ�������ݹ�ȥ����������������֮����������ĵ����ͨ�����������ά�����*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#define fo(	i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=20001;

struct point
{
	long len,id;
} p[maxn];

long head[maxn],next[maxn],node[maxn],tt;
long n,k,m,node_num,root,biggest,tn,ans;//nΪ�ڵ�����kΪ��Ծ����Ͻ�
long vis[maxn],dist[maxn];
long sum[maxn];

bool cmp(const point &p1, const point &p2)
{
	return p1.len<p2.len;
}
void add(long x, long y, long d)
{
	node[++tt]=y; next[tt]=head[x]; head[x]=tt;
	dist[tt]=d;
}
void init()
{
	long x,y,d;
	memset(head,0,sizeof(head)), tt=0;
	fo(i,1,n-1) 
		scanf("%d%d%d",&x,&y,&d), add(x,y,d), add(y,x,d);
}
void cal_num(long x, long y)
{
	++node_num;
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y && !vis[node[i]]) cal_num(node[i],x);
	    //ע���ų������������ĵ�,vis[node[i]]��ʾnode[i]��֮ǰ�Ѿ������ֵ���
}
long find_root(long x, long y)
{
	long bigger=0, tot=1, now;//bigerΪ�Ե�ǰx��������ʱ����ǿ������Ľڵ���
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y && !vis[node[i]]) {
		   if ((now=find_root(node[i],x))>bigger) bigger=now;
		   tot+=now;
	    }
	if (node_num-tot>bigger) bigger=node_num-tot;
	if (bigger<biggest) biggest=bigger, root=x;
	return tot;
}
void count_len(long x, long y, long len)
{
	p[++m].len=len, p[m].id=tn;
	for (long i=head[x]; i; i=next[i]) 
		if (node[i]!=y && !vis[node[i]]) count_len(node[i],x,len+dist[i]);
}
void cal_ans()
{
	memset(sum,0,sizeof(sum)); 
	p[0].len=0, p[0].id=0;
	fo(i,1,m) ++sum[p[i].id];
	for (long i=0, j=m; i<j; --sum[p[++i].id]) {
		while (i<j && p[j].len+p[i].len>k) --sum[p[j--].id];
		ans+=(j-i)-sum[p[i].id];//�����ʱ��Ҫ��ȥͬһ�������е���������ĵ����
	}
}
void cal(long x)
{
	node_num=m=tn=0, biggest=n;
	cal_num(x,x); //ͳ�Ƶ�ǰ���Ľڵ���
	find_root(x,x); //������
	for (long i=head[root]; i; i=next[i]) 
		if (!vis[node[i]]) 
		    ++tn, count_len(node[i],root,dist[i]); //���ÿ�������нڵ㵽����root�ľ��룬tn��¼��rootΪ���������ĸ���
	sort(p+1,p+m+1,cmp);//�����нڵ㵽root�ľ�������
	cal_ans();//����ά��������������ĵ����
	vis[root]=1;
	for (long i=head[root]; i; i=next[i])  //�ݹ����ÿһ������
		if (!vis[node[i]]) cal(node[i]);
}
void solve()
{
	memset(vis,0,sizeof(vis));
	ans=0;
	cal(1);
	printf("%d\n",ans);
}
int main()
{
	while (scanf("%d%d",&n,&k),n!=0) {
		init();
		solve();
	}
	return 0;
}
