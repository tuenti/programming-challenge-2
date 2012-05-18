#!/usr/bin/perl
$path=$0;
$path =~ s/challenge9.pl$//;


$C=<>;
foreach (1..$C) {
    $_=<>;
    chop;
    ($W,$N) = split / /;
    open IDX,"<$path/index/$W";
    foreach (1..$N) {
	$output=<IDX>;
    }
    print $output;
}

