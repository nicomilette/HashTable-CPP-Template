CC := g++

CFLAGS := -std=c++11 -lcrypt

SRCS := scrypt.cpp testdriver.cpp userpass.cpp

OBJS := ${SRCS:.cpp=.o} pass_server.o 

PROGS := ${SRCS:.cpp=} 

.PHONY: all

all: ${PROGS}

scrypt: scrypt.o 
	${CC} ${CFLAGS} $^ -o $@ 
testdriver: testdriver.o pass_server.o
	${CC} ${CFLAGS} $^ -o $@ 
userpass: userpass.o pass_server.o
	${CC} ${CFLAGS} $^ -o $@ 

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} ${OBJS} *.bak *~
