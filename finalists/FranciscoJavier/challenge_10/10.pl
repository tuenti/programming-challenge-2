#!/usr/bin/perl

while(<>) {
    @stack=();
    chop;
    foreach (split / /) {
	if ($_ =~ /\d+/) {
	    push @stack,$_;
	}
	elsif ($_ eq "mirror") {
	    $a = pop @stack;
	    push @stack, -$a;
	}
	elsif ($_ eq "breadandfish") {
	    $a = pop @stack;
	    push @stack, $a;
	    push @stack, $a;
	}
	elsif ($_ eq "#") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $a * $b;
	}
	elsif ($_ eq "fire") {
	    $b = pop @stack;
	}
	elsif ($_ eq "\$") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $a - $b;
	}
	elsif ($_ eq "dance") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $b;
	    push @stack, $a;
	}
	elsif ($_ eq "conquer") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $a % $b;
	}
	elsif ($_ eq "&") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $a / $b;
	}
	elsif ($_ eq "@") {
	    $b = pop @stack;
	    $a = pop @stack;
	    push @stack, $a + $b;
	}
	elsif ($_ eq ".") {
	    $res = pop @stack;
	    print "$res\n";
	}
	else {
	    print STDERR "ERROR\n";
	}
    }
}
