//candy
/*
   �뿴2003����Ҽ�ѵ������  ��֪��  
   ��ǳ̸�ü���˼��������Ӿ������⡷ 
   ��O��NM����ʵ��������Ӿ���
   
   �Ҷ������������⣺������Ϊ���ģ���������չ��ֱ����ס����Ϊֹ����ס��
   λ�ÿ����ǵ�ǰ�У�Ҳ������֮ǰ���У���ô�����е����߶�����һ���
   ������Ч�Ӿ����Ȼ�����档 
*/
#include<stdio.h>
#include<memory>
#define MAXN 1001   //��Χ 
using namespace std;
int s[MAXN][MAXN];
int l[MAXN],r[MAXN],height[MAXN];
int n,m,leftmost,rightmost,acc,res,now,i,j;
int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	scanf("%d%d",&n,&m);
	 for ( i=1;i<=n;++i)
	     l[i]=1,r[i]=m,height[i]=0; //��ʼ��ʱ�����߸߶ȶ�Ϊ0����˿������쵽���� 
    memset(s,0,sizeof(s));//s�Ǽ�¼��i,jΪ���½ǵľ������ֵ 
		 res=0;
    for ( i=1;i<=n;++i)
    {
	   leftmost=1; 
	   acc=0;
        for ( j=1;j<=m;++j)      
        {
		   scanf("%d",&now);
		   acc+=now;
		   s[i][j]=s[i-1][j]+acc;
		    if (now){             // �����ǰ�����ϰ��� 
			    ++height[j];     //j�еĸ߶�+1 
		       if (leftmost>l[j]) l[j]=leftmost; //�޸Ŀ�ס��ǰ���ߵ����λ�� 
		    	}
				else {          //�����ǰ���ϰ��� 
			    height[j]=0;     
			    leftmost=j+1;  //��ôj֮��ĵ�����߿��ܱ�j��ס�����Լ�¼���� 
				l[j]=1;r[j]=m;  //��Ȼ���߸߶���0����ô��û�п��Կ�ס�ĵ� 
     //�˴�ʹ�ÿ��Կ�סj���ϰ�������j��height��Χ���ڵĵ㣬��height��ʼ���¼������ұ߽� 
			 }
		 }
	   rightmost=m;
        for (j=m;j>=1;--j)
		{
		    if (height[j]){     //��������ϰ��� 
			   if (rightmost<r[j]) r[j]=rightmost;  // �޸Ŀ�ס��ǰ�����ұߵ�λ�� 
             acc=s[i][r[j]]-s[i-height[j]][r[j]]-s[i][l[j]-1]+s[i-height[j]][l[j]-1];
             //ͳ���Ӿ���� 
              if (acc>res)  res=acc;
			}
			 else {
			    rightmost=j-1;//������ϰ��㣬��¼��ǰ���ұ߿��ܱ���ס��λ�� 
			 }
		}
	}
	printf("%d\n",res);
   return 0;
}
