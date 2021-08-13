#!/bin/mksh
#	$MirOS: src/bin/ed/test/mkscripts.sh,v 1.6 2021/08/13 22:56:32 tg Exp $
#	$OpenBSD: mkscripts.sh,v 1.2 1996/06/23 14:20:08 deraadt Exp $
#	$NetBSD: mkscripts.sh,v 1.10 1995/04/23 10:07:36 cgd Exp $
#
# This script generates ed test scripts (.ed) from .t files

PATH="/bin:/usr/bin:/usr/local/bin/:."
ED=$1
SHELL=$2
test x"$3" = x"sentinel" || { echo >&2 "E: quoting mismatch"; exit 255; }
[ ! -x $ED ] && { echo "$ED: cannot execute"; exit 1; }

for i in *.t; do
#	base=${i%.*}
#	base=`echo $i | sed 's/\..*//'`
#	base=`expr $i : '\([^.]*\)'`
#	(
#	echo "#!/bin/mksh"
#	echo "$ED - <<\EOT"
#	echo "r $base.d"
#	cat $i
#	echo "w $base.o"
#	echo EOT
#	) >$base.ed
#	chmod +x $base.ed
# The following is pretty ugly way of doing the above, and not appropriate 
# use of ed  but the point is that it can be done...
	base=`$ED - \!"echo $i" <<-EOF
		s/\..*/
		Q
	EOF`
	$ED - <<-EOF
		a
		#!$SHELL
		$ED - <<\EOT
		H
		r $base.d
		w $base.o
		Q
		EOT
		.
		-3r $i
		w $base.ed
		!chmod +x $base.ed
		Q
	EOF
done

for i in *.err; do
#	base=${i%.*}
#	base=`echo $i | sed 's/\..*//'`
#	base=`expr $i : '\([^.]*\)'`
#	(
#	echo "#!/bin/mksh"
#	echo "$ED - <<\EOT"
#	echo H
#	echo "r $base.err"
#	cat $i
#	echo "w $base.o"
#	echo EOT
#	) >$base-err.ed
#	chmod +x $base-err.ed
# The following is pretty ugly way of doing the above, and not appropriate 
# use of ed  but the point is that it can be done...
	base=`$ED - \!"echo $i" <<-EOF
		s/\..*/
		Q
	EOF`
	$ED - <<-EOF
		a
		#!$SHELL
		$ED - <<\EOT
		H
		r $base.err
		w $base.o
		Q
		EOT
		.
		-3r $i
		w ${base}.red
		!chmod +x ${base}.red
		Q
	EOF
done
