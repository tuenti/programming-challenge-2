#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $n_test_cases = <>;
print F $n_test_cases;
chomp $n_test_cases;

my $test_case;

for ($test_case = 1; $test_case <= $n_test_cases; $test_case++)
{
  my $number_n = <>;
  print F $number_n;
  chomp $number_n;

  # Input is the number of straight cuts made through a round chocolate cake
  # and output is the maximum number of cake pieces that can be produced.

  my $cuts = 1 + ($number_n * ($number_n + 1)) / 2;
  print "Case #$test_case: $cuts\n";

}

close F;

