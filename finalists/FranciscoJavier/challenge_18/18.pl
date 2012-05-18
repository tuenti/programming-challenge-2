#!/usr/bin/perl
use Math::BigInt;

#Bee is of course much more advanced than Ook, but backwards compatible.
#running the challenge 18 as an ook program, uncovered the following question:

#Input is the number of straight cuts made through a round chocolate cake and output is the maximum number of cake pieces that can be produced.

$C = <>;
foreach $case (1..$C) {
    $N=<>;
    print "Case #$case: ",1+($N*($N+1))/2,"\n";
}
