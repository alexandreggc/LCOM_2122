# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = $(proj.c) $(wildcard/source *.c) $(wildcard/defines *.h) $(wildcard *.o)

# Object files
OBJ=$(wildcard/source:.c=.o)

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D__LCOM_OPTIMIZED__
CPPFLAGS += -D proj

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>