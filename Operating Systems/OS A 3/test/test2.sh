#!/bin/sh

count=0

# These tests should be built in the distribution
# make xas > /dev/null
# ./xas echo_ia.xas echo_ia.xo > /dev/null
# ./xas echo_oa.xas echo_oa.xo > /dev/null
# ./xas echo_ioa.xas echo_ioa.xo > /dev/null
# ./xas randtest.xas randtest.xo > /dev/null
 
echo Testing Asynchronous Input
if ./testrun.sh  "OBJX=" echo_ia.xo echo.xas echo.xas; then
  let "count = count + 2"
fi
echo Testing Asyncronous Output
if ./testrun.sh "OBJX=" echo_oa.xo echo.xas echo.xas; then
  let "count = count + 2"
fi
echo Testing Asynchronous Input and Output
if ./testrun.sh "OBJX=" echo_ioa.xo echo.xas echo.xas; then
  let "count = count + 2"
fi
echo Testing Testing Random Device
if ./testrun.sh "OBJX=" randtest.xo empty.out empty.out; then
  let "count = count + 1"
fi

echo =============================================
echo $count out of 7 marks.
