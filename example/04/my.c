#include <stdio.h>

#include "my.h"
 
int add(int a, int b)
{	
	return a+b;
}

int sub(int a,int b)
{
	return a-b;
}

int mul(int a,int b)
{
	return a*b;
}

int div(int a,int b)
{
	return a/b;
}

int main(int argc, char const *argv[])
{

	init(add);
	init(sub);
	init(mul);
	init(div);
	init_data(2,atoi(argv[1]),atoi(argv[2]));
	printf("ret = %d\n", use(add));
	printf("ret = %d\n", use(sub));
	printf("ret = %d\n", use(mul));
	printf("ret = %d\n", use(div));
	
	return 0;
}
