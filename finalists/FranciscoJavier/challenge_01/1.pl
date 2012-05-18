#!/usr/bin/perl

%key=('1',02,' ',01,
      '2',14,'A',11,'B',12,'C',13,
      '3',24,'D',21,'E',22,'F',23,
      '4',34,'G',31,'H',32,'I',33,
      '5',44,'J',41,'K',42,'L',43,
      '6',54,'M',51,'N',52,'O',53,
      '7',65,'P',61,'Q',62,'R',63,'S',64,
      '8',74,'T',71,'U',72,'V',73,
      '9',85,'W',81,'X',82,'Y',83,'Z',84,
      '0',101);

$N=<>;
foreach(1..$N) {
    #init
    $cost=0;
    $cur=10;
    $upper=0;

    $line=<>;
    chop $line;
    foreach (split '',$line) {
	#print "$_\n";

	#check if case needs to be changed
	if ((/[A-Z]/ && !$upper) || (/[a-z]/ && $upper)) {
	    go(11);
	    press(1);
	}
	tr/a-z/A-Z/;

	go(int($key{$_} / 10));
	press($key{$_} % 10);

    }
    print "$cost\n";
}

sub go() {
    my $dest=shift;
    #print "  GOING FROM $cur to $dest\n";

    if ($cur == $dest) {
	$cost += 500;
    }
    else {
	while ($cur != $dest) {
	    ($y1,$x1) = (int($cur/3),$cur % 3);
	    ($y2,$x2) = (int($dest/3),$dest % 3);

	    #print "$x1,$y1 to $x2,$y2\n";
	    if ($x2>$x1 && $y2>$y1) {
		$cost+=350;
		$cur=($x1+1) + ($y1+1)*3;
	    }
	    elsif ($x2>$x1 && $y2<$y1) {
		$cost+=350;
		$cur=($x1+1) + ($y1-1)*3;
	    }
	    elsif ($x2<$x1 && $y2>$y1) {
		$cost+=350;
		$cur=($x1-1) + ($y1+1)*3;
	    }
	    elsif ($x2<$x1 && $y2<$y1) {
		$cost+=350;
		$cur=($x1-1) + ($y1-1)*3;
	    }
	    elsif ($x2<$x1) {
		$cost+=200;
		$cur=($x1-1) + ($y1)*3;
	    }
	    elsif ($x2>$x1) {
		$cost+=200;
		$cur=($x1+1) + ($y1)*3;
	    }
	    elsif ($y2<$y1) {
		$cost+=300;
		$cur=($x1) + ($y1-1)*3;
	    }
	    elsif ($y2>$y1) {
		$cost+=300;
		$cur=($x1) + ($y1+1)*3;
	    }
	    else {
		die "PAQUETE\n";
	    }
	}
    }
}

sub press() {
    my $times=shift;
    if ($cur == 11) {
	$upper=!$upper;
	#print "  Changing case\n";
    }
    
    #print "  Pressing $times times\n";
    $cost+= 100 * $times;
}
