#!/bin/sh

count=0

gcc -Wall -o itoa itoa.c

echo Testing Multi-CPU, Synchronous Input
if ./testrun2.sh  mt_echo.xo; then
  let "count = count + 3"
fi
echo Testing Multi-CPU, Asynchronous Input
if ./testrun2.sh mt_echo_ia.xo; then
  let "count = count + 3"
fi
echo Testing Multi-CPU Asyncronous Output
if ./testrun2.sh mt_echo_oa.xo; then
  let "count = count + 2"
fi
echo Testing Multi-CPU Asynchronous Input and Output
if ./testrun2.sh mt_echo_ioa.xo; then
  let "count = count + 2"
fi

echo =============================================
echo $count out of 10 marks.
