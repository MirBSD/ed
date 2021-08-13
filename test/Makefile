#	$MirOS: src/bin/ed/test/Makefile,v 1.4 2021/08/13 21:57:43 tg Exp $
#	$OpenBSD: Makefile,v 1.2 1996/06/23 14:20:05 deraadt Exp $
#	$NetBSD: Makefile,v 1.11 1995/03/21 09:05:14 cgd Exp $

ED=	../obj/ed

all: check
	@:

check: build ckscripts.sh
	@echo testing $(ED) ...
	@$(SHELL) ckscripts.sh $(ED) quiet
	@set +e; grep -h '\*\*\*' errs.o scripts.o >errs.z; test $$? -lt 2
	@if cmp -s errs.z errs.exp; then \
		echo "tests completed successfully."; \
	elif test -s errs.z; then \
		cat errs.z; \
	else \
		echo "tests completed with POSIX strictness."; \
	fi

build: mkscripts.sh
	@if [ -f errs.o ]; then :; else \
		echo "building test scripts for $(ED) ..."; \
		$(SHELL) mkscripts.sh $(ED); \
	fi

clean:
	rm -f *.ed *.red *.[oz] *~
