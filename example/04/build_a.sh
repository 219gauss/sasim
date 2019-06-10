#!/bin/bash

gcc -c test.c
#生成静态库
ar -cr test.a test.o
#使用静态库
gcc -o test my.c -L. test.a
