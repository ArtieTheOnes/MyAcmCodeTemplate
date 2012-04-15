//��
#include<iostream>
#include<map>
   #define Type int  //����Խڵ��������� 
   #define MIN_HEAP  //���������С�� 
   #define EXTREME -1 //���ڴ�С�ѵļ���ֵ���壬��ɾ��������Ҫ�õ� 

using namespace std;
class heap
{
   private:
     struct HeapNode {
      Type d;         //�ڵ�ֵ 
      map<Type,int>::iterator pos;
	  //ָ��map���Ըýڵ�ֵΪ�ؼ��ֵ��Ǹ���ĵ�����(ʵ���Ͼ���ָ��) 
	 };
     int size,len; //size�����ݹ�ģ���ڳ�ʼ��ʱҪ���������ģֵ
	              //len�ǵ�ǰ���еĽڵ��� 
     HeapNode *hp;  //hp���Ƕѽڵ㼯 
     map<Type,int> rpos; //rpos��һ��map����һ���Ƕ��нڵ�ֵ���ڶ���
	                     //�Ǹýڵ�ֵ�ڶ���λ�� 
    public:
     heap(int);
     void insert(Type &);    
     void pop();             //ɾ���Ѷ�ֵ 
     void Delete(Type &);    //ɾ��ֵΪType�Ľڵ� 
     void down(int);     
     void up(int);
     void swap(HeapNode &,HeapNode &);
     Type top();             //���ضѶ�ֵ 
     bool comp(Type &x,Type &y) //�����С�ѵıȽϣ�
	 {
	 	#ifdef MIN_HEAP
	     return x<y;
        #else ifdef MAX_HEAP
         return x>y;
        #endif;
	 }
};
heap::heap(int InitSize)
{
	size=InitSize+1;
	len=0;
	hp=new HeapNode[size+1];	
}
void heap::insert(Type &x)
{
	hp[++len].d=x;
	hp[len].pos=(rpos.insert(pair<Type,int>(x,len)).first);   
	up(len); 
}
void heap::pop()
{
    if (len>0)
    {
	    rpos.erase(hp[1].pos);
	    hp[len].pos->second=1;
	    hp[1]=hp[len--];
	    down(1);
	}
}
void heap::Delete(Type &x)
{
   int w=rpos[x];
   hp[w].d=EXTREME;
   up(w);
   pop();   
}
void heap::swap(HeapNode &x,HeapNode &y)
{
	HeapNode tmp=x;x=y;y=tmp;   
}
Type heap::top()
{
   if (len>0) return hp[1].d;
    else return -1;
}
void heap::down(int x)
{
    int y;
	if (x*2<=len) {
    if (x*2==len) y=x*2;
     else if (comp(hp[x*2].d,hp[x*2+1].d))  y=x*2;
      else y=x*2+1;
     if (comp(hp[y].d,hp[x].d)) {
     	hp[x].pos->second=y;
     	hp[y].pos->second=x;
     	swap(hp[x],hp[y]);
     	down(y);
	 }else return;
	}
}
void heap::up(int x)
{
  if (x>1){
     int y=x/2;
     if (comp(hp[x].d,hp[y].d)) {
     	hp[x].pos->second=y;
     	hp[y].pos->second=x;
     	swap(hp[x],hp[y]);
     	up(y);
	 }else return;
  }
}
int main()
{
	heap a(100000);
	for(int i=1;i<=100000;++i)
	   a.insert(i);
     for (int i=1;i<=100000;++i)
	    a.pop();
     cout<<a.top()<<endl;
   return 0;
} 

