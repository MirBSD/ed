# $MirOS: src/bin/ed/GNUmakefile,v 1.6 2016/11/06 18:58:43 tg Exp $
#-
# Makefile for GNU make, possibly nmake
# You will need to provide strlcpy(3) and strlcat(3) to the link by
# setting the DPADD (dependency) and LDADD (link object) correctly.

PROG=		ed
OBJS1=		buf.o glbl.o io.o main.o re.o sub.o undo.o
#OBJS2=		strlcat.o strlcpy.o
OBJS=		$(OBJS1) $(OBJS2)
DEFS1=		-DBACKWARDS
DEFS2=		-D'__IDSTRING(id,x)=static const char __idstring_ ## id [] = x'
DEFS3=		-D'__RCSID(x)=static const char __rcsid[] = x'
#DEFS4=		-DNO_FSEEKO
DEFS=		$(DEFS1) $(DEFS2) $(DEFS3) $(DEFS4)

all: $(PROG)

$(PROG): $(OBJS) $(DPADD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) $(LIBS) $(LDADD)

strlcat.o: strlfun.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DOUTSIDE_OF_LIBKERN -DL_strlcat -c -o $@ strlfun.c

strlcpy.o: strlfun.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DOUTSIDE_OF_LIBKERN -DL_strlcpy -c -o $@ strlfun.c

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) -c -o $@ $<
