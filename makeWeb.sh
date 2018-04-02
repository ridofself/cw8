#! /bin/ksh

make
./test
cp html/* ../html/
cp cgi-bin/* ../html/cgi-bin/
mkhomepg -p
