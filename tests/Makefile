BINDIR := bin
OPTIONS +=
CFLAGS += -Wall
LDFLAGS += -lpthread
CC := clang

build:
	@mkdir -p ${BINDIR}
	${CC} gettime.c -o ${BINDIR}/gettime ${LDFLAGS} ${CFLAGS}
	${CC} ntpclient.c -o ${BINDIR}/ntpclient ${LDFLAGS} ${CFLAGS}

	#${CC} at_2d.c -o ${BINDIR}/at_2d ${LDFLAGS} ${CFLAGS}
	${CC} at_cpuid.c -o ${BINDIR}/at_cpuid ${LDFLAGS} ${CFLAGS}
	${CC} at_ctx.c -o ${BINDIR}/at_ctx ${LDFLAGS} ${CFLAGS}
	${CC} at_fork.c -o ${BINDIR}/at_fork ${LDFLAGS} ${CFLAGS}
	${CC} at_fsync.c -o ${BINDIR}/at_fsync ${LDFLAGS} ${CFLAGS}
	${CC} at_getifaddrs.c -o ${BINDIR}/at_getifaddrs ${LDFLAGS} ${CFLAGS}
	#${CC} at_malloc.c -o ${BINDIR}/at_malloc ${LDFLAGS} ${CFLAGS}
	${CC} at_mmap.c -o ${BINDIR}/at_mmap ${LDFLAGS} ${CFLAGS}
	${CC} at_sigbench.c -o ${BINDIR}/at_sigbench ${LDFLAGS} ${CFLAGS}
	${CC} at_vmm.c -o ${BINDIR}/at_vmm ${LDFLAGS} ${CFLAGS} -Wno-unused-but-set-variable -Wno-div-by-zero

run:
	${BINDIR}/at_cpuid ${OPTIONS}
	${BINDIR}/at_fsync ${OPTIONS}
	${BINDIR}/at_getifaddrs ${OPTIONS}
	${BINDIR}/at_malloc ${OPTIONS}
	${BINDIR}/at_mmap ${OPTIONS}
	${BINDIR}/at_sigbench ${OPTIONS}
	${BINDIR}/at_vmm ${OPTIONS}

clean:
	rm -rf ${BINDIR}

.PHONY: build clean
