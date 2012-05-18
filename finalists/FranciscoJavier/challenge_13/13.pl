#!/usr/bin/perl
use Math::BigInt;

$C=<>;
foreach $case (1..$C) {
    $_ = <>;
    chop;
    ($N,$L) = split ' ';
    print("0\n"),next if $L > $N;

    @starting_deck = (0..$N-1);

    #do just one shuffle
    @deck = ();
    @set1 = @starting_deck[0..$L-1];
    @set2 = @starting_deck[$L..$N-1];
    while (@deck < $N) {
	push @deck, pop @set1 if @set1;
	push @deck, pop @set2 if @set2;
    }

    #extract cycle length for each card
    @cycle_len = ();
    for ($i = 0 ; $i < $N ; $i++) {
	$j = $i;
	do {
	    $cycle_len[$i]++;
	    $j = $deck[$j];
	    #speed up cycle calclation
	    if ($cycle_len[$j]) {
		$cycle_len[$i] = $cycle_len[$j];
		$j = $i;
	    }
	} while ($j != $i);
    }

    #minimum common multiple  (faster if removing duplicates first!)
    $res = Math::BigInt::blcm(uniq(@cycle_len));
    print "Case \#$case: $res\n";
}


sub uniq {
    return keys %{{ map { $_ => 1 } @_ }};
}
