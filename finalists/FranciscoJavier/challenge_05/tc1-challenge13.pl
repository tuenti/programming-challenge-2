#!/usr/bin/perl

@numbers = ([1,1,1,1,1,1,0],  #0
	    [1,1,0,0,0,0,0],  #1
	    [1,0,1,1,0,1,1],  #2
	    [1,1,1,0,0,1,1],  #3
	    [1,1,0,0,1,0,1],  #4
	    [0,1,1,0,1,1,1],  #5
	    [0,1,1,1,1,1,1],  #6
	    [1,1,0,0,0,1,0],  #7
	    [1,1,1,1,1,1,1],  #8
	    [1,1,1,0,1,1,1]); #9

foreach $i (0..59) { 
    $leds_sm[$i]=tick_pair($i,($i+1)%60) + ($i>0)*$leds_sm[$i-1];
}
foreach $i (0..23) { 
    $leds_h[$i]=tick_pair($i,($i+1)%24) + ($i>0)*$leds_h[$i-1];
}

while(<>) {
    $segs = $_;

    $ciclos_s = int ($segs / 60);
    $ciclos_m = int ($segs / (60*60));
    $ciclos_h = int ($segs / (60*60*24));

    $resto_s = $segs % 60;
    $resto_m = int(($segs % (60*60)) / 60);
    $resto_h = int(($segs % (60*60*24)) / (60*60));
    
    $leds_s = $leds_sm[59] * $ciclos_s + ($resto_s>0)*$leds_sm[$resto_s-1];
    $leds_m = $leds_sm[59] * $ciclos_m + ($resto_m>0)*$leds_sm[$resto_m-1];
    $leds_h = $leds_h[23] * $ciclos_h + ($resto_h>0)*$leds_h[$resto_h-1];

    print 36+$leds_s+$leds_m+$leds_h,"\n";
}

sub tick_pair() {
    my $n1 = shift;
    my $n2 = shift;
    $n1_1 = int($n1 / 10);
    $n1_2 = $n1 % 10;
    $n2_1 = int($n2 / 10);
    $n2_2 = $n2 % 10;
    tick_digit($n1_1,$n2_1) + tick_digit($n1_2,$n2_2);
}

sub tick_digit() {
    my $n1 = shift;
    my $n2 = shift;
    my $p1 = $numbers[$n1];
    my $p2 = $numbers[$n2];
    my $ilums = 0;
    my $i;
    foreach $i (0..6) {$ilums++ if ${$p2}[$i] and not ${$p1}[$i]}    
    $ilums;
}

