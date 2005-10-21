# $MirOS: src/bin/ed/Makefile,v 1.2 2005/03/15 18:58:31 tg Exp $
# $OpenBSD: Makefile,v 1.8 2003/07/29 18:36:30 jmc Exp $

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
