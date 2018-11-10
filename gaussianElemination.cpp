#include<iostream>

using namespace std;

int main()
{
	double b[5][5]={
			{5,2,8,1,3},
			{2,8,1,3,9},
			{2,2,4,9,7},
			{7,2,1,5,6},
			{6,8,9,2,4}
	       	       };

	double a[5][5];

	double c[5]={10,2,5,9,4};
	double d[5];

	for(int i=0;i<5;i++)
	{
		if(i==0)
		{
			d[i]=c[i];
		}
		else
		{
			d[i]=0;
		}
		for(int j=0;j<5;j++)
		{
			if(i==0)
			{
				a[i][j]=b[i][j];
			}
			else
			{
				a[i][j]=0;
			}
			cout<<b[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<" gaussian elemination "<<endl;

	for(int k=0;k<4;k++)
	{
		for(int i=k+1;i<5;i++)
		{
	
			for(int j=0;j<5;j++)
			{
		
				a[i][j]=b[i][j]-((b[i][k]/b[i-1][k])*b[i-1][j]);
		
			}
			d[i]=c[i]-((b[i][k]/b[i-1][k])*c[i-1]);
			//cout<<" b[1][0] "<<a[i][0]<<endl;	
		}

		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				b[i][j]=a[i][j];
			}
			c[i]=d[i];
		}		

	}

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}

	cout<<"RHS "<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<d[i]<<endl;
	}

	//X values
	double x[5]={0,0,0,0,0};
	double m=0;
	for(int i=4;i>=0;i--)
	{
		for(int j=4;j>=0;j--)
		{
			m=m+a[i][j]*x[j];
		}
		x[i]=(d[i]-m)/a[i][i];
	}
	cout<< " solution : "<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<x[i]<<endl;
	}

	return 0;
}
