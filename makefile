# nmake makefile
# 
# Tools used:
#  Compile::Resource Compiler
#  Compile::GNU C
#  Make: nmake
all : star5.exe

star5.exe : star5.obj star5.def
	gcc -Zomf star5.obj star5.def -o star5.exe

star5.obj : star5.c
	gcc -Wall -Zomf -c -O2 star5.c -o star5.obj

clean :
	rm -rf *exe *RES *obj