#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $queue = <>;
print F $queue;
chomp $queue;

my @transformations = ();

my @people = split(//, $queue);


my $last_trans = -1;

# read all transformations, and accumulate them into the hash,
# in order to do only one transformation
while ( ($line = <>) )
{
  print F $line;
  chomp $line;

  my @transformations_of_serie = split(/,/, $line);
  
  push(@transformations, {});
  $last_trans++;

  foreach my $trans (@transformations_of_serie)
  {
    $trans =~ /(.)=>(.+)/;
    my $original = $1;
    my $clones = $2;

    $transformations[$last_trans]{$original} = $clones;
  }
}

close F;

my $num_cycles = scalar @transformations;

my @fast_transformations = ();
my $i;
for ($i = 0; $i < $num_cycles; $i++)
{
  push(@fast_transformations, {});
}

# now, dump to a file the resulting queue of people

my %total_trans = ();

foreach my $single_letter (qw(a b c d e f g h i j k l m n o p q r s t u v w x y z))
{
  $total_trans{$single_letter} = transformate($single_letter, \@transformations, 0, \@fast_transformations);

  my $up = uc($single_letter);

  $total_trans{$up} = transformate($up, \@transformations, 0, \@fast_transformations);
}

foreach my $person (@people)
{
  # output via stdout to md5sum
  print $total_trans{$person};
}

sub transformate ($$$$)
{
  my $input = $_[0];
  my $transformations = $_[1];
  my $n = $_[2];
  my $fast_transformations = $_[3];
  my $ret;
  my $r;
  my $incomplete;

  if ($n == scalar @$transformations)
  {
    $ret = $input;
  }
  else
  {
    my @letters = split(//, $input);

    $ret = "";
    my $incomplete = 0;

    foreach my $l (@letters)
    {
      if (exists $fast_transformations->[$n]{$l})
      {
        if (!$incomplete)
        {
          $ret .= $fast_transformations->[$n]{$l};
        }
      }
      else
      {
        if (exists $transformations->[$n]{$l})
        {
          $r = transformate($transformations->[$n]{$l}, $transformations, $n + 1, $fast_transformations);
          if ($r eq "")
          {
            $incomplete = 1;
          }
          else
          {
            $fast_transformations->[$n]{$l} = $r;
            if (!$incomplete)
            {
              $ret .= $r;
            }
          }
        }
        else
        {
          $r = transformate($l, $transformations, $n + 1, $fast_transformations);
          if ($r eq "")
          {
            $incomplete = 1;
          }
          else
          {
            $fast_transformations->[$n]{$l} = $r;
            if (!$incomplete)
            {
              $ret .= $r;
            }
          }
        }
      }
    }
    if ($incomplete or (length ($ret) > 32768))
    {
      #$ret = "";
    }
  }

  return $ret;
}

