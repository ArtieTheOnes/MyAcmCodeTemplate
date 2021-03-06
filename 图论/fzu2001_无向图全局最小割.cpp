/*
  stoer-Wagner 算法求一个无向图的全局最小割,
  算法复杂度为O(n^3)
 */
#include<cstdio>
#include<cstring>
#define MAXN 510
#define inf 1000000000
using namespace std;
int w[MAXN];
int link[MAXN][MAXN];
bool inq[MAXN];
bool die[MAXN]; //die表示i是否已经被合并了
int n,m,left;
void input()
{
  int x,y,c;
  memset(link,0,sizeof(link));
  for(int i=0;i<m;i++)
  {
    scanf("%d%d%d",&x,&y,&c);
       x--;   y--;
    link[x][y]+=c;
    link[y][x]+=c;
  }
}
void contract(int s,int t)//压缩
{
    if(s>=0 && s<n && t>=0 && t<n){
  die[s]=true;
  for(int i=0;i<n;i++) if(link[s][i]){
      link[i][t]=(link[t][i]+=link[s][i]);
      link[s][i]=link[i][s]=0;
   }
   }
}
int mincut(int &s,int &t)  
{
  memset(inq,0,sizeof(inq));
  memset(w,255,sizeof(w)); //w[x]表示sigma{link[i][x] | i 属于 A} ,inq为true即在A中
  int start;
  for(start=0;start<n;start++) if(!die[start]) break; //任选一个初始点到A上
  inq[start]=true;
  for(int i=0;i<n;i++) if(!die[i]) w[i]=link[i][start];
  for(int i=0;i<left-1;i++) //直到把所有点都加入A位置,每次标记一个进去
  {
    int x=-1,Max=-inf;
    for(int j=0;j<n;j++) if(!die[j] && !inq[j] && w[j]>Max) Max=w[j],x=j; //每次选择一个不在A中的而且与A的link和最大的那个点加入到A中
    inq[x]=true;
    if(x==-1) return 0;
    s=t; t=x;          //记录加入顺序的最后两个
    for(int j=0;j<n;j++)  //每次加入x点到A之后都要更新
      if(!inq[j] && !die[j])   w[j]+=link[x][j];  
  }
  return w[t];//w[t]为最小割
}
void stoer()
{
  int min_cut=inf,tmp_cut;
  int s,t;
  memset(die,0,sizeof(die));
  left=n;
  s=t=-1;
  for(int i=0;i<n-1;i++)
  {
    tmp_cut=mincut(s,t);
    if(tmp_cut<min_cut) min_cut=tmp_cut;
    if(min_cut==0) break;
    contract(s,t);  //合并最后加入的那两个，注意会存在只有一个的情况，防止RTE
    left--;
  }
  if(min_cut==inf) min_cut=0;
  printf("%d\n",min_cut);
}
int main()
{
  freopen("fzu2001.in","r",stdin);
  int st;
  while(scanf("%d%d%d",&n,&m,&st)!=EOF)
  {
    input();
    stoer();    
  }
  return 0;
}
