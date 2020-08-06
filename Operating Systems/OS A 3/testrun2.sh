#!/bin/sh

PROG=xsim
XO=$1

if [ ! -x $PROG ]; then
  echo $PROG not found
  echo " " FAILED
  exit 1
elif [ ! -f $2 ]; then
  echo $2 not found
  echo " " FAILED
  exit 1
fi

echo Please wait, this will take a minute
cat /dev/zero | ./$PROG 0 $1 4 | ./itoa | grep -v 255 | sort -n > test.out
if diff test.out test.gold > /dev/null; then
  echo " " PASSED
  exit 0
else
  echo " " FAILED
  cp test.out test.out.$1
  exit 1
fi
