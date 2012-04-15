//avl--����ԭ����sbt��� 
#include<stdio.h>
#include<algorithm>
      #define Type int    //�˴�����Type������ 
      #define MAXN 100010   //������Χ 
      #define MAXM 100010   //��ѯ����Χ 
using namespace std;
struct avl
{
  int size; //size�����ݵĹ�ģ��n�ǵ�ǰ���еĽڵ���
  int s[MAXN],left[MAXN],right[MAXN],bal[MAXN];   //bal��ƽ������ 
  bool solve;//solve��һ�����е�һ���źţ���ʾ���������Ƿ��Ե�ǰ����ƽ�������в 
  Type data[MAXN];    
   avl (){  left[0]=right[0]=s[0]=bal[0]=size=0;data[0]=0;}  //���캯������ʼ�� 
    //�����������÷� 
    /* void leftrotate(int &);    //������ת 
    void rightrotate(int &);
    void insert(int &,Type &);     //������� 
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
//tran������������ƽ�����ӵļ���
inline int tran(int x,int step)
{  int tmp[]={1,-1,0,1,-1},*p=tmp+2;
   if (x==0) return 0;    //���left[right[x]] ��right[left[x]]ƽ������Ϊ0
   else return p[x+step];// ��ô��ת֮��x,��left[x]��right[x]ƽ�����Ӷ�Ϊ0 
}                         //�������ҳ��Ĺ���������    
//���Ĳ�����maintain
void maintain(int &x)
{
	int y;
   if (bal[x]==-2)
   {
       if (bal[left[x]]==-1) {    //ֱ������ת 
	      bal[x]=bal[left[x]]=0;   
	     rightrotate(x);	     
       }else if (bal[left[x]]==1) {
       	   y=right[left[x]];	 //�Ȱ��չ��ɼ�����ת���ƽ�����ӣ�����ת 
		    bal[left[x]]=tran(bal[y],1);
			bal[x]=tran(bal[y],-1);	 
			bal[y]=0;  
		  leftrotate(left[x]);
		  rightrotate(x);  
        }else {    //�������Ҫɾ�����˲�����Ҫ�����ǵ�����ɾ������֮��
		           //�ᵼ����������ķ�������Ҫ���п���                
		   bal[x]=-1;bal[left[x]]=1;
		   rightrotate(x);
		}
   }
   else {
       if (bal[right[x]]==1){
       	  bal[x]=bal[right[x]]=0;
       	  leftrotate(x);	   
	   } else if (bal[right[x]]==-1){
	       y=left[right[x]];	       
	       bal[right[x]]=tran(bal[y],-1);
	       bal[x]=tran(bal[y],1);
	       bal[y]=0;
	       rightrotate(right[x]);
	       leftrotate(x);
	   } else {
	      bal[x]=1;bal[right[x]]=-1;
	      leftrotate(x);
	   }
    }   
}
 //����ڵ�
void  insert(int &x,Type &w) 
    {
	   if (x==0){
		   x=++size;
		   data[x]=w;
		   left[x]=right[x]=bal[x]=0;
		   s[x]=1;  
		   solve=false;      //�ղ������ܻᵼ�²�ƽ�� 
		} else { 
		    ++s[x]; 
		    if (w<data[x])  insert(left[x],w);
		     else insert(right[x],w);
		   if (!solve){     //�����������Ե�ǰ��ƽ�������в�����д��� 
               bal[x]+=(w>=data[x])-(w<data[x]);//�޸�ƽ������ 
              if (bal[x]>1||bal[x]<-1) maintain(x);
		                      //����ƽ���һ�����Ը��ڵ������в 
			  solve=bal[x]==0;//�����������е������1��1ʹ��ǰ����ƽ�⣬
			 }                 //��ôҲ����Ը��ڵ������в	   			  	 			 	       
		}
    }
//ɾ������ 
Type Delete(int &x,Type w)
{   
    Type tmp;
    --s[x];
    if (data[x]==w||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)
     {
	    tmp=data[x];
	     if (left[x]==0||right[x]==0){    //ֱ��ɾ�������ҿ��ܶԸ��ڵ������в 
	       x=left[x]+right[x],solve=false;            
	     }else {
		    data[x]=Delete(left[x],data[x]); //ת�޽ڵ������ɾ�� 
	       if (!solve){        
	       	  if (++bal[x]>1) maintain(x);//��ƽ���������������������������ͬ�� 
                         //ƽ�����֮��ǰ���ĸ߶Ȼ��С���ǻ���в�����ڵ��ƽ�� 
	       	  solve=bal[x]!=0;//�����Ϊɾ����ƽ��������0��Ϊ1��-1����ô���ĸ߶�
                             //�ǲ���ģ�����Ը��ڵ������в,�෴�����ͨ������
							//��ֱ�Ӽ�1���1�ﵽ0�Ļ������ĸ߶Ⱦͼ�С�ˣ�����в		  			
			}		  
         }        
	 }
     else {
    	tmp=w<data[x]?Delete(left[x],w):Delete(right[x],w);
		if (!solve){
		  bal[x]+=(w<data[x])-(w>=data[x]);//�޸�ƽ�����ӣ�����Ҫ��ס�����ɾ���Ĳ�ͬ 
		  if (bal[x]>1||bal[x]<-1)  maintain(x);//���������ͺ�����һ�� 
		  solve=bal[x]!=0; 
		}   	    	
     }
   return tmp; 
}
//�������е�w�� 
Type find_th(int &x,int w)
{
   if (w==s[left[x]]+1)  return data[x];
   else if (w<=s[left[x]])	return find_th(left[x],w);
   else return find_th(right[x],w-s[left[x]]-1); 	
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
   avl zoo;
    int i,j;
	  scanf("%d%d",&n,&m);      
	  for( i=0;i<n;++i) scanf("%d",&abl[i+1]);	
	  for( i=0;i!=m;++i) scanf("%d%d%d",&itr[i].x,&itr[i].y,&itr[i].z),itr[i].num=i;
      sort(itr,itr+m,cmp);

	  root=0;
	 for ( i=itr[0].x;i<=itr[0].y;++i)
	      zoo.insert(root,abl[i]);
       for ( i=1;i<m;++i)
	   {
	   	  ans[itr[i-1].num]=zoo.find_th(root,itr[i-1].z);
	       for ( j=itr[i-1].x;j<=min(itr[i-1].y,itr[i].x-1);++j)
	           zoo.Delete(root,abl[j]);
	       for ( j=max(itr[i-1].y+1,itr[i].x);j<=itr[i].y;++j)
		       zoo.insert(root,abl[j]);     
	   }      
      ans[itr[m-1].num]=zoo.find_th(root,itr[m-1].z);
	  for ( i=0;i<m;++i)	
		  printf("%d\n",ans[i]);		  
   return 0;
}

