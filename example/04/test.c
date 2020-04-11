#include <stdio.h>
#include <stdarg.h>
#include "my.h"

struct operation ops = {
	.mRet = 0,
	.mCount = 0,
	.moperationCount = 0
};

void init(int (*opstype)(int,int)){
	int i = 0;

	for(i =0;i<10;i++){
		if(!ops.opstype[i]){
			ops.opstype[ops.moperationCount] = opstype;
			ops.moperationCount++;
			break;
		}
	}
}

/*
* data:参数数量
*/
void init_data(int data, ...){

	int i;
	va_list v1;

	va_start(v1,data);

	for (i = 0; i < data; i++)
	{
		ops.mData[i] = va_arg(v1,int);	//该函数返回v1指向的值，并是v1向下移动一个int的距离，使其指向下一个int
		ops.mCount++;
	}

	va_end(v1);
}

int use(int (*opstype)(int,int)){
	int i = 0,j = 0;

	ops.mRet = 0;	//每次使用清空结果

	for(i =0;i<ops.moperationCount;i++){
		if(ops.opstype[i] && (ops.opstype[i] == opstype)){
			for(j=0 ;j<ops.mCount-1 ;j++){
				ops.mRet = ops.opstype[i](ops.mData[j],ops.mData[j+1]);
			}
			break;
		}
	}
	return ops.mRet;
}
