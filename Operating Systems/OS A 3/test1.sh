#!/bin/sh

TESTS='0 1 2 3 4'
PROG=xsim
count=0

if [ ! -e $PROG ]; then
  echo Error: $PROG is not in the current directory 
  exit 1
fi

echo Attempting Full Test
if ./testrun.sh $PROG echo.xo echo.xas echo.xas; then
  let "count = count + 8"
else
  echo Attempting Partial Tests
  echo Testing xsim.c
  if ./testrun0.sh OBJS=xsim.o echo.xo echo.xas echo.xas; then
    let "count = count + 2"
  fi
  echo Testing xcpu.c
  if ./testrun0.sh OBJS=xcpu.o echo.xo echo.xas echo.xas; then
    let "count = count + 2"
  fi
  echo Testing devices.c
  if ./testrun0.sh OBJS=devices.o echo.xo echo.xas echo.xas; then
    let "count = count + 2"
  fi
  echo Testing xdev.c
  if ./testrun0.sh OBJS=xdev.o echo.xo echo.xas echo.xas; then
    let "count = count + 2"
  fi
fi

echo =============================================
echo $count out of 8 marks.
echo Run test2 now
