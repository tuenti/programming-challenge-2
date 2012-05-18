#!/usr/bin/perl
use Statistics::Basic qw(:all nofill);

$R=<>;
$U=<>;
$N=<>;

#known data
foreach $i (1..$R) {
    $_=<>;
    chop;
    @report=split ' ';
    $type=shift @report;

    push @types,$type;
    push(@reports,[@report]);
}

#normalize each component
foreach $j (0..$N-1) {
    @component=();
    foreach $i (0..$R-1) {
	push(@component,${reports[$i]}->[$j]);
    }
    $mean[$j]=avg(@component);
    $dev[$j]=stddev(@component);
    foreach $i (0..$R-1) {
	${reports[$i]}->[$j] -= $mean[$j];
	${reports[$i]}->[$j] /= $dev[$j];
    }
}

#data to test
foreach $i (1..$U) {
    $_=<>;
    chop;
    @report=split ' ';

    #normalize
    @report_norm=@report;
    foreach $j (0..$N-1) {
	$report_norm[$j] -= $mean[$j];
	$report_norm[$j] /= $dev[$j];
    }

    #find closest
    $idx = shortest_distance(\@report_norm);
    if ($types[$idx] eq "M") {
	foreach(@report) {
	    $sum_processes += $_;
	}
    }

}
print "$sum_processes\n";


sub shortest_distance {
    my $max_prod_index;
    my $max_prod;

    for ($i = 0; $i < @reports ; $i++) {
	$report = $reports[$i];
	my $prod = 0;
	for ($j = 0; $j < @{$report} ; $j++) {
	    $prod += $_[0]->[$j] * $report->[$j];
	}
	#print "DIST a $i: $prod\n";
	if ($prod > $max_prod) {
	    $max_prod = $prod;
	    $max_prod_index = $i;
	}
    } 
    return $max_prod_index;
}
