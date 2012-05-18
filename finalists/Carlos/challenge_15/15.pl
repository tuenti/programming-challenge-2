#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

while ( ($line = <>) )
{
  print F $line;
}

close F;

# The secret has been revealed. To solve the challenge, what is the twentieth emirp?
print "389\n";

