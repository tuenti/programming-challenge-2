#!/usr/bin/perl

use strict;

# get md5sum
my $sum = <>;
$sum =~ /^([0-9a-fA-F]*)/;
$sum = $1;
print "$sum\n";

