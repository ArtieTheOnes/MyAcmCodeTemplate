#include<cstdio>
#include<cstring>
#define MAXN 100010
using namespace std;
int n;
int phi[MAXN];
void all_phi(int n)
{
    memset(phi,0,sizeof(phi));
	phi[1]=1;
	for(int i=2;i<=n;++i) // O(nlogn)
	  if(!phi[i])//i������
	{
	    for(int j=i;j<=n;j+=i)
		{
			if(!phi[j]) phi[j]=j;		     
			phi[j]=phi[j]/i*(i-1);
		}
	}
}
int main()
{
	scanf("%d",&n);
	  all_phi(n);
	  for(int i=1;i<=n;++i)	 
		    printf("%d  %d\n",i,phi[i]);	 
	return 0;
}
