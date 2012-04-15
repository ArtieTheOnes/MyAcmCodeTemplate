//͹����graham�㷨
#include<stdio.h>
#include<math.h>
#include<algorithm>
#define MAXN 100010             
#define MAXNUM 2000000000
using namespace std;
typedef long long  int64;     //�ض��壬�Է�������� 
struct  point
      { 
	     int x,y;	      
	     point(int ix,int iy):x(ix),y(iy){} //���캯��������������ʱ���� 
	     point():x(0),y(0){}      //����Ĺ��캯������������ʱ�ᷢ������ 
		  int64 operator * (const point &that) const{  //���
		      return (int64)x*that.y-(int64)y*that.x;
		  }
		  point operator-(const point &that) const{	 	 
             return  point(x-that.x,y-that.y);		 
		  }
		  point operator+(const point &that)  const{
             return  point(x+that.x,y+that.y);            
		  }
	  };

point dot[MAXN],stack[MAXN];//dot�ǵ�����飬stack��graham scanʱ����ʱ��ջ 
int n;
inline  int64 sqr(int x) {return (int64)x*x; } 
inline int64 dist(const point &p1,const point &p2)
   { return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);   }
void init()
{
   point zero(MAXNUM,MAXNUM);  //����Ѱ��������������ʱ���� 
   int loca,x,y;           //loca���Ǹ�����λ�� 
   scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
       scanf("%d%d",&x,&y);
       dot[i].x=x;dot[i].y=y;
        if (dot[i].y<zero.y||dot[i].y==zero.y&&dot[i].x<zero.x)    
           zero=dot[i],loca=i;
    }
    zero=dot[loca];  dot[loca]=dot[0];  dot[0]=zero;     
}    
bool cmp(const point &p1,const point &p2)    
{    								    //sort�ıȽϺ���������ʱ�����̵����� 
    int64 m=p1*p2;
    return m>0||
	m==0&&sqr(p1.x)+sqr(p1.y)<sqr(p2.x)+sqr(p2.y);
}
void graham()
{
    int top,i;   
    if (n<=2) return ;
    for (i=1;i<n;++i)  dot[i]=dot[i]-dot[0];
    sort(dot+1,dot+n,cmp);         //�������򣬰���cmp�Ķ��壬����֮������ʱ���         
    for (i=1;i<n;++i)  dot[i]=dot[i]+dot[0];    
      stack[0]=dot[0];stack[1]=dot[1];      
       top=1;
       for (i=2;i<n;++i)  //�˴�������2����0��ÿһ��
          {
		      while (top>0&&(dot[i]-stack[top-1])*(stack[top]-stack[top-1])>=0)    
		         --top;					// �ǵô˴���while 
              stack[++top]=dot[i];
		  }	
    n=top+1;
	for (i=0;i<n;++i) dot[i]=stack[i];   //��͹�����Ƶ�dot��ȥ 
}
//***************************************************************
void area()   //�����
{
   int next,i;
   int64 area=0;      
   for ( i=0;i<n;++i)   
   {
       area+=(dot[i]*dot[(i+1)%n])/2;         	         
   }
   printf("%d\n",area/50);  //��ʱ�룬��������ֵ 
}
//*****************************************************************
//����Զ���� 
double height(const point &p1,const point &p2,const point &p3)
{
    double area=(p2-p1)*(p3-p1);  
    double len=sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
    len=sqrt(len);
    return area/len;
}
template<class Type>
inline Type max(Type &p1,Type &p2)
{
   return p1>p2;
}
void farpair()    
{
    int64 maxl=0;
    int i,j,k;
    if (n==1)maxl=0; 
	 else if (n==2) maxl=dist(dot[0],dot[1]);
	 else {
	 	k=2;
        for (int i=0;i<n;++i)
        {
		   while (height(dot[i],dot[(i+1)%n],dot[k])<height(dot[i],dot[(i+1)%n],dot[(k+1)%n]))
		     k=(k+1)%n;
            maxl=max(maxl,max(dist(dot[i],dot[k]),dist(dot[(i+1)%n],dot[k])));            
         }
	 }    
   printf("%.2lf",sqrt(double(maxl)));
}
//*****************************************************************
int main()
{
    //freopen("farcow.in","r",stdin);
    // freopen("farcow.out","w",stdout);   
    init();	 
    graham();
   // farpair(); 
    return 0;
}
