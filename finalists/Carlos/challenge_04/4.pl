#!/usr/bin/perl

use strict;

my $line;

# save input data, just for review
open F, ">input_data.txt";

my $test_cases = <>;
print F $test_cases;
chomp $test_cases;

while ($test_cases-- > 0)
{
  $line = <>;
  print F $line;
  $line =~ /(\d+)\s+(\d+)\s+(\d+)/;

  my $r = $1;
  my $k = $2;
  my $g = $3;

  $line = <>;
  print F $line;
  chomp $line;

  my @groups = split (/\s+/, $line);
  
  my %visited_group = ();
  my %litres_group = ();
  my %dest_group = ();

  my $curr_g = 0;

  do
  {
    my $people = 0;
    my $used_grps = 0;

    $visited_group{$curr_g} = 1;

    while ($used_grps < $g)
    {
      if ($groups[($curr_g + $used_grps) % $g] + $people <= $k)
      {
        $people += $groups[($curr_g + $used_grps) % $g];
        $used_grps++;
      }
      else
      {
        last;
      }
    }

    $litres_group{$curr_g} = $people;
    $dest_group{$curr_g} = ($curr_g + $used_grps) % $g;
    
    $curr_g = ($curr_g + $used_grps) % $g;
  } while (!exists $visited_group{$curr_g});

  my $period_start_g = $curr_g;
  my $preperiod_litres = 0;
  my $period_litres = 0;
  my $preperiod_len = 0;
  my $period_len = 0;

  $curr_g = 0;
  while ($curr_g != $period_start_g)
  {
    $preperiod_litres += $litres_group{$curr_g};
    $curr_g = $dest_group{$curr_g};
    $preperiod_len++;
  }

  do
  {
    $period_litres += $litres_group{$curr_g};
    $curr_g = $dest_group{$curr_g};
    $period_len++;
  } while ($curr_g != $period_start_g);


  my $litres = 0;

  $curr_g = 0;
  if ($r >= $preperiod_len + $period_len)
  {
    $r -= $preperiod_len;
    $litres += $preperiod_litres;
    $litres += int($r / $period_len) * $period_litres;
    $r = $r % $period_len;
    $curr_g = $period_start_g;
  }

  while ($r-- > 0)
  {
    $litres += $litres_group{$curr_g};
    $curr_g = $dest_group{$curr_g};
  }


  print "$litres\n";
}


close F;

