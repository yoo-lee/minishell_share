#include<stdio.h>
#include<stdlib.h>

int main ()
{
	int *ptr;
	int n;
	n = 10;
	ptr = &n;

	ptr = (int *)malloc(sizeof(int));
	free(ptr);
	ptr = ;
	system("leaks a.out");
}