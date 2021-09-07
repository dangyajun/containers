LIB_DIR = ../containers
LIB_SRC = $(shell find ${LIB_DIR} -name '*.c' -print )
LIB_HDR = $(shell find ${LIB_DIR} -name '*.h' -print )


all: rbtree_test list_test

rbtree_test: rbtree_test.c ${LIB_SRC} ${LIB_HDR}
	gcc -o $@ $< ${LIB_SRC} -I ${LIB_DIR}

list_test: list_test.c ${LIB_SRC} ${LIB_HDR}
	gcc -o $@ $< ${LIB_SRC} -I ${LIB_DIR}


clean:
	rm -f rbtree_test
	rm -f list_test
