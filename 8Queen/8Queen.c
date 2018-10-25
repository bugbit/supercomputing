#include <stdlib.h>

int cmp(int *n1,int *n2)
{
	return *n1-*n2;
}

int NQUEEN(int n,int *i,int ni,int **s,int *ns)
{
	int *e=(int*)calloc(n,sizeof(int));

	if (e==NULL)
		return -1;

	if (ni>0)
		qsort(i,ni,sizeof(int),(int (*)(const void *, const void *))&cmp);

	*s=NULL;
	*ns=0;

	free(e);

	return 0;
}

int main(int argc,char **argv)
{

	return EXIT_SUCCESS;
}