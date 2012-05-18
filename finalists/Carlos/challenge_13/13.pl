#!/usr/bin/perl

use strict;
# I'm afraid we need these really-big bigints. (N can be up to 1000000)
use bigint;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $test_cases = <>;
print F $test_cases;
chomp $test_cases;
my $test_case;
for ($test_case = 1; $test_case <= $test_cases; $test_case++)
{
  $line = <>;
  print F $line;

  $line =~ /(\d+)\s+(\d+)/;
  my $n = $1;
  my $l = $2;
  my $m = crazy_croupier($1, $2);
  print "Case #$test_case: $m\n";
}


close F;




#my $n;
#my $l;
#
#for ($n = 1; $n < 45; $n++)
#{
#  for ($l = 0; $l <= $n; $l++)
#  {
#    my $r = crazy_croupier($n, $l);
#    print STDERR sprintf("%5d ", $r);
#  }
#  print STDERR "\n";
#}

sub crazy_croupier ($$)
{
  my $n = $_[0];
  my $l = $_[1];
  my $ret;

  if ($n == 1)
  {
    $ret = 1;
  }
  elsif ($l == 0)
  {
    $ret = 2
  }
  elsif (($n == 2) and ($l == 1))
  {
    $ret = 1;
  }
  elsif ($n > 3 * $l)
  {
    my $x = $n - 3 * $l;
    $ret = crazy_croupier(3 * $l, $l);
    if ((($ret % 2) != 0) and ($x >= 2))
    {
      $ret *= 2;
    }
  }
  elsif ($n == 3 * $l)
  {
    my %jumps = ();
    my $i;
    my $j;
    my $count;
    $ret = 1;
    for ($i = 0; $i < $n; $i++)
    {
      if (!exists $jumps{$i})
      {
        $count = 0;
        $j = $i;
        do
        {
          $jumps{$j} = 1;

          if ($j < $l)
          {
            $j = 2 * ($l - $j - 1);
          }
          elsif ($j < 2 * $l)
          {
            $j = 4 * $l - $j - 1;
          }
          else
          {
            $j = 6 * $l - 2 * $j - 1;
          }

          $count++;
        } while ($i != $j);

        $ret = lcm($ret, $count);
      }
    }
  }
  elsif ($n <= 2 * $l)
  {
    my %jumps = ();
    my $i;
    my $j;
    my $count;
    $ret = 1;
    for ($i = 0; $i < $n; $i++)
    {
      if (!exists $jumps{$i})
      {
        $count = 0;
        $j = $i;
        do
        {
          $jumps{$j} = 1;

          if ($j < 2 * $l - $n)
          {
            $j = $n - $j - 1;
          }
          elsif ($j < $l)
          {
            $j = 2 * ($l - $j - 1);
          }
          else
          {
            $j = 2 * $n - 2 * $j - 1;
          }

          $count++;
        } while ($i != $j);

        $ret = lcm($ret, $count);
      }
    }
  }
  else
  {
    my %jumps = ();
    my $i;
    my $j;
    my $count;
    $ret = 1;
    for ($i = 0; $i < $n; $i++)
    {
      if (!exists $jumps{$i})
      {
        $count = 0;
        $j = $i;
        do
        {
          $jumps{$j} = 1;

          if ($j < $l)
          {
            $j = 2 * ($l - $j - 1);
          }
          elsif ($j < $n - $l)
          {
            $j = $n + $l - $j - 1;
          }
          else
          {
            $j = 2 * $n - 2 * $j - 1;
          }

          $count++;
        } while ($i != $j);

        $ret = lcm($ret, $count);
      }
    }
  }

  return $ret;
}

# Greatest common divisor
sub gcd ($$)
{
  my $a = $_[0];
  my $b = $_[1];

  while ($b != 0)
  {
    my $t = $b;
    $b = $a % $b;
    $a = $t;
  }

  return $a;
}

# Least common multiple
sub lcm ($$)
{
  my $a = $_[0];
  my $b = $_[1];
  my $g = gcd($a, $b);
  # avoid overflow
  my $aa = int($a / $g);
  my $bb = int($b / $g);

  return $aa * $bb * $g;
}
