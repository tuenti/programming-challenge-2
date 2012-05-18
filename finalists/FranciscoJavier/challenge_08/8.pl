#!/usr/bin/perl

#input
$queue=<>;
chop $queue;
while (<>) {
    chop;
    %transform=();
    foreach (split /,/) {
	($a,$b)=split /=>/;
	$transform[$C]->{$a}=$b;
    } 
    $C++;
}

#precalculate full composite transform for each distinct input person
foreach (split '',$queue) {
    $alphabet{$_}=1;
}
foreach $p (keys %alphabet) {
    $output[0] = $p;
    foreach $i (1..$C) {
	$output[$i] = "";
	foreach $person (split '',$output[$i-1]) {
	    $output[$i].= $transform[$i-1]->{$person} || $person;
	}
    }
    $fulltransform{$p} = $output[$C];
}

#generate output
open MD5SUM, "| md5sum | cut -d ' ' -f 1";
foreach $person (split '',$queue) {
    print MD5SUM $fulltransform{$person};
}
close MD5SUM;
