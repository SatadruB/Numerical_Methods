	/* LU Decomposition */
#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include<string>

using namespace std;

int main(int argc, char* argv[] )
{
	ifstream InputFile;
	string lineRead;
	string A_Matrix;
	string B_Vector;

	if(argc==3)
	{
		A_Matrix=argv[1];
		B_Vector=argv[2];
	}
	else
	{
		cout<<" [ ./Executable ] [Input File Path for square Matrix ] [Input File Path for Vector]"<<endl;
		return -1;
	}

	InputFile.open(A_Matrix.c_str());
	int lineCount=0;
	while(getline(InputFile,lineRead))
	{
		lineCount++;
	}
	InputFile.close();

	int truncatedSize=lineCount;
	vector<vector<double> > TruncatedGlMatrix(truncatedSize, vector<double> (truncatedSize));
	vector<double> TruncatedForce(truncatedSize);
	vector<vector<double> > L(truncatedSize, vector<double> (truncatedSize));
	vector<vector<double> > U(truncatedSize, vector<double> (truncatedSize));
	vector<int> diag(truncatedSize);

	

	//InputFile.open(A_Matrix.c_str());
	InputFile.open("StiffnessMatrix");
	for(int i=0;i<truncatedSize;i++)
	{
		for(int j=0;j<truncatedSize;j++)
		{
			InputFile>>TruncatedGlMatrix[i][j];
			//cout<<TruncatedGlMatrix[i][j]<<"\t";
		}
		//cout<<endl;
	}
	InputFile.close();

	//InputFile.open(B_Vector.c_str());
	InputFile.open("Force");
	for(int i=0;i<truncatedSize;i++)
	{
		InputFile>>TruncatedForce[i];
		//cout<<TruncatedForce[i]<<endl;
	}
	InputFile.close();

	for(int i=0;i<truncatedSize;i++)
	{
		for(int j=0;j<truncatedSize;j++)
		{
			if(i==j)
			{
				L[i][j]=1;
				diag[i]=i;
			}
			else
			{
				L[i][j]=0;
			}

			if(i==0)
			{
				U[i][j]=TruncatedGlMatrix[i][j];
			}
			else
			{
				U[i][j]=0;
			}
		}
	}

	for(int k=1;k<truncatedSize;k++)
	{
		// Evaluating L 
		for(int i=0;i<diag[k];i++)
		{
			double addition_L=0;
			for(int j=0;j<truncatedSize;j++)
			{

				addition_L=addition_L+(L[k][j]*U[j][i]);
			}


			L[k][i]=(TruncatedGlMatrix[k][i]-addition_L)/U[i][i];	
		}
	
		// Evaluating U
		for(int ll=diag[k];ll<truncatedSize;ll++)
		{
			double addition_U=0;
			for(int jj=0;jj<truncatedSize;jj++)
			{
				addition_U=addition_U+(L[k][jj]*U[jj][ll]);
			}
			U[k][ll]=(TruncatedGlMatrix[k][ll]-addition_U)/L[k][diag[k]];
		}		

	}
	cout<<endl;
	cout<<" Lower Triangular Matrix :"<<endl;
	for(int i=0;i<truncatedSize;i++)
	{
		for(int j=0;j<truncatedSize;j++)
		{
			cout<<L[i][j]<<'\t';
		}
		cout<<endl;
	}

	cout<<endl;

	cout<<" Upper Triangular Matrix :"<<endl;
	for(int i=0;i<truncatedSize;i++)
	{
		for(int j=0;j<truncatedSize;j++)
		{
			cout<<U[i][j]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
	//Forward Substitution
	vector<vector<double> > x(truncatedSize,vector<double> (2));
	double m;

	for(int i=0;i<truncatedSize;i++)
	{
		m=0;
		for(int j=0;j<truncatedSize;j++)
		{
			m=m+L[i][j]*x[j][1];
		}
		x[i][1]=(TruncatedForce[i]-m)/L[i][i];
	}
	/*for(int i=0;i<truncatedSize;i++)
	{
		cout<<"Backward :"<<x[i][1]<<endl;
	}*/

	// Backward Substitution
	vector<vector<double> > y(truncatedSize,vector<double> (2));
	double mm;
		for(int i=(truncatedSize-1);i>=0;i--)
		{
			mm=0;
			for(int j=(truncatedSize-1);j>=0;j--)
			{
				mm=mm+U[i][j]*y[j][1];
			}
			y[i][1]=(x[i][1]-mm)/U[i][i];
		}

	cout<<" Solution :"<<endl;
	for(int i=0;i<truncatedSize;i++)
	{
		cout<<y[i][1]<<endl;
	}

	return 0;
}
