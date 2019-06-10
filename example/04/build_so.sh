#!/bin/bash
#编译so库
gcc -shared -fpic -o test.so test.c 
#使用so库
gcc -o test my.c -L. test.so 
#添加库的寻找路径
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
