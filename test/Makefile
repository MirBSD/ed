#	$MirOS: src/bin/ed/test/Makefile,v 1.3 2016/11/06 19:55:04 tg Exp $
#	$OpenBSD: Makefile,v 1.2 1996/06/23 14:20:05 deraadt Exp $
#	$NetBSD: Makefile,v 1.11 1995/03/21 09:05:14 cgd Exp $

ED=	../obj/ed

all: check
	@:

check: build ckscripts.sh
	@echo testing $(ED) ...
	@$(SHELL) ckscripts.sh $(ED) quiet
	@if grep -h '\*\*\*' errs.o scripts.o; then :; else \
		echo "tests completed successfully."; \
	fi

build: mkscripts.sh
	@if [ -f errs.o ]; then :; else \
		echo "building test scripts for $(ED) ..."; \
		$(SHELL) mkscripts.sh $(ED); \
	fi

clean:
	rm -f *.ed *.red *.[oz] *~
