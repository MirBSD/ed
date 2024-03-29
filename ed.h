#define ED_H_ID "$MirOS: src/bin/ed/ed.h,v 1.22 2021/08/13 22:41:24 tg Exp $"
/*	$OpenBSD: ed.h,v 1.22 2016/03/27 00:43:38 mmcc Exp $	*/
/*	$NetBSD: ed.h,v 1.23 1995/03/21 09:04:40 cgd Exp $	*/

/* ed.h: type and constant definitions for the standard text editor */
/*
 * Copyright (c) 2013, 2016, 2020, 2021
 *	mirabilos <m@mirbsd.org>
 * Copyright (c) 1993 Andrew Moore
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ed.h,v 1.5 1994/02/01 00:34:39 alm Exp
 */

#ifdef __MirBSD__
#include <sys/param.h> /* for MirBSD */
#endif
#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <signal.h>

#ifndef HAVE_ATTRIBUTE_USED
#define HAVE_ATTRIBUTE_USED	1
#endif

#if HAVE_ATTRIBUTE_USED
#define MKSH_A_USED		__attribute__((__used__))
#else
#define MKSH_A_USED		/* nothing */
#endif

#if defined(MirBSD) && (MirBSD >= 0x09A1) && \
    defined(__ELF__) && defined(__GNUC__) && \
    !defined(__llvm__) && !defined(__NWCC__)
/*
 * We got usable __IDSTRING __COPYRIGHT __RCSID __SCCSID macros
 * which work for all cases; no need to redefine them using the
 * "portable" macros from below when we might have the "better"
 * gcc+ELF specific macros or other system dependent ones.
 */
#else
#undef __IDSTRING
#undef __IDSTRING_CONCAT
#undef __IDSTRING_EXPAND
#undef __COPYRIGHT
#undef __RCSID
#undef __SCCSID
#define __IDSTRING_CONCAT(l,p)		__LINTED__ ## l ## _ ## p
#define __IDSTRING_EXPAND(l,p)		__IDSTRING_CONCAT(l,p)
#ifdef MKSH_DONT_EMIT_IDSTRING
#define __IDSTRING(prefix,string)	/* nothing */
#elif defined(__ELF__) && defined(__GNUC__) && \
    !(defined(__GNUC__) && defined(__mips16) && (__GNUC__ >= 8)) && \
    !defined(__llvm__) && !defined(__NWCC__) && !defined(NO_ASM)
#define __IDSTRING(prefix,string)				\
	__asm__(".section .comment"				\
	"\n	.ascii	\"@(\"\"#)" #prefix ": \""		\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define __IDSTRING(prefix,string)				\
	static const char __IDSTRING_EXPAND(__LINE__,prefix) []	\
	    MKSH_A_USED = "@(""#)" #prefix ": " string
#endif
#define __COPYRIGHT(x)		__IDSTRING(copyright,x)
#define __RCSID(x)		__IDSTRING(rcsid,x)
#define __SCCSID(x)		__IDSTRING(sccsid,x)
#endif

#define edbool unsigned char

#ifdef NEED_STRLFUN_DECL
size_t strlcat(char *, const char *, size_t);
size_t strlcpy(char *, const char *, size_t);
#endif

#ifdef NEED_REALLOCARRAY_DECL
void *reallocarray(void *, size_t, size_t);
#endif

#define ERR		(-2)
#define EMOD		(-3)
#define FATAL		(-4)

#define MINBUFSZ 512		/* minimum buffer size - must be > 0 */
#define SE_MAX 30		/* max subexpressions in a regular expression */
#define LINECHARS INT_MAX	/* max chars per line */

#ifdef NO_FSEEKO
#define do_fseek fseek
#define do_ftell ftell
#define tp_ftell long
#else
#define do_fseek fseeko
#define do_ftell ftello
#define tp_ftell off_t
#endif

/* gflags */
#define GLB 001		/* global command */
#define GPR 002		/* print after command */
#define GLS 004		/* list after command */
#define GNP 010		/* enumerate after command */
#define GSG 020		/* global substitute */

/* Line node */
typedef struct line {
	struct line	*q_forw;
	struct line	*q_back;
	tp_ftell	adr;		/* address of line in scratch buffer */
	size_t		llen;		/* length of line */
} line_t;


typedef struct undo {

/* type of undo nodes */
#define UADD	0
#define UDEL 	1
#define UMOV	2
#define VMOV	3

	int type;			/* command type */
	line_t	*h;			/* head of list */
	line_t	*t;			/* tail of list */
} undo_t;

#ifndef MAX
# define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
# define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define INC_MOD(l, k)	((l) + 1 > (k) ? 0 : (l) + 1)
#define DEC_MOD(l, k)	((l) - 1 < 0 ? (k) : (l) - 1)

/* SPL1: disable some interrupts (requires reliable signals) */
#define SPL1() (mutex++)

/* SPL0: enable all interrupts; check signal flags (requires reliable signals) */
#define SPL0impl()					\
	do {						\
		if (--mutex == 0) {			\
			if (sighup)			\
				handle_hup(SIGHUP);	\
			if (sigint)			\
				handle_int(SIGINT);	\
		}					\
	} while (0)
#ifdef SMALL
extern void edSPL0(void);
#define SPL0 edSPL0
#else
#define SPL0 SPL0impl
#endif

/* STRTOI: convert a string to int */
extern int edSTRTOI(int *, char **);
#define STRTOI(i,p) do {		\
	if (edSTRTOI(&(i), &(p)))	\
		return (ERR);		\
} while (/* CONSTCOND */ 0)

