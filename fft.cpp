#include<iostream>
#include<complex>
#include<cmath>
#include<iomanip>

using namespace std;
double PI=acos(-1);
complex<double> *btf(complex<double> *z,int n,int stage); //complex exponential funtion
complex<double> w(int num,int n);
int large(int *array,int length);
void plot(complex<double> *array,int n);
int small(int *array,int length);
void delta(int *array,int big,int least,int length);
int *binary(int n);
int big=0;
int least=0;
int main()
{
	cout<<std::fixed<<setprecision(1);
	int n=0;
	cout<<"sequence size"<<endl;
	cin>>n;
	complex<double> temp=0;
	complex<double> array[n],*p;
	int *b,bitrev[n];
	
	b=binary(n); 	//returned array is stored in ptr p.
	
	for(int j=0;j<n;j++)	//copying ptr values to new array.
		{
			//array[j]=*(p+j);
			bitrev[j]=*(b+j);	//bit reversal order.
		}

	cout<<"enter the sequence"<<endl;
	for(int j=0;j<n;j++) //storing input sequence in bit reversed order
	{
		cin>>temp;
		int t=bitrev[j];
		array[t]=temp;
		//cout<<array[j]<<" ";
	}
	int max_stage=log(n)/log(2);
	cout<<"max_stage "<<max_stage<<endl;
	int stage=1;
	for(int k=0;k<max_stage;k++)
	{
		p=btf(array,n,stage);
		for(int j=0;j<n;j++)	//copying ptr values to new array.
			array[j]=*(p+j);
		//cout<<"stage "<<stage<<" ";
		stage++;
	}

	cout<<endl;
	plot(array,n);
		for(int j=0;j<n;j++)
	{
		cout<<array[j]<<" ";
	}
	cout<<endl;
	return(0);
}
complex<double> *btf(complex<double> *z,int n,int stage)
{
	complex<double> temp=0+0i;
	int s=pow(2,stage-1);
	int t=0;
	int count=0;
	int max_count=pow(2,stage-1);
	
		for(int j=0;j<n;j++)
		{	
			count++;
			temp=z[j];
			z[j]=z[j]+z[j+s]*w(t,n); //s depends on stage
			z[j+s]=temp-z[j+s]*w(t,n);

			if(stage!=1)
				t+=n/pow(2,stage);
			cout<<stage<<" "<<w(t,n)<<endl;
			if(count==max_count)
			{
				j+=s;
				count=0;
				t=0;
			}
		}
		cout<<"skip "<<s<<" "<<pow(2,stage)<<endl;
		for(int j=0;j<n;j++)		//display result after each stage
		{	
			cout<<z[j]<<" ";
		}
		cout<<"exiting stage "<<stage<<endl;
	return(z);
}

complex<double> w(int num,int n)
{
	double t=2*PI*num/n;
	complex<double> z=cos(t)-1i*sin(t);
	//cout<<z<<endl;
	return (z);
}

int *binary(int n)
{
	int len=0;
	len=log(n)/log(2);
	//cout<<len<<endl;
	int array[n][len]; //n x len array for storing the len bit binary rep of the n numbers.
	 int array2[n];
	for(int j=0;j<n;j++)
	{
		int k=j;
		for(int i=0;i<len;i++)
		{
			array[j][i]=k%2;
			k=k/2;
		}
	
	}

	for(int j=0;j<n;j++)
	{
		int t=0;
		for(int i=0;i<len;i++)
		{
			if(array[j][i]==1)
				t=t+pow(2,len-1-i);
		}
	array2[j]=t;
	//cout<<t<<endl;
	}

	return (array2);
}

int large(int *array,int len)
{
	int large=array[0];
	for(int j=0;j<len;j++)
	{
		if(array[j]>large)
			large=array[j];
	}
	return large;
}
void plot(complex<double> *array,int n)
{
	int rl[n],im[n];
	complex<double> g=1i;
	complex<double> temp[n];
	for(int j=0;j<n;j++)
	{
		temp[j]=g*array[j];	//bug to be fixed
		rl[j]=imag(temp[j]);
		im[j]=imag(array[j]);
	}
	for(int i=0;i<n;i++)
	{
		cout<<rl[i]<<" "<<real(array[i])<<"	  ";
	}
big=large(rl,n);
least=small(rl,n);

cout<<endl<<endl<<"real part"<<endl<<endl;
delta(rl,big,least,n);
big=large(im,n);
least=small(im,n);

cout<<endl<<"imaginary part"<<endl<<endl;
delta(im,big,least,n);
cout<<endl;
}
int small(int *array,int len)
{
	int large=array[0];
	for(int j=0;j<len;j++)
	{
		if(array[j]<large)
			large=array[j];
	}
	return large;
}

void delta(int *array,int big,int least,int len)
{
	int delta[len];
	int negative_members[len];
	for(int j=0;j<len;j++)
	{
		negative_members[j]=0;
		if(array[j]>0)
		{
			delta[j]=big-(array[j]);//enclose in if loop to ensure positive num
		}
		else
			{
			delta[j]=big;
			negative_members[j]=-1*(array[j]);
			}
	}

	for(int l=0;l<big;l++)
	{	int j=0;
		while(j<len)
		{
			if(delta[j]<=l)
				cout<<"**  ";
			else 
				cout<<"    ";
			j++;
		}
		
		cout<<endl;
	}
	for(int j=0;j<len;j++)
	{
		cout<<"----";
	}
	cout<<endl;
	if(least<0)
	{
		
	for(int l=1;l<=-1*least;l++)
	{	int j=0;
		while(j<len)
		{
			if(negative_members[j]>=l)
				cout<<"**  ";
			else 
				cout<<"    ";
			j++;
		}
		
		cout<<endl;
	}
	}
	for(int j=0;j<len;j++)
	{
		cout<<"----";
	}
	cout<<endl;
	for(int j=0;j<len;j++)
	{
		cout<<array[j]<<"   ";
	}
	cout<<endl;
}
