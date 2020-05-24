program: pandemic.c lkdlst.so mltgrp.so
	gcc pandemic.c lkdlst.so mltgrp.so -o pandemic

lkdlst.so: lkdlst.c lkdlst.h
	gcc lkdlst.c -o lkdlst.so -c

mltgrp.so: mltgrp.c mltgrp.h
	gcc mltgrp.c -o mltgrp.so -c