/* REALLOC: assure at least a minimum size for buffer b */
#ifdef SMALL
extern int edREALLOC(void **, size_t *, size_t);
#define REALLOC(b,n,i,err) do {						\
	if ((i) > (n)) {						\
		if (edREALLOC((void **)&(b), &(n), (i)))		\
			return (err);					\
	}								\
} while (/* CONSTCOND */ 0)
#else
#define REALLOC(b,n,i,err) do {						\
	if ((i) > (n)) {						\
		size_t L = (i);						\
		void *nb;						\
									\
		/* determine new len: round to next 2⁸ multiple */	\
		L = (L + 0xFFU) & ((size_t)(~(size_t)0xFFU) + 0U);	\
									\
		SPL1();							\
		errno = EOVERFLOW;					\
		if (L < (n) || L < (i) || !(nb = realloc((b), L))) {	\
			perror(NULL);					\
			seterrmsg("out of memory");			\
			SPL0();						\
			return (err);					\
		}							\
		(n) = L;						\
		(b) = nb;						\
		SPL0();							\
	}								\
} while (/* CONSTCOND */ 0)
#endif

/* REQUE: link pred before succ */
#define REQUE(pred, succ) (pred)->q_forw = (succ), (succ)->q_back = (pred)

/* INSQUE: insert elem in circular queue after pred */
#define INSQUE(elem, pred) \
{ \
	REQUE((elem), (pred)->q_forw); \
	REQUE((pred), elem); \
}

/* remque: remove_lines elem from circular queue */
#define REMQUE(elem) REQUE((elem)->q_back, (elem)->q_forw);

/* NUL_TO_NEWLINE: overwrite ASCII NULs with newlines */
#define NUL_TO_NEWLINE(s, l) translit_text(s, l, '\0', '\n')

/* NEWLINE_TO_NUL: overwrite newlines with ASCII NULs */
#define NEWLINE_TO_NUL(s, l) translit_text(s, l, '\n', '\0')

/* Local Function Declarations */
void add_line_node(line_t *);
int build_active_list(int);
void clear_active_list(void);
void clear_undo_stack(void);
int close_sbuf(void);
int delete_lines(int, int);
int display_lines(int, int, int);
int exec_command(void);
int exec_global(int, int);
int extract_addr_range(void);
int extract_subst_tail(int *, int *);
line_t *get_addressed_line_node(int);
regex_t *get_compiled_pattern(void);
char *get_extended_line(ssize_t *, int);
int get_line_node_addr(line_t *);
char *get_sbuf_line(line_t *);
ssize_t get_tty_line(void);
void handle_hup(int) __attribute__((__noreturn__));
void handle_int(int) __attribute__((__noreturn__));
int has_trailing_escape(char *, char *);
void init_buffers(void);
int open_sbuf(void);
int pop_undo_stack(void);
undo_t *push_undo_stack(int, int, int);
char *put_sbuf_line(char *);
int put_tty_line(char *, size_t, int, int);
void quit(int) __attribute__((__noreturn__));
int read_file(char *, int);
int search_and_replace(regex_t *, int, int);
void seterrmsg(const char *);
char *strip_escapes(const char *);
char *translit_text(char *, size_t, int, int);
void unmark_line_node(line_t *);
void unset_active_nodes(line_t *, line_t *);
int write_file(const char *, const char *, int, int);

/* global buffers */
extern char *ibuf;
extern char *ibufp;
extern size_t ibufsz;

/* global flags */
extern edbool isbinary;
extern edbool isglobal;
extern edbool modified;

extern volatile sig_atomic_t mutex;
extern volatile sig_atomic_t sighup;
extern volatile sig_atomic_t sigint;

/* global vars */
extern int addr_last;
extern int current_addr;
extern int first_addr;
extern int lineno;
extern int second_addr;
