# $MirOS: src/bin/ed/Makefile,v 1.5 2020/10/27 02:48:11 tg Exp $
# $OpenBSD: Makefile,v 1.12 2018/06/15 08:46:24 martijn Exp $

PROG=		ed
SRCS=		buf.c glbl.c io.c main.c re.c sub.c undo.c

# These just get installed verbatim
.if make(install)
SUBDIR+= USD.doc/09.edtut USD.doc/10.edadv
.endif

.include <bsd.prog.mk>
