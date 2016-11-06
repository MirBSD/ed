# $MirOS: src/bin/ed/GNUmakefile,v 1.7 2016/11/06 19:18:02 tg Exp $
#-
# Makefile for GNU make, possibly nmake
# Add strlcpy(3), strlcat(3) and reallocarray(3) to the link either
# by setting DPADD (dependency) and LDADD (link object) accordingly
# or by adding the respective files and uncommenting OBJS2 below.

PROG=		ed
OBJS1=		buf.o glbl.o io.o main.o re.o sub.o undo.o
#OBJS2=		strlcat.o strlcpy.o reallocarray.o
OBJS=		$(OBJS1) $(OBJS2)
DEFS1=		-DBACKWARDS
DEFS2=		-D'__IDSTRING(id,x)=static const char __idstring_ \#\# id [] = x'
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
