CC=gcc
CFLAGS=-Wall -Werror
LIBNAME=libnnet.so

${LIBNAME}: nnet.o layer.o
	${CC} -shared nnet.o layer.o -o ${LIBNAME}

layer.o:
	${CC} ${CFLAGS} -c layer.cpp -fpic -o layer.o

nnet.o:
	${CC} ${CFLAGS} -c nnet.cpp -fpic -o nnet.o

clean:
	rm -f *.o ${LIBNAME}

uninstall:
	sudo rm /usr/lib/${LIBNAME}

install: ${LIBNAME}
	sudo cp ${LIBNAME} /usr/lib/${LIBNAME}

