#!/usr/bin/perl
use POSIX;

$C = <>;
foreach $case (1..$C) {
    $_ = <>;
    chop;
    ($W,$H,$ct) = split / /;

    $message = <>;
    chop $message;
    @words=split / /,$message;

    $ft_size=1;
    while(evaluate()) {$ft_size++};

    $thread = 0;
    if (--$ft_size) {
	$thread_inches_per_char = ($ft_size*$ft_size)/(2*$ct);
	foreach (@words) {
	    $thread += length($_) * $thread_inches_per_char;
	}
	$thread = ceil($thread);
    }
    print "Case #$case: $thread\n";
}

sub evaluate() {
    $inches_per_char = $ft_size / $ct;
    if ($inches_per_char > $H || $inches_per_char > $W) {
	return 0;
    }
    $x = -1;
    $y = 0;
    foreach $word (@words) {
	$len = length($word);
	while ( ($x+1+$len)*$inches_per_char  > $W) {
	    #go to next line
	    $x = -1;
	    $y += 1;
	    if ( ($y+1)*$inches_per_char > $H) {
		#does not fit
		return 0;
	    }
	}
	$x += (1+$len);
    }
    return 1;
}
