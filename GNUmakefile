# $MirOS: src/bin/ed/GNUmakefile,v 1.2 2011/04/09 17:04:48 tg Exp $
#-
# Makefile for GNU make, possibly nmake
# You will need to provide strlcpy(3) and strlcat(3) to the link.

PROG=		ed
OBJS=		buf.o glbl.o io.o main.o re.o sub.o undo.o
DEFS1=		-DBACKWARDS
DEFS2=		-D'__SCCSID(x)=static const char __sccsid[] = x'
DEFS3=		-D'__RCSID(x)=static const char __rcsid[] = x'
DEFS4=		-D'__COPYRIGHT(x)=static const char __copyright[] = x'
DEFS=		$(DEFS1) $(DEFS2) $(DEFS3) $(DEFS4)

all: $(PROG)

$(PROG): $(OBJS) $(DPADD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) $(LIBS) $(LDADD)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) -c -o $@ $<
