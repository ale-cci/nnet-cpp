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
	rm -f /usr/lib/${LIBNAME}
	rm -rf /usr/include/nnet-cpp

install: ${LIBNAME}
	cp ${LIBNAME} /usr/lib/${LIBNAME}
	mkdir /usr/include/nnet-cpp
	cp *.hpp /usr/include/nnet-cpp
	cp nnet.hpp /usr/include/nnet-cpp/nnet

