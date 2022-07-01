#include<stdio.h>
#include<stdlib.h>

void *f(int n)
{
	int num;
	return &n;
}

int main ()
{
	int *ptr = NULL;
	ptr = f(4);
	printf("%d", *ptr);
	return 0;
}