#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

while ( ($line = <>) )
{
  print F $line;
  chomp $line;

  my @stack = ();

  # operators
  my @ops = split(/\s+/, $line);

  my $reg;
  my $reg_temp;

  my $i;

  # Reverse Polish notation
  for ($i = 0; $i < scalar @ops; $i++)
  {
    $reg = $ops[$i];

    if ($reg eq "mirror")
    {
      $reg = pop(@stack);
      $reg = -$reg;
      push(@stack, $reg);
    }
    elsif ($reg eq "breadandfish")
    {
      $reg = pop(@stack);
      push(@stack, $reg);
      push(@stack, $reg);
    }
    elsif ($reg eq "#")
    {
      $reg = pop(@stack) * pop(@stack);
      push(@stack, $reg);
    }
    elsif ($reg eq "fire")
    {
      $reg = pop(@stack);
    }
    elsif ($reg eq '$')
    {
      $reg = pop(@stack);
      $reg = pop(@stack) - $reg;
      push(@stack, $reg);
    }
    elsif ($reg eq "dance")
    {
      $reg = pop(@stack);
      $reg_temp = pop(@stack);
      push(@stack, $reg);
      push(@stack, $reg_temp);
    }
    elsif ($reg eq "conquer")
    {
      $reg = pop(@stack);
      $reg_temp = pop(@stack);
      $reg = $reg_temp % $reg;
      push(@stack, $reg);
    }
    elsif ($reg eq "&")
    {
      $reg = pop(@stack);
      $reg = pop(@stack) / $reg;
      push(@stack, $reg);
    }
    elsif ($reg eq "@")
    {
      $reg = pop(@stack) + pop(@stack);
      push(@stack, $reg);
    }
    elsif ($reg eq ".")
    {
      $reg = pop(@stack);
      print "$reg\n";
    }
    elsif ($reg ne "")
    {
      push(@stack, $reg);
    }
  }
}


close F;

