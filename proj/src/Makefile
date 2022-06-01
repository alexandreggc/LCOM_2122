PROG=proj

.PATH: ${.CURDIR}/source

SRCS= game.c keyboard.c mouse.c timer.c utils.c videocard.c proj.c
IPATHS=-I./defines -I./macros

CPPFLAGS += -pedantic ${IPATHS} -D proj -D __LCOM_OPTIMIZED__ -Wall -Wextra -Wshadow -Wunreachable-code #-Weverything -Wno-padded -Wno-unused-macros

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>