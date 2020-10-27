# $MirOS: src/bin/ed/Makefile,v 1.6 2020/10/27 07:33:42 tg Exp $
# $OpenBSD: Makefile,v 1.12 2018/06/15 08:46:24 martijn Exp $

PROG=		ed
SRCS=		buf.c glbl.c io.c main.c re.c sub.c undo.c

# These just get installed verbatim
.if make(install)
SUBDIR+= USD.doc/09.edtut USD.doc/10.edadv
.endif

SRCDIR=		${.CURDIR}

regress:
	cd ${SRCDIR:Q}/test && \
	    ${MAKE} clean && \
	    ${MAKE} ED=${.OBJDIR:Q}/ed && \
	    ${MAKE} clean

.include <bsd.prog.mk>
