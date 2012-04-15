#include <iostream>
using namespace std;

const maxn=100;
long b[maxn],m[maxn];

long cal_gcd(long a, long b, long &x, long &y) {//����ax+by=gcd��a,b)���ؽ� 
    if (b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        long tx, ty, d;
        d = cal_gcd(b, a%b, tx, ty);
        x = ty; y = tx-a/b*ty;
        return d;
    }
}

/*ģ����ax��b��mod m������ؽ�x0��� ת��Ϊx��x0��mod  m')
������ m= m'*gcd(a,b)*/

long cal_mo(long a, long b, long m) //����ax��b��mod m�����ؽ� 
{
    long x,y,d;
    d=cal_gcd(a,m,x,y);
    if (b%d==0) return (x*(b/d))%m //�ؽ⣬�Ӽ�m�����������õ����н� 
    else return 0;//�޽� 
}

long cal_no_sys()//����ģ���Է�����x��bi��mod mi������n�����̣� 
{
    long x,y,d,m0=m[0],b0=b[0],i;
    for (i=1; i!=n; ++i) {//�������������ϲ�,
      d=cal_gcd(m0,m[i],x,y);
      if ((b0-b[i])%d==0){
        b0=x*(b0-b[i])/d+b0;
        m0=m0*m[i]/d; //m0��m[i]����С������ 
        b0=b0%m0; //�������̺ϲ�Ϊx��b0��mod m0�� 
      } else return 0; //�޽� 
    } 
    return b0; //��������ؽ⣬�Ӽ�m0���������õ����н� 
}
int main()
{
    
}
