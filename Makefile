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
	sudo rm -f /usr/lib/${LIBNAME}
	sudo rm -rf /usr/include/nnet-cpp

install: ${LIBNAME}
	sudo cp ${LIBNAME} /usr/lib/${LIBNAME}
	sudo mkdir /usr/include/nnet-cpp
	sudo cp *.hpp /usr/include/nnet-cpp
	sudo cp nnet.hpp /usr/include/nnet-cpp/nnet

