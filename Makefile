#!Makefile 

CC 	=	gcc
OUT	=	out
LIB_SO = calc_so.c

#基于依赖递归更新的编译规则
all:
	gcc -fPIC -shared -o calc.so $(LIB_SO)
	mv calc.so /lib/
	gcc -rdynamic -o $(OUT) entry.c -ldl

#隐晦规则，伪目标文件
#-rm 某些文件出现问题，但不要管，继续做后面的事
.PHONY:run
run:
	./out

.PHONY:clean
clean:
	-rm -f calc.so $(OUT)
	-rm -f /lib/calc.so
