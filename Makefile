program: pandemic.c lkdlst.so
	gcc pandemic.c lkdlst.so -o pandemic

lkdlst.so: lkdlst.c lkdlst.h
	gcc lkdlst.c -o lkdlst.so -c

