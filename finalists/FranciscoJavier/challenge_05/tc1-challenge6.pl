#!/usr/bin/perl

#   0 1 2 3 4 5 6 7 8 9
@p=(6,2,5,5,4,5,6,3,7,6);

while(<>) {
    $_++;
    $D = int($_/(24*3600));
    $_ %= (24*3600);
    $H = int($_/3600);
    $_ %= 3600;
    $M = int($_/60);
    $S = $_ % 60;

    $sum = 0;
    for $i (0..23) {
	#hora $i
	$veces=60*60*($D+($H>$i))+(60*$M+$S)*($H==$i);
	$sum+=$veces* palitos($i);
    }
    for $i (0..59) {
	#minuto $i y segundo $i
	$veces =60*( (24*$D+$H)+($M>$i))+$S*($M==$i);
	$veces+=(24*60*$D+60*$H+$M+($S>$i));	
	$sum += $veces * palitos($i);
    }
    print "$sum\n";
}

sub palitos() {
    my $num=shift;
    $p[$num/10]+$p[$num % 10];
}


