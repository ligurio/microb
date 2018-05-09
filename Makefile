CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -Wmissing-declarations -g
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wstrict-prototypes

TESTS =	example

all: ${TESTS}

example: example.o

%.o: %.c
	${CC} -c -o $@ ${CFLAGS} $<

%: %.o
	${CC} -o $@ ${LDFLAGS} $^

*.o: Makefile
*.o: microb.h

clean:
	rm -f ${TESTS} *.o *.core
