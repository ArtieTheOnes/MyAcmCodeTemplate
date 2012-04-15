/*���ò��������rela[x]��ʾx�������ڲ����root�Ĺ�ϵ
Ȼ��ͨ��·��ѹ�������¹�ϵ��Ϊ�˷��㲻��ÿ�����������
��ÿ��ѯ�ʶ���x��y�Ƶ������rootλ�ã��������ж���ϲ�*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=50010;

long fa[maxn],rela[maxn];
long n,m;

//·��ѹ����ͬʱ���¹�ϵ��������¹�ϵ�Ĺ��ɿ�ͨ���б����
long renew(long x) 
{
	long root;
	if (fa[x]) {
		root=renew(fa[x]);
		if (fa[x]!=root) rela[x]=(rela[x]+rela[fa[x]])%3;//��������Ĺ�ϵ
		fa[x]=root;
		return root;
	}
	return x;
}
void move_root(long x)//��x�Ƶ�root��λ�ã�ͬʱ����ù�ϵ
{
	if (rela[x]==0) rela[fa[x]]=0;
	else rela[fa[x]]=3-rela[x];
	fa[fa[x]]=x; fa[x]=0;
}
void solve()
{
	long d,x,y,ans=0;
	memset(fa,0,sizeof(fa));
	fo(l,1,m) {
		scanf("%d%d%d",&d,&x,&y);
		if (x>n || y>n) { ++ans;  continue; }
		if (x==y) {
			if (d==2) ++ans;
			continue;
		}
		/*·��ѹ����xҪ�������ڲ����root�µĶ��ӣ�Ҫ���Ǿ���root�����Ƕ������Ƶ�root
		���������x��y��ͬһ�������y��Ϊroot��xΪ�����*/

		//����renew������move_root������x��y�����γɶ��Ӹ��׹�ϵ����x��y��ͬһ�����
		renew(x); if (fa[x]) move_root(x); 
		renew(y); if (fa[y]) move_root(y);
		//�ж��Ƿ�Ϊ�ٻ�
		if (fa[x]==y && ( (d==1 && rela[x]!=0) || (d==2 && rela[x]!=1)) ) {++ans; continue;}
        //����֮ǰ�Ĳ������ϲ�ֱ�Ӵ���rela��fa����
		if (fa[x]!=y) rela[x]=d-1, fa[x]=y;
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d%d",&n,&m);
	solve();
	return 0;
}
