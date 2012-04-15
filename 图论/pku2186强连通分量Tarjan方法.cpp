//��Tarjan��SCC�㷨
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
struct node
{
	int u,v,next;
}e[50010];
int num,x,y;
int low[10010],dfn[10010],len,beg[10010],stk[10010];
int od[10010],top,id[10010],scc,w;
void insert(int u,int v)
{
    e[++num]=(node){u,v,beg[u]};
	beg[u]=num;               
}
void dfs(int x)
{
   low[x]=dfn[x]=++len; 
   stk[++top]=x;
   for(int q=beg[x];q;q=e[q].next)
   {
	   int v=e[q].v;
	   if(dfn[v]==0) dfs(v);
	   if(low[v]<low[x]) low[x]=low[v];//ȡ�����������ӵ������ȷ��ʵĵ�
   }  
   if(low[x]<dfn[x]) return ; 
   //�����������ӵ����ȣ���ô���ܴӵ�ǰ�ĵ��ǿ��ͨ��֧�ֳ�ȥ
   ++scc;//����Ϳ����Ե�ǰ�ĵ�Ϊ���ߣ����������û�����ӵ����������
   //������������뵽�µķ�֧�У������
    do{ 
		id[w=stk[top--]]=scc;
		low[w]=inf;//����Ҫע����ǣ�������ͼ���Ǵ��ں�ߵģ�����
		//����Ҫ�Ѽ���SCC�ĵ��low����Ϊoo������˺���ߵ����⡣
	}while(w!=x);
}
void find_block()
{
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	top=0;
	scc=0;
    for(int i=1;i<=n;++i)		
		if(dfn[i]==0)  dfs(i);	 
}
void judge()
{
	memset(od,0xff,sizeof(od));
     for(int i=1;i<=num;++i)
		 if(id[e[i].u]!=id[e[i].v])
	 {
		 if (od[id[e[i].u]]==-1) od[id[e[i].u]]=1;
		 else od[id[e[i].u]]++;
	 }
	 int ans=0;
    for(int i=1;i<=scc;++i)
		if(od[i]==-1)
	{
		if(ans!=0) 
		{
			printf("0\n");
			return ;
		}
		for(int j=1;j<=n;++j)
			if(id[j]==i) ++ans;		
	}
	if(ans==0) ans=n;
	printf("%d\n",ans);	
}
int main()
{
	freopen("test.in","r",stdin);
	   while(scanf("%d%d",&n,&m)!=EOF)
	{
		   num=0;
		   memset(beg,0,sizeof(beg));
	      for(int i=1;i<=m;++i)
		  {
		      scanf("%d%d",&x,&y);              
			  insert(x,y);
		  }
		  find_block();
		  judge();
	   }
	return 0;
}
