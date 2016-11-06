# $MirOS: src/bin/ed/Makefile,v 1.4 2016/11/06 18:58:43 tg Exp $
# $OpenBSD: Makefile,v 1.11 2014/05/24 01:35:55 daniel Exp $

PROG=		ed
SRCS=		buf.c glbl.c io.c main.c re.c sub.c undo.c
CPPFLAGS+=	-DBACKWARDS

# These just get installed verbatim
.if make(install)
SUBDIR+= USD.doc/09.edtut USD.doc/10.edadv
.endif

.include <bsd.prog.mk>
