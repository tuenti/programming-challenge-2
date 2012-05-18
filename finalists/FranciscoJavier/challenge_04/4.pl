#!/usr/bin/perl
use bigint;
$N=<>;

foreach $testcase (1..$N) {
    ($R,$k,$G) = split ' ',<>;
    @groups = split ' ',<>;
    @visited=();
    @races=();
    @liters=();

    $avail = $k;
    $i = 0;
    $liters = 0;
    for ($r=0;$r<$R;$r++) {
	$remaining_races = $R-$r;

	if ($visited[$i]) {
	    $races_since = $r-$races[$i];
	    $liters_since = $liters-$liters[$i];

	    $skip = int($remaining_races / $races_since);
	    if($skip) {
		$r += $races_since * $skip -1;
		$liters += $liters_since * $skip;
		next;
	    }
	}

	$visited[$i]=1;
	$liters[$i]=$liters;
	$races[$i]=$r;
	
	$groups_in = 0;
	while($avail >= $groups[$i] && $groups_in < $G) {
	    $avail -= $groups[$i];
	    $i = ($i+1) % $G;
	    $groups_in++;
	}
	#dispatch group
	$liters += $k-$avail;
	$avail = $k;

    }	
    print "$liters\n";
}
