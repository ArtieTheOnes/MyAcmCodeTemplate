/*
�󲻰���ĳЩ�Ӵ����ַ�������
����trieͼ��dp��ע��trieͼ�Ĺ���Ҫ��trie�����������
ͨ��bfs������ע������ڵ��ǵ�Ҫͬʱ����׺�ڵ��Ƿ��ǡ�
�����ת��Ϊ��root��ʼ�ڰ�ȫͼ����m���ķ�����
ע����ȷ�ҳ���ȫͼ
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=51; //��ĸ���С
const long maxm=101;//tire��״̬��
const long root=0;

//������
struct arr
{
	long h[maxm],len;

	arr()
	{
		memset(h,0,sizeof(h)), len=0;
	}

	void add(arr b)
    {
	   len=len>b.len?len:b.len;
	   h[1]+=b.h[1];
	   fo(i,2,len)
		   h[i]+=b.h[i]+h[i-1]/10, h[i-1]%=10;
       while (h[len]>=10)
		   h[++len]=h[len-1]/10, h[len-1]%=10;
    }

	void print()
	{
		if (len==0) { printf("0\n"); return;}
		fod(i,len,1) printf("%d",h[i]); printf("\n");
	}

} f[maxn][maxm],ans;

long trie[maxm][maxn],suffix[maxm],lab[maxm],tt;
long n,m,k,vis[maxm];
char s[maxn],apb[maxn];

void init()
{
	scanf("%d%d%d%*c",&n,&m,&k); 
	--n;
	fo(i,0,n) scanf("%c",&apb[i]);
}

/*trie��صĹ���***********************************************************************/
void make_trie_graph()
{
	long q[maxm],st=0,ed=0;
	suffix[root]=0;

	fo(i,0,n) 
		if (trie[root][i]) q[ed++]=trie[root][i], suffix[trie[root][i]]=0; //ע���ʼ��

	for (; st!=ed; st=(st+1)%maxm) {
		long p=q[st];
		fo(i,0,n) 
			if (trie[p][i]) {
		        q[ed]=trie[p][i], ed=(ed+1)%maxm;
				suffix[trie[p][i]]=trie[suffix[p]][i];
			    if (lab[suffix[trie[p][i]]]) lab[trie[p][i]]=1; //�ڵ�Ҫ��ǵ���һ����Ϊ���׺�ѱ��
	        } 
			else trie[p][i]=trie[suffix[p]][i];//��trie�в�����p���ַ�i�ıߣ����±�ָ��p�ĺ�׺�ڵ�i����
	}
}
void make_trie()
{
	fo(i,0,n-1) trie[root][i]=0;  tt=0; lab[root]=0; 
	fo(l,1,k) {
		scanf("%s",s);
		long p=root,w,len=strlen(s); 
		for (long i=0; i<len; ++i) {
			for (w=0; w<=n; ++w) if (apb[w]==s[i]) break;
			if (trie[p][w]==0) {
				trie[p][w]=++tt; lab[tt]=0;
				fo(j,0,n) trie[tt][j]=0; 
			}
			if (lab[p]) lab[trie[p][w]]=1;
			p=trie[p][w];
		}
		lab[p]=1;
	}
}
/************************************************************************************/

void cal(long step)
{
	fo(i,0,tt) 
		fo(j,0,n) 
		   if (!lab[trie[i][j]]) f[step][trie[i][j]].add(f[step-1][i]);
}
void solve()
{
	f[0][0].h[1]=1, f[0][0].len=1;
	//һ�������㣬��m�ܴ�����þ������
	fo(i,1,m) {
		memset(vis,0,sizeof(vis));
		cal(i);
	}
	fo(i,0,tt) ans.add(f[m][i]);
	ans.print();
}
int main()
{
	init();
	make_trie();
	make_trie_graph();
	solve();
	return 0;
}
