#include <stdio.h>
#include "my.h"

void init(void (*opstype)(int,int)){
	int i = 0;
	for(i =0;i<10;i++){
		if(!ops.opstype[i]){
			ops.opstype[i] = opstype;
			break;
		}
	}
}

void use(void (*opstype)(int,int)){
	int i = 0;

	for(i =0;i<10;i++){
		if(ops.opstype[i] && (ops.opstype[i] == opstype)){
			ops.opstype[i](1,2);
			break;
		}
	}
}
