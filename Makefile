program: pandemic.c lkdlst.so mltgrp.so datimp.so
	gcc pandemic.c lkdlst.so mltgrp.so datimp.so -o pandemic

lkdlst.so: lkdlst.c lkdlst.h
	gcc lkdlst.c -o lkdlst.so -c

mltgrp.so: mltgrp.c mltgrp.h
	gcc mltgrp.c -o mltgrp.so -c

datimp.so: datimp.c datimp.h
	gcc datimp.c -o datimp.so -c
