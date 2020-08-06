./xas test.$1.xas test.$1.xo
./xsim_gold 100000 test.$1.xo > test$1.out.gold
./xsim 100000 test.$1.xo > test$1.out
diff -y test$1.out.gold test$1.out
