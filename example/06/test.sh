#!/bin/bash

#函数不带参数可以忽略function
function print(){
	echo $1			#这个$1是指调用print是传进来的第一恶参数
}

print $1			#这个$1是指执行这个脚本是传进来的第一个参数
echo $1
