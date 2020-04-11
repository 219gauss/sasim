#ifndef _TEST_H
#define _TEST_H

struct operation {
    
    int (*opstype[10])(int,int);
    int mData[10];	/*运算数据*/
    int mRet;		/*运算结果*/
    int mCount;
    int moperationCount;
};

void init(int (*opstype)(int,int));
int use(int (*opstype)(int,int));
void init_data(int data, ...);

#endif
