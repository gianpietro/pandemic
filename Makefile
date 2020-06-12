program: pandemic.c lkdlst.so mltgrp.so poplib.so
	gcc -g pandemic.c lkdlst.so mltgrp.so poplib.so -o pandemic

lkdlst.so: lkdlst.c lkdlst.h
	gcc lkdlst.c -o lkdlst.so -c

mltgrp.so: mltgrp.c mltgrp.h
	gcc mltgrp.c -o mltgrp.so -c

poplib.so: poplib.c poplib.h
	gcc poplib.c -o poplib.so -c
