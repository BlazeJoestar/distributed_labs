SHELL := /bin/bash
current_dir = $(shell pwd)


mono: monolit
stat: static
dynam: dynamic

monolit: test.o uni_f.o
	gcc test.o uni_f.o -o monolit
test.o: test.c
	gcc -c test.c -o test.o
uni_f.o: uni_functions.c uni_functions.h uni_types.h
	gcc -c uni_functions.c -o uni_f.o


static: test.o lib_uni_f.a
	gcc test.o lib_uni_f.a -o static
lib_uni_f.a: uni_functions.c uni_functions.h uni_types.h
	gcc -c uni_functions.c -o uni_f.o
	ar r lib_uni_f.a uni_f.o


dynamic: test.o lib_uni_functions.so
	gcc test.o -L. -l_uni_functions -o dynamic	
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
lib_uni_functions.so: uni_functions.o
	gcc uni_functions.o -shared -o lib_uni_functions.so
uni_functions.o: uni_functions.c uni_functions.h uni_types.h
	gcc -c -fPIC -Wall -D_GNU_SOURCE uni_functions.c

clean:
	rm -f *.o *.a *.so monolit static dynamic
