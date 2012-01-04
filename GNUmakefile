# $MirOS: src/bin/ed/GNUmakefile,v 1.4 2012/01/04 21:27:33 tg Exp $
#-
# Makefile for GNU make, possibly nmake
# You will need to provide strlcpy(3) and strlcat(3) to the link by
# setting the DPADD (dependency) and LDADD (link object) correctly.

PROG=		ed
OBJS=		buf.o glbl.o io.o main.o re.o sub.o undo.o
DEFS1=		-DBACKWARDS
DEFS2=		-D'__SCCSID(x)=static const char __sccsid[] = x'
DEFS3=		-D'__RCSID(x)=static const char __rcsid[] = x'
DEFS4=		-D'__COPYRIGHT(x)=static const char __copyright[] = x'
#DEFS5=		-DNO_FSEEKO
DEFS=		$(DEFS1) $(DEFS2) $(DEFS3) $(DEFS4) $(DEFS5)

all: $(PROG)

$(PROG): $(OBJS) $(DPADD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) $(LIBS) $(LDADD)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) -c -o $@ $<
