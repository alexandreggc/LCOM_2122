PROG=proj

.PATH: ${.CURDIR}/project/src
.PATH: ${.CURDIR}/libs/graph/src
.PATH: ${.CURDIR}/libs/kbc/src
.PATH: ${.CURDIR}/libs/rtc/src
.PATH: ${.CURDIR}/libs/timer/src
.PATH: ${.CURDIR}/libs/utils/src
.PATH: ${.CURDIR}/media

SRCS= game.c keyboard.c mouse.c timer.c utils.c videocard.c proj.c sprite.c rtc.c entities.c rectangle.c menu.c font.c project_functions.c keys.c leaderboard.c makecode_map.c

IPATHS=-I./project/include -I./libs -I./libs/graph/include -I./libs/rtc/include -I./libs/kbc/include -I./libs/timer/include -I./libs/utils/include -I./media

CPPFLAGS += -pedantic ${IPATHS} -D proj -D __LCOM_OPTIMIZED__ -Wall -Wextra -Wshadow -Wunreachable-code #-Weverything -Wno-padded -Wno-unused-macros

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>