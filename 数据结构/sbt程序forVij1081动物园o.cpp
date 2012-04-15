//SBT��ʵ�� 
#include<stdio.h>
#include<algorithm>
      #define Type int    //�˴�����Type������ 
      #define MAXN 300010   //������Χ 
      #define MAXM 100010   //��ѯ����Χ 
using namespace std; 
struct sbt
{ 
  int size; //size�����ݵĹ�ģ��n�ǵ�ǰ���еĽڵ���
  int s[MAXN],left[MAXN],right[MAXN];
  Type data[MAXN];    
    sbt (){  left[0]=right[0]=s[0]=size=0;data[0]=0;}
   /* void leftrotate(int &);
    void rightrotate(int &);
    void insert(int &,Type &);
    Type Delete(int &,Type );//delete��ͷҪ��д������͹ؼ���delete��ͻ 
    void maintain(int &,bool);  
	Type find_th(int &x,int w); //�ҳ����е�w����ֵ 
	int find_pos(int &x,Type &w); //�ҳ�w�����е�λ�ã��������򷵻�-1  
	*/
//����ת����
void leftrotate(int &x)
{
   int y=right[x];
   right[x]=left[y];
   left[y]=x;
   s[y]=s[x];
   s[x]=s[left[x]]+s[right[x]]+1;
   x=y;
} 
//����ת����
void rightrotate(int &x)
{
    int y=left[x];
    left[x]=right[y];
    right[y]=x;
    s[y]=s[x];
    s[x]=s[left[x]]+s[right[x]]+1;
    x=y;
} 
 //����ڵ�
void insert(int &x,Type &w) 
    {
	   if (x==0)
        {
		   x=++size;
		   data[x]=w;
		   left[x]=right[x]=0;
		   s[x]=1;
		} else { 
		    ++s[x]; 
		    if (w<data[x]) insert(left[x],w);
			 else insert(right[x],w);
		  maintain(x,w>=data[x]); 
		}
    }
//ɾ������ 
Type Delete(int &x,Type w)
{
    --s[x];
    if (data[x]==w||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)
     {
	    Type tmp=data[x];
	     if (left[x]==0||right[x]==0)
	       x=left[x]+right[x];
         else data[x]=Delete(left[x],data[x]);
        return tmp;
	 }
     else if (w<data[x])  return Delete(left[x],w);
       else return Delete(right[x],w);
}
 //���Ĳ�����maintain
void maintain(int &x,bool w)
	{
	  if (!w) 
	  {
	     if (s[left[left[x]]]>s[right[x]]) 
		 rightrotate(x);
		  else if (s[right[left[x]]]>s[right[x]])
		  	{
		     leftrotate(left[x]);
		     rightrotate(x);
		    } 
		  else return ;
	   }else if (s[right[right[x]]]>s[left[x]]) 
	        leftrotate(x);
	     else if (s[left[right[x]]]>s[left[x]])
	     {
		    rightrotate(right[x]);
		    leftrotate(x);
		 }
	    else return ;
      maintain(left[x],false);
      maintain(right[x],true);
      maintain(x,false);
      maintain(x,true);
	}
//�������е�w�� 
Type find_th(int &x,int w)
{
   if (w==s[left[x]]+1)  return data[x];
    else if (w<=s[left[x]])
	{ 
	return find_th(left[x],w);
	} else 
	{
	return find_th(right[x],w-s[left[x]]-1); 
	}
}
//�ҳ�w�����е�λ��
int find_pos(int &x,Type &w)
{
    if (x==0||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)return -1;
      else if (w==data[x])return s[left[x]]+1;
	  	else {
	      int tmp=find_pos(w<data[x]?left[x]:right[x],w);
         if (tmp==-1) return -1;
          else  return tmp+(w<data[x]?0:s[left[x]]+1);
	  }
} 

};
//ʵ�����г��� 
struct interval{
     int x,y,z,num; 
  };
int root=0,n,m,i,l,r,j;
int abl[MAXN];
interval itr[MAXM];
int ans[MAXM];
 
bool cmp(const interval &p1,const interval &p2) 
{  return p1.x<p2.x;   }
inline int  max(int x,int y) {  return x>y?x:y;}
inline int  min(int x,int y)  {  return x<y?x:y;}
int main()
{    
   freopen("zoo.in","r",stdin);
   freopen("zoo.out","w",stdout);
   sbt zoo;
	  scanf("%d%d",&n,&m);      
	  for(int i=0;i<n;++i) scanf("%d",&abl[i+1]);	
	  for(int i=0;i!=m;++i) scanf("%d%d%d",&itr[i].x,&itr[i].y,&itr[i].z),itr[i].num=i;
      sort(itr,itr+m,cmp);

	  root=0;
	 for (int i=itr[0].x;i<=itr[0].y;++i)
	      zoo.insert(root,abl[i]);
       for (int i=1;i<m;++i)
	   {
	   	  ans[itr[i-1].num]=zoo.find_th(root,itr[i-1].z);
	       for (int j=itr[i-1].x;j<=min(itr[i-1].y,itr[i].x-1);++j)
	           zoo.Delete(root,abl[j]);
	       for (int j=max(itr[i-1].y+1,itr[i].x);j<=itr[i].y;++j)
		       zoo.insert(root,abl[j]);     
	   }      
      ans[itr[m-1].num]=zoo.find_th(root,itr[m-1].z);
	  for (int i=0;i<m;++i)	
		  printf("%d\n",ans[i]);	  
   return 0;
}

