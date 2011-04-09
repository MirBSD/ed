# $MirOS: src/bin/ed/Makefile,v 1.3 2011/04/09 16:28:48 tg Exp $
# $OpenBSD: Makefile,v 1.9 2010/01/04 17:50:37 deraadt Exp $

PROG=		ed
SRCS=		buf.c cbc.c glbl.c io.c main.c re.c sub.c undo.c
CPPFLAGS+=	-DBACKWARDS -DDES

#LINKS=  ${BINDIR}/ed ${BINDIR}/red
#MLINKS= ed.1 red.1

# These just get installed verbatim
.if make(install)
SUBDIR+= USD.doc/09.edtut USD.doc/10.edadv
.endif

.include <bsd.prog.mk>
