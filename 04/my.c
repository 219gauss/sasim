#include <stdio.h>

#include "my.h"
 
void add(int a,int b)
{
	printf("%d\n",a+b);
}

void sub(int a,int b)
{
	printf("%d\n",a-b);
}

int main(int argc, char const *argv[])
{

	init(add);
	init(sub);

	use(add);
	
	return 0;
}
