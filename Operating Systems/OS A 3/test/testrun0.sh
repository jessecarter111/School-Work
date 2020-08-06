#!/bin/sh

PROG=xsim
OBJS=$1
XO=$2
INP=$3
OUT=$4

count=0

rm -f $PROG *.o
make $PROG $1 > /dev/null

rm -f test.out

if [ ! -x $PROG ]; then
  echo $PROG not found
  echo " " FAILED
  exit 1
elif [ ! -f $2 ]; then
  echo $2 not found
  echo " " FAILED
  exit 1
fi

cat $3 | ./$PROG 100000 $2 1 > test.out
if diff test.out $4 > /dev/null; then
  echo " " PASSED
  exit 0
else
  echo " " FAILED
  exit 1
fi
