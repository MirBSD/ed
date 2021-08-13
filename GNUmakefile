# $MirOS: src/bin/ed/GNUmakefile,v 1.15 2021/08/13 22:51:44 tg Exp $
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
DEFS0=		-DMBSDPORT_H=\"ed.h\"
DEFS1=		-D_GNU_SOURCE
#DEFS2=		-DNEED_STRLFUN_DECL
#DEFS3=		-DNEED_REALLOCARRAY_DECL
#DEFS4=		-DNO_FSEEKO
DEFS=		$(DEFS0) $(DEFS1) $(DEFS2) $(DEFS3) $(DEFS4)
STFN=		$(DEFS0) -DNEED_STRLFUN_PROTOS
SHELL=		/bin/sh

all: $(PROG)

$(PROG): $(OBJS) $(DPADD)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS) $(LIBS) $(LDADD)

strlcat.o: strlfun.c
	cat strlfun.c >strlcat.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STFN) -DL_strlcat -c strlcat.c

strlcpy.o: strlfun.c
	cat strlfun.c >strlcpy.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STFN) -DL_strlcpy -c strlcpy.c

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEFS) -c $<

clean:
	cd test && $(MAKE) clean
	rm -f strlcpy.c strlcat.c $(OBJS) $(PROG)

check:
	cd test && $(MAKE) clean && SHELL='$(SHELL)' $(MAKE) ED=../ed && $(MAKE) clean
