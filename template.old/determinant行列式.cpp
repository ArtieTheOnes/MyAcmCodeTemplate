#include<iostream>
using namespace std;

const int maxn=/*����ʽ��С*/ 
const int mo=/*��ȡ��*/ 

int det[maxn][maxn],n,ans;

void make_det()
{
    /*��������ʽ*/ 
}


void cal_det()/*ת��Ϊ������������ʽ*/ 
{
     int i,j,k,t,swap;
     ans=1;  
     
     for (i=0; i!=n; ++i)
       for (j=0; j!=n; ++j) det[i][j]%=mo;
       
     for (i=0; i!=n; ++i) { /*��*/ 
       for (j=i+1; j!=n; ++j) /*��*/
         while (det[j][i]!=0) { /*շת����Ԫ*/ 
           t=det[i][i]/det[j][i];
           ans=-ans; /*�����к�����ʽֵ�为*/ 
           for (k=i; k!=n; ++k) {
             det[i][k]-=det[j][k]*t;
             
             /*������*/ 
             swap=det[i][k];
             det[i][k]=det[j][k];
             det[j][k]=swap;
           }
       }
       if (det[i][i]==0) {
         ans=0;
         break;
       } else ans=(ans*det[i][i])%mo;
     }    
     cout << ans << endl;    
}

int main()
{

    make_det();
    cal_det();

}
