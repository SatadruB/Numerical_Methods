#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

int main()
{
    
    //vector<vector<double> > m(100,vector<double> (100));
   double m[5][5]={
                {10,-1,2,0,6},
                {-1,11,-1,3,25},
                {2,-1,10,-1,-11},
                {0,3,-1,8,15}
};
    
    vector<vector<double> > x(100,vector<double> (100));
    int k=0;
    double add,error;

    for(int i=0;i<4;i++)
    {
        x[0][i]=0;
    }
    
    do
    {
        for(int h=0;h<2;h++)
        {
            for(int i=0;i<4;i++)
            {
                add=0;
                for(int j=0;j<4;j++)
                {
                    add=add+(m[i][j]*x[k][j]);   
                }
                add=(m[i][4]-(add-m[i][i]*x[k][i]))/m[i][i];
                x[k][i]=add;
                x[k+1][i]=x[k][i];
              
            }
            
            k++;
        
        }
        error=(x[k][1]-x[k-2][1]);
        error=fabs(error);
    
    }while(error>0.00001);
  
    for(int i=0;i<4;i++)
    {
        cout<<" The value: "<<x[k][i]<<endl;
    }
    return 0;
}