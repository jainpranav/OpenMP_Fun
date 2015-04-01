#include<stdio.h>
#include<omp.h>
#include<time.h>

void main()
{
int N=256;
FILE *op,*op1,*op2,*op3;

float r,w,s1,s2,s3,s4;

float y[N][1];
int b,c,d,e,f,g,h,i,j,k,l,u,s,t,v,z;
op=fopen("y.txt","r");
for (j=0;j<N;j++)
{
	fscanf(op,"%f",&y[j][0]);
}

float X[N][1];
op2=fopen("x.txt","r");
for (g=0;g<N;g++)
{
	fscanf(op2,"%f",&X[g][0]);
}

float a[N][N];
op1=fopen("A.txt","r");
for (c=0;c<N;c++)
{
	for (d=0;d<N;d++)
	{
		fscanf(op1,"%f",&r);
		a[c][d]=r;
	}
}

float trans[N][N];
op3=fopen("A.txt","r");
for (s=0;s<N;s++)
{
	for (t=0;t<N;t++)
	{
		fscanf(op3,"%f",&w);
		trans[t][s]=w;
	}
}

float xend[N][1];
for (e=0;e<N;e++)
xend[e][0]=0.0;

omp_set_num_threads(4);
double tim=omp_get_wtime();

int I,J,K,M;
float func[N][1],func1[N][1],func2[N][1];
for (J=0;J<50000;J++)
{
	#pragma omp parallel for 
	for (i=0;i<N;i++)
	func[i][0]=0.0;

	#pragma omp parallel for
	for (K=0;K<N;K++)
	func2[K][0]=0.0;


	#pragma omp parallel for
	for (k=0;k<N;k++)
	{
	#pragma omp parallel for reduction(+:s1)
	for (l=0;l<N;l++)
	{
		s1=func[k][0];
		s1=s1+(a[k][l])*(xend[l][0]);
	func[k][0]=s1;
	}
	}

	#pragma omp parallel for
	for (u=0;u<N;u++)
	{
		func1[u][0]=y[u][0]-func[u][0];

	}
	#pragma omp parallel for
	for (v=0;v<N;v++)
	{
		#pragma omp parallel for reduction(+:s2)
		for (z=0;z<N;z++)
		{	
		s2=func2[v][0];
		s2=s2+(trans[v][z])*(func1[z][0]);
		func2[v][0]=s2;
		}
	}
	#pragma omp parallel for reduction(*:s3)
	for (b=0;b<N;b++)
	{
		s3=func2[b][0];
		s3=s3*(1/1.9660);
		func2[b][0]=s3;
	}
	#pragma omp parallel for reduction(+:s4)
	for (I=0;I<N;I++)
	{
		s4=xend[I][0];
		s4=s4+func2[I][0];
		xend[I][0]=s4;
	}
}
for (M=0;M<N;M++)
printf("%f\n",xend[M][0]);
double tim1=omp_get_wtime();
printf("time=%f\n",tim1-tim);
}
