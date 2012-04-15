/*lrjѧϰָ���ϵķ���*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define min(u,d) (u)<(d)?(u):(d)
using namespace std;

const long maxk=11; //k��·���Ͻ�
const long maxn=110; //�����Ͻ�
const long inf=100000000;

struct kpath //ǰk��·
{
	long klen[maxk];
	kpath() 
	{
		fo(i,1,maxk-1) klen[i]=inf; //��ʼ������Ϊinf
	}
} dist[maxn][maxn]; //i��j��ǰk��·

long n,k; //������k��·��
long heap[maxn],lab[maxn],hlen; //���ڼ��ټ���·���͵�ǰk��·�Ķ�

inline void swap(long i)//�������е�����Ԫ��
{
	long tmp;

	tmp=heap[i];  heap[i]=heap[i/2];  heap[i/2]=tmp;
    tmp=lab[i]; lab[i]=lab[i/2]; lab[i/2]=tmp;
}
inline void ins(long x, long w)
{
	long tmp;

	if (x>inf) x=inf;
	heap[++hlen]=x; lab[hlen]=w;
	for (long i=hlen; i>1; i/=2) {
		if (heap[i/2]>heap[i]) { swap(i); continue; }
		break;
	}
}
inline void del()
{
	heap[1]=heap[hlen]; lab[1]=lab[hlen--];
	for (long i=2; i<=hlen; i*=2) {
		if (i+1<=hlen && heap[i+1]<heap[i]) ++i;
		if (heap[i/2]>heap[i]) { swap(i); continue; }
		break;
	}
}
inline void init()
{
	long m,x,y,d;
	scanf("%d%d%d",&n,&m,&k);
	//fo(i,1,n) dist[i][i].klen[1]=0;
	fo(i,1,m) { 
		 scanf("%d%d%d",&x,&y,&d);
		 dist[x][y].klen[1]=min(dist[x][y].klen[1],d);
		 dist[y][x].klen[1]=dist[x][y].klen[1];
	}
}
inline kpath min_klen(kpath p1, kpath p2) //��p1,p2���ҳ�ǰk��·
{
	kpath p;
	long l1=1, l2=1;

	fo(l,1,k) {
		if (l2>k || ( l1<=k && p1.klen[l1]<p2.klen[l2])) { p.klen[l]=p1.klen[l1++]; continue; }
		p.klen[l]=p2.klen[l2++];
	}
	return p;
}
inline kpath add(kpath p1, kpath p2)
/*
����p1,p2����������·��֮���е�ǰk��·
���������Ȱ�p1�е�ÿ��·�����ȼ���p2�е����·�������
ÿ��ȡ����ǰ���·�󽫱�ȡ����p1·�����ȼ���p2����һ��·�����ȼ������
Ҫע��·����Ӻ���ܻ�Խ�磬��Խ��������inf
*/
{
	kpath p;
	long pt[maxk], wpt; //��ǰÿ��p1��·������ָ���p2�е�·������
	
	hlen=0;
	fo(i,1,k) {
		pt[i]=1;
		ins(p1.klen[i]+p2.klen[1], i);
	}
	fo(i,1,k) {
		p.klen[i]=heap[1]; //ȡ����ǰ��̳�����Ϊ�µĵ�i��·
		wpt=lab[1]; //��ȡ����p1�еĵ�wpt��·
		del();
		ins(p1.klen[wpt]+p2.klen[++pt[wpt]],wpt); //���º�������
	}
	return p;
}
inline kpath extend_kpath(kpath pp)
/*
��pp��չ���������߻�����ȡǰk��·
*/
{
	kpath p,ext_p=pp;
	fo(i,1,k) {
		p=min_klen(p,pp);
		ext_p=add(ext_p,pp);
	}
	return p;
}
void cal_every_kpath()
{
	kpath pp;
	fo(l,1,n)
		fo(i,1,n) 
		   fo(j,1,n) {
		       pp=extend_kpath(dist[l][l]);
			   //ֻ����lһ��
			   dist[i][j]=min_klen( dist[i][j], add(dist[i][l],dist[l][j]) ); 
			   //����l���λ����ϣ����Ҫ��չ
		       dist[i][j]=min_klen( dist[i][j], add( extend_kpath(dist[l][l]) , add(dist[i][l],dist[l][j]) ) );
		   }
	/*
	d[i][j][l]��ʾ���ǵ�ǰ��i��j�м�ֻ�������Ϊ1��l�ĵ��ǰk��·
	1��ֻ����1-(l-1)����d[i][j][l-1]
	2������l�����ڿ��ܶ�ξ���l������Ҫ��dist[l][l][l-1]��չ�������߻����ó���ξ���l��ǰk��·��
	     ��dist[i][l][l-1]+extend(dist[l][l][l-1])+dist[j][l][l-1]
	��������ʱ����Խ���3άʡ�Ե�
	*/
}
void solve()
{
	long x,y,kp;
    while (scanf("%d%d%d",&x,&y,&kp), x!=0) 
		printf("%d\n",dist[x][y].klen[kp]);
}
int main()
{
	init();
	cal_every_kpath();
	solve();
	return 0;
}
