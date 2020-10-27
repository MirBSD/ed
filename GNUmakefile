# $MirOS: src/bin/ed/GNUmakefile,v 1.11 2020/10/27 08:21:05 tg Exp $
#-
# Makefile for GNU make, possibly nmake
# Add strlcpy(3), strlcat(3) and reallocarray(3) to the link either
# by setting DPADD (dependency) and LDADD (link object) accordingly
# or by adding the respective files and uncommenting OBJS2/OBJS3 as
# needed; uncommenting DEFS2/DEFS3 may also be necessary (even with
# LDADD=-lbsd); glibc ships reallocarray now but still not strlfun.

PROG=		ed
OBJS1=		buf.o glbl.o io.o main.o re.o sub.o undo.o
#OBJS2=		strlcat.o strlcpy.o
#OBJS3=		reallocarray.o
OBJS=		$(OBJS1) $(OBJS2) $(OBJS3)
DEFS0=		-D'__IDSTRING(id,x)=static const char __idstring_ \#\# id [] __attribute__((__used__)) = x'
DEFS1=		-D'__RCSID(x)=__IDSTRING(rcsid,x)'
#DEFS2=		-DNEED_STRLFUN_DECL
#DEFS3=		-DNEED_REALLOCARRAY_DECL
#DEFS4=		-DNO_FSEEKO
DEFS5=		-D_GNU_SOURCE
DEFS=		$(DEFS0) $(DEFS1) $(DEFS2) $(DEFS3) $(DEFS4) $(DEFS5)
STFN=		$(DEFS0) $(DEFS1) -DOUTSIDE_OF_LIBKERN

all: $(PROG)

$(PROG): $(OBJS) $(DPADD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) $(LIBS) $(LDADD)

strlcat.o: strlfun.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STFN) -DL_strlcat -c -o $@ strlfun.c

strlcpy.o: strlfun.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STFN) -DL_strlcpy -c -o $@ strlfun.c

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(PROG)
