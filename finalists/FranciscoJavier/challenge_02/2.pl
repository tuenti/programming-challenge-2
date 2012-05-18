#!/usr/bin/perl
use bigint;

$C=<>;
foreach $i (1..$C) {
    $N=<>;

    #extract msb
    $aux=$N;
    $msb=-1;
    while($aux) {
	$aux>>=1;
	$msb++;
    }

    #calculate M
    $mask = (1<<$msb)-1;
    $dif=$N-$mask;
    $M=count_ones($mask)+count_ones($dif);

    #output
    print "Case #$i: $M\n";
}

sub count_ones() {
    my $aux=shift;
    my $ones;
    while($aux) {
	$ones++ if $aux & 1;
	$aux>>=1;
    }
    $ones;
}
