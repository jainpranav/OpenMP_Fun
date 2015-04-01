#include<stdio.h>
#include<omp.h>
#include<stdlib.h>


int main()
{
	int i;
	int N=1000000;
	FILE *op,*fp;
	op=fopen("random.txt","w");
	#pragma omp parallel for
		for (i=0;i<N;i++)
		{
			fprintf(op,"%d\n",rand()%100);
		}
	fclose(op);
	int j=0,count=0,sum=0;
	fp=fopen("random.txt","r");
	#pragma omp parallel for
		for(count=0;count<N;count++)
		{
		 if(fscanf(fp,"%d",&j)=='\n') 
		 continue;
		 sum+=j;
		 }
   	fclose (fp);
   	printf("sum of the 1 million integers :");
	printf("%d\n",sum);
}
